/*************************************************************************************************************
功能:     上电初始化后开始录音,完成后开始播放，循环往复(录音时间约10s)
版本:     2023-5-16 V1.0
修改记录: 无
作者:     ZZZ
编码格式：GB2312
*************************************************************************************************************/

#include "gd32f4xx.h"
#include "main.h"
#include "i2c.h"
#include "stdio.h"
#include "string.h"
#include "e4.h"

//-----------debug----------// need-for-printf
typedef struct print_buffer
{
    char buf[40096];
    int idx;
} print_buffer;
print_buffer stdio_print_buf;
void print_buf_putchar(struct print_buffer *buffer, char ch)
{
    if (buffer == NULL)
    {
        buffer = &stdio_print_buf;
    }
    if (buffer->idx >= sizeof(buffer->buf))
    {
        buffer->idx = 0;
    }
    buffer->buf[buffer->idx++] = ch;
}
int fputc(int ch, FILE *f)
{
    print_buf_putchar(NULL, ch);
    return ch;
    /* USART2 for printf */
    // usart_data_transmit(EVAL_COM0, (uint8_t) ch);
    // while (RESET == usart_flag_get(EVAL_COM0, USART_FLAG_TBE));
    // return ch;
}

uint16_t  delay_count = 0;                 //延时变量
uint16_t  time_count = 0;                  //1s定时变量

unsigned short playdata[PLAYCNT];		   //语音数据缓存

unsigned long playcnt = 0;				   //音频文件索引
unsigned char playflag = 0;				   //放音标志

uint8_t  start_flag = 0;	//录音标志
uint8_t  record_flag = 0;	//录音完成标志

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <math.h>

#define MAX_PCM_VALUE 32768.0
#define REFERENCE_PRESSURE 0.00002

double calculateDB() {
    double sum = 0.0;
    for(size_t i = 0; i < playcnt; ++i) if((double)playdata[i] < MAX_PCM_VALUE) {
            double normalizedSample = playdata[i] / MAX_PCM_VALUE;
            sum += normalizedSample * normalizedSample;
        }
    double rms =  sqrt(sum / playcnt);
    return 20.0 * log10(rms / REFERENCE_PRESSURE);
}

int colorBuffer[31];

//久坐提醒
uint8_t getSeatStatus(){
    return 1;
}
int seatMin=0;
void spark(){
    int T=5;
    while(T--){
        for(int i=0;i<30;i++){
            send_rgb(0);
        }
        printf("shit\n");
        delay_ms_1(500);
				printf("shit\n");
        for (int i = 0; i <30; ++i) {
            send_rgb(0xffffff);
        }
				printf("shit\n");
        delay_ms_1(500);
				printf("shit\n");
    }
    send_led(colorBuffer,30);
}
void seatTimer(){
    if(getSeatStatus())
        seatMin++;
    else seatMin=0;
    if(seatMin>=10){
        spark();
        seatMin=0;
    }
}

void print_dB(void) {
    double decibels = calculateDB();
    printf("%lf dB\n", decibels);

    //for(size_t i = 0; i < playcnt; ++i) if((double)playdata[i] < MAX_PCM_VALUE)
    //	printf("%d ", (int)playdata[i]);

    for(int i=29;i>0;i--)
        colorBuffer[i]=colorBuffer[i-1];

    if (decibels >= 55 && decibels < 64) {
        colorBuffer[0]=0x00ff00;
    }
    else if (decibels >= 64 && decibels < 67) {
        colorBuffer[0]=0x0000ff;
    }
    else if (decibels >= 67 && decibels < 75) {
        colorBuffer[0]=0xff0000;
    }
    else if (decibels<82) {
        colorBuffer[0] = 0xffffff;
    }
    else{
//        spark();
        for(int i=0;i<30;i++)
            colorBuffer[i]=0;
    }
    colorBuffer[0]=(colorBuffer[0]+colorBuffer[1])/2;
    send_led(colorBuffer,30);

}


int main(void)
{
    led_init();
    for(int i=0;i<720;i++){
        send1(GPIOC,GPIO_PIN_10);
    }
    for(int i=0;i<30;i++)
        colorBuffer[i]=0xFFFFFF;

    printf("Hello World!\n\n");
    nvic_priority_group_set(NVIC_PRIGROUP_PRE4_SUB0);

    dis_led_init();
    e4_init();

    while(1)
    {
        if(start_flag == 0)
        {
            start_flag = 1;
            record_flag = 0;
            playcnt = 0;
            e4_sound_recording_config();
            nvic_irq_enable(SPI2_IRQn,0,0);                //打开中断,可以录音
            LED_OFF;
        }
        else
        {
            if(record_flag)
            {
                record_flag = 0;
//                e4_playback_config();
                playflag = 1;
                LED_ON;
            }
        }
    }
    while(0){
        seatTimer();
        delay_ms_1(1000);
    }
}


/***********************************************************************************************************
//timer3 init 1ms定时
************************************************************************************************************/
void timer3_init(void)
{
    timer_parameter_struct timer_init_struct;

    rcu_periph_clock_enable(RCU_TIMER3);

    timer_deinit(TIMER3);
    timer_init_struct.prescaler			= 4199;
    timer_init_struct.period			= 20;
    timer_init_struct.alignedmode		= TIMER_COUNTER_EDGE;
    timer_init_struct.counterdirection	= TIMER_COUNTER_UP;
    timer_init_struct.clockdivision		= TIMER_CKDIV_DIV1;
    timer_init_struct.repetitioncounter = 0;
    timer_init(TIMER3, &timer_init_struct);

    nvic_irq_enable(TIMER3_IRQn, 1, 1);
    timer_interrupt_enable(TIMER3, TIMER_INT_UP);
    timer_enable(TIMER3);
}



/********************************************************************************************************
//初始化led
*********************************************************************************************************/
void  dis_led_init (void)
{
    /* enable the led clock */
    rcu_periph_clock_enable(RCU_GPIOF);
    /* configure led GPIO port */
    gpio_mode_set(GPIOF, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,GPIO_PIN_4);
    gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_4);

    GPIO_BC(GPIOF) = GPIO_PIN_4;
}


/********************************************************************************************************
//初始化串口
*********************************************************************************************************/
void uart_init(uint32_t usart_periph)
{
    if(usart_periph == USART0)
    {
        nvic_irq_enable(USART0_IRQn, 0, 0);
        rcu_periph_clock_enable(RCU_GPIOB);	/* enable GPIO clock */
        rcu_periph_clock_enable(RCU_USART0);	/* enable USART clock */
        gpio_af_set(GPIOB, GPIO_AF_7, GPIO_PIN_6);	/* connect port to USARTx_Tx */
        gpio_af_set(GPIOB, GPIO_AF_7, GPIO_PIN_7);	/* connect port to USARTx_Rx */
        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_6);	/* configure USART Tx as alternate function push-pull */
        gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_6);
        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_7);	/* configure USART Rx as alternate function push-pull */
        gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_7);
        /* USART configure */
        usart_deinit(USART0);
        usart_baudrate_set(USART0,115200U);
        usart_receive_config(USART0, USART_RECEIVE_ENABLE);
        usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
        usart_enable(USART0);
        usart_interrupt_enable(USART0, USART_INT_RBNE);
    }
    else if(usart_periph == USART2)
    {
        nvic_irq_enable(USART2_IRQn, 0, 0);
        rcu_periph_clock_enable(RCU_GPIOC);	/* enable GPIO clock */
        rcu_periph_clock_enable(RCU_USART2);	/* enable USART clock */
        gpio_af_set(GPIOC, GPIO_AF_7, GPIO_PIN_10);	/* connect port to USARTx_Tx */
        gpio_af_set(GPIOC, GPIO_AF_7, GPIO_PIN_11);	/* connect port to USARTx_Rx */
        gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_10);	/* configure USART Tx as alternate function push-pull */
        gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_10);
        gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_11);	/* configure USART Rx as alternate function push-pull */
        gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_11);
        /* USART configure */
        usart_deinit(USART2);
        usart_baudrate_set(USART2,115200U);
        usart_receive_config(USART2, USART_RECEIVE_ENABLE);
        usart_transmit_config(USART2, USART_TRANSMIT_ENABLE);
        usart_enable(USART2);
        usart_interrupt_enable(USART2, USART_INT_RBNE);
    }
}



/********************************************************************************************************
//串口发送数据
*********************************************************************************************************/
uint16_t uart_print(uint32_t usart_periph, uint8_t *data, uint16_t len)
{
    uint8_t i;
    for(i = 0; i < len; i++)
    {
        while(usart_flag_get(usart_periph, USART_FLAG_TC) == RESET);
        usart_data_transmit(usart_periph, data[i]);
    }
    while(usart_flag_get(usart_periph, USART_FLAG_TC) == RESET);
    return len;
}

/********************************************************************************************************
//调试串口发送数据
*********************************************************************************************************/
void debug_printf(uint32_t usart_periph,char *string)
{
    uint8_t  buffer[100];
    uint16_t len;

    len = strlen(string);
    strncpy((char*)buffer,string,len);
    uart_print(usart_periph,buffer,len);
}
/********************************************************************************************************
//1ms定时中断服务程序
*********************************************************************************************************/
void TIMER3_IRQHandler(void)
{
    if(timer_interrupt_flag_get(TIMER3, TIMER_INT_FLAG_UP))
    {
        timer_interrupt_flag_clear(TIMER3, TIMER_INT_FLAG_UP);

        if(delay_count > 0)
            delay_count--;

        if(time_count++ >= 300)
        {
            time_count = 0;

        }
    }
}



/********************************************************************************************************
//spi2 i2s中断
*********************************************************************************************************/
void SPI2_IRQHandler(void)
{
    if(SET == spi_i2s_interrupt_flag_get(SPI2,SPI_I2S_INT_TBE))
    {
        if(playflag)
        {
            spi_i2s_data_transmit(SPI2, playdata[playcnt++]);	//放音
            if(playcnt >= PLAYCNT)
            {
                playflag = 0;
                playcnt = 0;
                start_flag = 0;
            }
        }
        else
        {
            spi_i2s_data_transmit(SPI2, 0x0000);
        }
    }

    if(SET == spi_i2s_interrupt_flag_get(I2S2_ADD,SPI_I2S_INT_RBNE))
    {
        playdata[playcnt++] = spi_i2s_data_receive(I2S2_ADD);	//录音
        if(playcnt >= PLAYCNT)
        {
            print_dB(); //------------------------------
            spi_i2s_interrupt_disable(I2S2_ADD, SPI_I2S_INT_RBNE);
            record_flag = 1;
            playcnt = 0;
        }
    }
}





