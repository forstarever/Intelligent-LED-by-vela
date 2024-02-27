//
// Created by star on 2024/1/17.
//

#ifndef LAB2_GPIO_LED_LED_H
#define LAB2_GPIO_LED_LED_H

#include <stdio.h>
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
void print_buf_putchar(struct print_buffer *buffer, char ch);
int fputc(int ch, FILE *f);
void led_init() ;
void led_flash();
void test_delayer();





#endif //LAB2_GPIO_LED_LED_H
