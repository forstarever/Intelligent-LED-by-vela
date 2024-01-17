//
// Created by star on 2023/12/14.
//

#include <stdio.h>
//#include <time.h>
#include "gd32f4xx.h"
#include "platform_systick.h"
#include "RGB.h"

//-----------debug----------//
typedef struct print_buffer
{
    char buf[4096];
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
////定时器初始化
//void time1_init(void)
//{
//
//    timer_parameter_struct timer_initpara;//定时器结构体
//
//    rcu_periph_clock_enable(RCU_TIMER1);//开启定时器时钟
//    //因为APB1是AHB的4分频，因此定时器时钟CK_TIMERx = CK_AHB = 200m
//    rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);//配置定时器时钟等于CK_AHB
//
//    timer_struct_para_init(&timer_initpara);//将定时器结构体内参数配置成默认参数
//    timer_deinit(TIMER1); //复位定时器
//
//    /* TIMER1 configuration */
//    //200M/200/1000 = 1k
//    //timer_initpara.prescaler         = 200-1;//预分频
//    timer_initpara.prescaler         = 10-1;//预分频
//    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE; //边缘对齐
//    timer_initpara.counterdirection  = TIMER_COUNTER_UP; //向上计数方式
//    //timer_initpara.period            = 1000-1; //计数值
//    timer_initpara.period            = 8-1; //计数值
//    // 200M/10/8 = 10^7 100ns 2.5*10^6 0.4*10^(-6) 400ns
//    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
//    timer_initpara.repetitioncounter = 0; //每次溢出都产生更新是件
//    timer_init(TIMER1,&timer_initpara);
//
//    /* auto-reload preload enable */
//    timer_auto_reload_shadow_enable(TIMER1);//使能自动重加载
//
//    timer_interrupt_enable(TIMER1,TIMER_INT_UP);//使能溢出中断
//
//    nvic_irq_enable(TIMER1_IRQn, 0, 1);//配置中断优先级
//
//    /* TIMER1 enable */
//    timer_enable(TIMER1);//使能定时器
//
//}
//uint32_t volatile msTicks; // Counter for millisecond Interval
////中断函数
//void TIMER1_IRQHandler(void)
//{
//    if(SET == timer_interrupt_flag_get(TIMER1,TIMER_INT_UP)){
//        //用户代码
//        msTicks++;
//        /* clear TIMER interrupt flag */
//        timer_interrupt_flag_clear(TIMER1,TIMER_INT_UP);
//    }
//}
//
//
//int get_ticks()
//{
//    return msTicks;
//}
//void delay_1tick(void)
//{
//    uint32_t curTicks;
//    curTicks = msTicks; // Save Current SysTick Value
//    while (msTicks == curTicks)
//    { // Wait for next SysTick Interrupt
//        __WFE(); // Power-Down until next Event/Interrupt
//    }
//}
//void delay_ms()
//{
//    int i;
//    // 1ms=10^-3 / 400*10^-9=2500
//    for (i = 0; i < 2500; i++)
//    {
//        delay_1tick();
//    }
//}




void U1_led_init() {
    /* enable the LEDs GPIO clock */
    rcu_periph_clock_enable(RCU_GPIOF);
    rcu_periph_clock_enable(RCU_GPIOC);

    gpio_mode_set(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_10);
    gpio_mode_set(GPIOF, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_4);

    gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_4);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);


    //gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,
    //GPIO_PIN_4);
    //gpio_bit_reset(GPIOF, GPIO_PIN_4);
}
void ugly_816ns_delay(){
	unsigned int cnt=22;
    while(cnt)
        cnt--;
}
void ugly_416ns_delay(){
	unsigned int cnt=7;
    while(cnt)
        cnt--;
}
void U1_led_flash() {

//    reset(GPIOC, GPIO_PIN_10);
    //reset(GPIOC, GPIO_PIN_10);
   // reset(GPIOF, GPIO_PIN_4);
    uint32_t i;
    reset(GPIOC, GPIO_PIN_10);
    for(i=0;i<1440;i++)
        send0(GPIOC, GPIO_PIN_10);
//    GPIO_BOP(GPIOF) = (uint32_t)GPIO_PIN_4;
//    delay_ms(1000);
//    GPIO_BC(GPIOF) = (uint32_t)GPIO_PIN_4;
//    delay_ms(1000);
//    for(i=0;i<1440;i++){
//        //uint32_t st=get_systick_ns();
//        GPIO_BOP(GPIOC) = (uint32_t)GPIO_PIN_10;
//        //GPIO_BOP(GPIOF) = (uint32_t)GPIO_PIN_4;
//        //gpio_bit_set(GPIOC, GPIO_PIN_10);
//        //gpio_bit_set(GPIOF, GPIO_PIN_4);
//        //printf("%d\n",get_systick_ns()-st);
////        delay_100ns(6);
////			delay_ms(100);
//        ugly_816ns_delay();
//        //st=get_systick_ns();
//        GPIO_BC(GPIOC) = (uint32_t)GPIO_PIN_10;
//        //GPIO_BC(GPIOF) = (uint32_t)GPIO_PIN_4;
//
////        gpio_bit_reset(GPIOC, GPIO_PIN_10);
////        gpio_bit_reset(GPIOF, GPIO_PIN_4);
//        //printf("%d\n",get_systick_ns()-st);
////        delay_100ns(2);
////			delay_ms(100);
//        ugly_416ns_delay();
//    }
}



//main函数
int main(void)
{
    //nvic_priority_group_set(NVIC_PRIGROUP_PRE2_SUB2);//配置优先级分组
    //time1_init();
    U1_led_init();
    //int st=time(NULL);
    reset(GPIOC, GPIO_PIN_10);
    reset(GPIOF, GPIO_PIN_4);
    while (1) {
        printf("time=%d\n",get_systick_ms());
        U1_led_flash();
    }
}


