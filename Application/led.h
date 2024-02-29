//
// Created by star on 2024/1/17.
//

#ifndef LED_H
#define LED_H

#include <stdio.h>
#include "gd32f4xx.h"
#include "platform_systick.h"
#include "RGB.h"


//void print_buf_putchar(struct print_buffer *buffer, char ch);
//int fputc(int ch, FILE *f);
void led_init() ;
void led_flash();
void test_delayer();

#endif //LAB2_GPIO_LED_LED_H
