//
// Created by star on 2023/12/20.
//

#ifndef LAB2_GPIO_LED_RGB_H
#define LAB2_GPIO_LED_RGB_H

#include <stdint.h>
#include "gd32f4xx.h"
#include "platform_systick.h"
//每组24bit对应的的GRB编码如下所示。发送颜色顺序为GRB，字节的高位在前。

typedef struct {
    uint8_t g;
    uint8_t r;
    uint8_t b;
} rgb_t;

#define send0(gpio_periph,pin) { \
GPIO_BOP(GPIOC)=(uint32_t)GPIO_PIN_10;\
ugly_325ns_delay();\
GPIO_BC(GPIOC)=(uint32_t)GPIO_PIN_10;\
ugly_860ns_delay();              \
}\

#define send1(gpio_periph,pin) { \
GPIO_BOP(GPIOC)=(uint32_t)GPIO_PIN_10;\
ugly_860ns_delay();\
GPIO_BC(GPIOC)=(uint32_t)GPIO_PIN_10;\
ugly_325ns_delay();              \
}\




void ugly_860ns_delay();
void ugly_325ns_delay();
//void send0(uint32_t gpio_periph, uint32_t pin);
//void send1(uint32_t gpio_periph, uint32_t pin);
void reset(uint32_t gpio_periph, uint32_t pin);
void send_blue_1(uint32_t gpio_periph, uint32_t pin);
void send_green_1(uint32_t gpio_periph, uint32_t pin);
void send_red_1(uint32_t gpio_periph, uint32_t pin);

void send_rgb_1(uint32_t gpio_periph, uint32_t pin,uint32_t rgb);
void send_led_1(uint32_t gpio_periph, uint32_t pin,uint32_t led[],uint32_t len);
void send_green();
void send_blue();
void send_red();
void send_rgb();
void send_led();

#endif //LAB2_GPIO_LED_RGB_H
