#ifndef __PLATFORM_SYSTICK_H__
#define __PLATFORM_SYSTICK_H__

#include <stdint.h>

uint32_t get_systick_ns(void);
uint32_t get_systick_us(void);
uint32_t get_systick_ms(void);

void delay_100ns(uint32_t ns);
void delay_ms_1(uint32_t ms);
void delay_us(uint32_t us);
void systick_deinit(void);
/*
 * Call by Systick interrupt server
 */
void systick_handler(void);

#endif
