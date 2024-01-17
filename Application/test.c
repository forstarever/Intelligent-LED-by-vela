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
void U1_led_init() {
    /* enable the LEDs GPIO clock */
    rcu_periph_clock_enable(RCU_GPIOF);//PF4
    rcu_periph_clock_enable(RCU_GPIOC);//PC10

    gpio_mode_set(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_10);
    gpio_mode_set(GPIOF, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_4);

    gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_4);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);

    //输入模式：
    rcu_periph_clock_enable(RCU_GPIOC);//PC11
    gpio_mode_set(GPIOC, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO_PIN_11);//设置为输入模式，无上拉
}
void U1_led_flash() {

//    reset(GPIOC, GPIO_PIN_10);
    //reset(GPIOC, GPIO_PIN_10);
   // reset(GPIOF, GPIO_PIN_4);
    uint32_t i;
    uint32_t in_bit;
    reset(GPIOC, GPIO_PIN_10);
    for(i=0;i<10;i++){
        if(i&1)
            gpio_bit_set(GPIOC,GPIO_PIN_10);
        else
            gpio_bit_reset(GPIOC,GPIO_PIN_10);
        in_bit=gpio_input_bit_get(GPIOC, GPIO_PIN_11);//输入模式GPIO状态获取
        printf("%d\n",in_bit);
        gpio_bit_set(GPIOF,GPIO_PIN_4);
        delay_ms(1000);
        gpio_bit_reset(GPIOF,GPIO_PIN_4);
        delay_ms(1000);
    }
        //send0(GPIOC, GPIO_PIN_10);
//    GPIO_BOP(GPIOF) = (uint32_t)GPIO_PIN_4;
//    delay_ms(1000);
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


