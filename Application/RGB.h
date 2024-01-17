//
// Created by star on 2023/12/20.
//

#ifndef LAB2_GPIO_LED_RGB_H
#define LAB2_GPIO_LED_RGB_H

#include <stdint.h>
//每组24bit对应的的GRB编码如下所示。发送颜色顺序为GRB，字节的高位在前。

typedef struct {
    uint8_t g;
    uint8_t r;
    uint8_t b;
} rgb_t;

void send0(uint32_t gpio_periph, uint32_t pin);
void send1(uint32_t gpio_periph, uint32_t pin);
void reset(uint32_t gpio_periph, uint32_t pin);


#endif //LAB2_GPIO_LED_RGB_H
