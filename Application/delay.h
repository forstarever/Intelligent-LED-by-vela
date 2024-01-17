//
// Created by star on 2023/12/7.
//

#ifndef LAB2_GPIO_LED_DELAY_H
#define LAB2_GPIO_LED_DELAY_H

#ifndef DELAY_H
#define DELAY_H
#include "gd32f4xx.h"

void Delay_Init(void);

uint32_t millis(void)  ; //毫秒级运行定时器
uint32_t micros(void)  ; //微秒级运行定时器


//void delay_ms(uint32_t ms) ; //毫秒级延时函数
void delay_us(uint32_t us) ; //毫秒级延时函数


#endif


#endif //LAB2_GPIO_LED_DELAY_H


