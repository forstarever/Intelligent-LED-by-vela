//
// Created by star on 2023/12/20.
//

#include "RGB.h"

void ugly_860ns_delay(){
    unsigned int cnt=30;
    while(cnt)
        cnt--;
}
void ugly_325ns_delay(){
    unsigned int cnt=6;
    while(cnt)
        cnt--;
}
//void send0(uint32_t gpio_periph, uint32_t pin)
//{
//    GPIO_BOP(GPIOC)=(uint32_t)GPIO_PIN_10;
//    ugly_325ns_delay();
//    GPIO_BC(GPIOC)=(uint32_t)GPIO_PIN_10;
//    ugly_860ns_delay();
//}
//void send1(uint32_t gpio_periph, uint32_t pin)
//{
//    GPIO_BOP(GPIOC)=(uint32_t)GPIO_PIN_10;
//    ugly_860ns_delay();
//    GPIO_BC(GPIOC)=(uint32_t)GPIO_PIN_10;
//    ugly_325ns_delay();
//}
void reset(uint32_t gpio_periph, uint32_t pin)
{
    gpio_bit_reset(gpio_periph, pin);
    delay_us(500);
//    int i;
//    for(i=0;i<200;i++)
//        delay_us(60);// 80us
}

// 0 255 0  G R B
void send_green_1(uint32_t gpio_periph, uint32_t pin)
{
    uint32_t i;
    delay_us(5);
    for(i=0;i<8;i++)
        send0(gpio_periph,pin);
    for(i=0;i<8;i++)
        send1(gpio_periph,pin);
    for(i=0;i<8;i++)
        send0(gpio_periph,pin);
}
// 0 0 255
void send_blue_1(uint32_t gpio_periph, uint32_t pin)
{
    uint32_t i;
    delay_us(5);
    for(i=0;i<16;i++)
        send0(gpio_periph,pin);
    for(i=0;i<8;i++)
        send1(gpio_periph,pin);
}
// 255 0 0
void send_red_1(uint32_t gpio_periph, uint32_t pin)
{
    uint32_t i;
    delay_us(5);
    for(i=0;i<8;i++)
        send1(gpio_periph,pin);
    for(i=0;i<16;i++)
        send0(gpio_periph,pin);
}
void send_rgb_1(uint32_t gpio_periph, uint32_t pin,uint32_t rgb)
{
    uint32_t i;
    delay_us(5);
    for(i=0;i<24;i++){
        if(rgb & 0x800000){
            send1(gpio_periph,pin);
        }else{
            send0(gpio_periph,pin);
        }
        rgb<<=1;
    }
}

void send_led_1(uint32_t gpio_periph, uint32_t pin,uint32_t led[],uint32_t len)
{
    uint32_t i;
    uint32_t rgb;
    for(i=0;i<len;i++){
        rgb=led[i];
        //printf("%d,",rgb);
        send_rgb_1(gpio_periph,pin,rgb);
    }
    reset(gpio_periph,pin);
}

//默认使用PC10端口
void send_green()
{
    send_green_1(GPIOC,GPIO_PIN_10);
}
// 0 0 255
void send_blue()
{
    send_blue_1(GPIOC,GPIO_PIN_10);
}
// 255 0 0
void send_red()
{
    send_red_1(GPIOC,GPIO_PIN_10);
}
void send_rgb()
{
    send_rgb_1(GPIOC,GPIO_PIN_10);
}

void send_led()
{
    send_led_1(GPIOC,GPIO_PIN_10);
}
