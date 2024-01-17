//
// Created by star on 2023/12/20.
//

#include "RGB.h"

void send0(uint32_t gpio_periph, uint32_t pin)
{
    gpio_bit_set(gpio_periph, pin);
    delay_100ns(4);//400ns T0H
    gpio_bit_reset(gpio_periph, pin);
    delay_100ns(8);//T0L
}
void send1(uint32_t gpio_periph, uint32_t pin)
{
    gpio_bit_set(gpio_periph, pin);
    delay_100ns(8);//T1H
    gpio_bit_reset(gpio_periph, pin);
    delay_100ns(4);//400ns T1L
}
void reset(uint32_t gpio_periph, uint32_t pin)
{
    gpio_bit_reset(gpio_periph, pin);
    int i;
    for(i=0;i<200;i++)
        delay_us(60);// 80us
}

// 0 255 0  G R B
void send_red(uint32_t gpio_periph, uint32_t pin)
{
    uint32_t i;
    for(i=0;i<8;i++)
        send0(gpio_periph,pin);
    for(i=0;i<8;i++)
        send1(gpio_periph,pin);
    for(i=0;i<8;i++)
        send0(gpio_periph,pin);
}
// 0 0 255
void send_blue(uint32_t gpio_periph, uint32_t pin)
{
    uint32_t i;
    for(i=0;i<16;i++)
        send0(gpio_periph,pin);
    for(i=0;i<8;i++)
        send1(gpio_periph,pin);
}
// 255 0 0
void send_green(uint32_t gpio_periph, uint32_t pin)
{
    uint32_t i;
    for(i=0;i<8;i++)
        send1(gpio_periph,pin);
    for(i=0;i<16;i++)
        send0(gpio_periph,pin);
}
void send_rgb(uint32_t gpio_periph, uint32_t pin,rgb_t rgb)
{
    uint32_t i;
    for(i=0;i<8;i++){
        if((rgb.g & 0x80) == 0x80){
            send1(gpio_periph,pin);
        }else
            send0(gpio_periph,pin);
        rgb.g<<=1;
    }
    for(i=0;i<8;i++){
        if((rgb.r & 0x80) == 0x80){
            send1(gpio_periph,pin);
        }else
            send0(gpio_periph,pin);
        rgb.r<<=1;
    }
    for(i=0;i<8;i++){
        if((rgb.b & 0x80) == 0x80){
            send1(gpio_periph,pin);
        }else
            send0(gpio_periph,pin);
        rgb.b<<=1;
    }
}
void send_led(uint32_t gpio_periph, uint32_t pin,rgb_t led[],uint32_t len)
{
    uint32_t p;
    for(p=0;p<len;p++){
        uint32_t i;
        rgb_t rgb=led[i];
        for(i=0;i<8;i++){
            if((rgb.g & 0x80) == 0x80){
                send1(gpio_periph,pin);
            }else
                send0(gpio_periph,pin);
            rgb.g<<=1;
        }
        for(i=0;i<8;i++){
            if((rgb.r & 0x80) == 0x80){
                send1(gpio_periph,pin);
            }else
                send0(gpio_periph,pin);
            rgb.r<<=1;
        }
        for(i=0;i<8;i++){
            if((rgb.b & 0x80) == 0x80){
                send1(gpio_periph,pin);
            }else
                send0(gpio_periph,pin);
            rgb.b<<=1;
        }
    }
}
