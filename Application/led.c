//
// Created by star on 2023/12/14.
//

#include "led.h"

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

void led_init() {
    /* enable the LEDs GPIO clock */
    rcu_periph_clock_enable(RCU_GPIOF);//PF4
    rcu_periph_clock_enable(RCU_GPIOC);//PC10

    gpio_mode_set(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_10);
    gpio_mode_set(GPIOF, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_4);

    gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_4);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);

    //输入模式：
    rcu_periph_clock_enable(RCU_GPIOC);//PC11
    gpio_mode_set(GPIOC, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO_PIN_11);//设置为输入模式，无上拉
}

void led_flash() {

    uint32_t i,j;
    uint32_t in_bit;
    for(i=0;i<1440;i++)
        send0(GPIOC,GPIO_PIN_10);
    reset(GPIOC,GPIO_PIN_10);

    uint32_t rgb=0xFF;
    rgb =0x0000FF;
    uint32_t led[32];
    for(i=0;i<30;i++){
        send_rgb_1(GPIOC,GPIO_PIN_10,rgb);
//        rgb |= 1;
//        rgb<<=1;
        //led[i]=rgb;
    }
//    send_led(GPIOC,GPIO_PIN_10,led,30);
//    for(i=0;i<30;i++){
//        send_blue(GPIOC,GPIO_PIN_10);
////        //send_rgb_1(GPIOC,GPIO_PIN_10,rgb);
////        //send_blue(GPIOC,GPIO_PIN_10);
////        //delay_100ns(5);
////        //send1(GPIOC,GPIO_PIN_10);
//////        send0(GPIOC,GPIO_PIN_10);
//////        GPIO_BOP(GPIOC)=(uint32_t)GPIO_PIN_10;
//////        ugly_860ns_delay();
//////        GPIO_BC(GPIOC)=(uint32_t)GPIO_PIN_10;
//////        ugly_325ns_delay();
//    }
    reset(GPIOC,GPIO_PIN_10);
    delay_ms(1000);
}


void test_delayer(){
    int start_time=get_systick_ms(),end_time;
    int i;
    for(i=0;i<100000;i++)
        ugly_860ns_delay();
    end_time=get_systick_ms();
    printf("each time=%.2lf\n",(end_time-start_time)*1.0/100000*1e6);
}
//main函数
int main(void)
{
    led_init();
    reset(GPIOC, GPIO_PIN_10);
    reset(GPIOF, GPIO_PIN_4);
    while (1) {
//		test_delayer();
        printf("time=%d\n",get_systick_ms());
        led_flash();
    }
}


