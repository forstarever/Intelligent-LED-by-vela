/*
 * Copyright (C) 2020, 2021  huohongpeng
 * Author: huohongpeng <1045338804@qq.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Change logs:
 * Date        Author       Notes
 * 2020-10-29  huohongpeng   First add
 * 2021-11-28  huohongpeng   fix bug [systick_ms, systick_us update can't synchronization with SysTick->VAL update]
 */
#include "platform_systick.h"
#include "gd32f4xx.h"

/*
 * Systick select external clock source
 * value is 0.5s clock count number
 * User overwrite the macro define value
 */
#define SYSTICK_EXT_CLOCK_500MS_CNT (120000000/8/2)

volatile static uint32_t systick_ns = 0;
volatile static uint32_t systick_ms = 0;
volatile static uint32_t systick_us = 0;
volatile static uint8_t is_init = 0;

static void systick_init(void)
{
    __disable_irq();
    is_init = 1;
    SysTick->LOAD  = SYSTICK_EXT_CLOCK_500MS_CNT;
    SysTick->VAL   = SYSTICK_EXT_CLOCK_500MS_CNT;
    SysTick->CTRL  = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
    __enable_irq();
}

void systick_deinit(void)
{
    __disable_irq();
    is_init = 0;
    SysTick->CTRL  &= (~(SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk));
    __enable_irq();
}
void delay_100ns(uint32_t ns)
{
    if (!is_init) systick_init();

    uint32_t end_count = 0, current = 0;

    current = get_systick_ns();
    end_count = current + ns;

    if (end_count == current) {
        return;
    } else if (end_count > current) {
        while (get_systick_ns() < end_count);
    } else {
        while (get_systick_ns() >= current);
        while (get_systick_ns() < end_count);
    }
}
void delay_us(uint32_t us)
{
    if (!is_init) systick_init();

    uint32_t end_count = 0, current = 0;

    current = get_systick_us();
    end_count = current + us;

    if (end_count == current) {
        return;
    } else if (end_count > current) {
        while (get_systick_us() < end_count);
    } else {
        while (get_systick_us() >= current);
        while (get_systick_us() < end_count);
    }
}

void delay_ms_1(uint32_t ms)
{
    if(!is_init) systick_init();

    uint32_t end_count = 0, current = 0;

    current = get_systick_ms();
    end_count = current + ms;

    if (end_count == current) {
        return;
    } else if (end_count > current) {
        while (get_systick_ms() < end_count);
    } else {
        while (get_systick_ms() >= current);
        while (get_systick_ms() < end_count);
    }
}
uint32_t get_systick_ns(void)
{
    if (!is_init) systick_init();

    uint32_t _systick_ns, _val;

    do {
        _systick_ns = systick_ns;
        _val = SysTick->VAL;
    } while (_systick_ns != systick_ns);

#if 0
    /*
	 * 64bit, low efficiency
	 */
	uint64_t tick = (SYSTICK_EXT_CLOCK_500MS_CNT - _val);
	uint32_t tick_us =(tick * 1000 * 500) / SYSTICK_EXT_CLOCK_500MS_CNT;
#else
    /*
     * 32bit, high efficiency
     */
    uint32_t tick = (SYSTICK_EXT_CLOCK_500MS_CNT - _val);
    uint32_t tick_ns =(tick * 2000) / (SYSTICK_EXT_CLOCK_500MS_CNT / 2500);
#endif

    return (tick_ns + _systick_ns);
}
/*
 * Max 4294967295(us)=4294967(us)=4294(s)=71(min)
 */
uint32_t get_systick_us(void)
{
    if (!is_init) systick_init();

    uint32_t _systick_us, _val;

    do {
        _systick_us = systick_us;
        _val = SysTick->VAL;
    } while (_systick_us != systick_us);

#if 0
    /*
	 * 64bit, low efficiency
	 */
	uint64_t tick = (SYSTICK_EXT_CLOCK_500MS_CNT - _val);
	uint32_t tick_us =(tick * 1000 * 500) / SYSTICK_EXT_CLOCK_500MS_CNT;
#else
    /*
     * 32bit, high efficiency
     */
    uint32_t tick = (SYSTICK_EXT_CLOCK_500MS_CNT - _val);
    uint32_t tick_us =(tick * 200) / (SYSTICK_EXT_CLOCK_500MS_CNT / 2500);
#endif

    return (tick_us + _systick_us);
}

/*
 * Max 4294967295(ms)=4294967(s)=71582(min)=1193(hour)=49(day)
 */
uint32_t get_systick_ms(void)
{
    if (!is_init) systick_init();

    uint32_t _systick_ms, _val;

    do {
        _systick_ms = systick_ms;
        _val = SysTick->VAL;
    } while (_systick_ms != systick_ms);

    uint32_t tick = (SYSTICK_EXT_CLOCK_500MS_CNT - _val);
    uint32_t tick_ms = tick / (SYSTICK_EXT_CLOCK_500MS_CNT / 500);
    tick_ms = tick_ms + _systick_ms;

    return tick_ms ;
}

/*
 * Call by Systick interrupt server
 */
void systick_handler(void)
{
    systick_ns += 500 * 10000;
    systick_us += 500 * 1000;
    systick_ms += 500;
}


void SysTick_Handler(void)
{
    systick_handler();
}