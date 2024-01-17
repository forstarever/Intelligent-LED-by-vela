cmake_minimum_required(VERSION 3.23)
project(lab2_gpio_led C)

set(CMAKE_C_STANDARD 11)

include_directories(GD32F4xx_Firmware_Library/CMSIS)
include_directories(GD32F4xx_Firmware_Library/CMSIS/GD/GD32F4xx/Include)
include_directories(GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Include)

add_executable(lab2_gpio_led
        Application/main.c
        GD32F4xx_Firmware_Library/CMSIS/GD/GD32F4xx/Include/gd32f4xx.h
        GD32F4xx_Firmware_Library/CMSIS/GD/GD32F4xx/Include/gd32f4xx_libopt.h
        GD32F4xx_Firmware_Library/CMSIS/GD/GD32F4xx/Include/system_gd32f4xx.h
        GD32F4xx_Firmware_Library/CMSIS/GD/GD32F4xx/Source/system_gd32f4xx.c
        GD32F4xx_Firmware_Library/CMSIS/core_cm4.h
        GD32F4xx_Firmware_Library/CMSIS/core_cm4_simd.h
        GD32F4xx_Firmware_Library/CMSIS/core_cmFunc.h
        GD32F4xx_Firmware_Library/CMSIS/core_cmInstr.h
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Include/gd32f4xx_adc.h
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Include/gd32f4xx_can.h
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Include/gd32f4xx_crc.h
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Include/gd32f4xx_ctc.h
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Include/gd32f4xx_dac.h
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Include/gd32f4xx_dbg.h
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Include/gd32f4xx_dci.h
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Include/gd32f4xx_dma.h
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Include/gd32f4xx_enet.h
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Include/gd32f4xx_exmc.h
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Include/gd32f4xx_exti.h
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Include/gd32f4xx_fmc.h
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Include/gd32f4xx_fwdgt.h
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Include/gd32f4xx_gpio.h
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Include/gd32f4xx_i2c.h
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Include/gd32f4xx_ipa.h
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Include/gd32f4xx_iref.h
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Include/gd32f4xx_misc.h
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Include/gd32f4xx_pmu.h
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Include/gd32f4xx_rcu.h
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Include/gd32f4xx_rtc.h
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Include/gd32f4xx_sdio.h
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Include/gd32f4xx_spi.h
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Include/gd32f4xx_syscfg.h
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Include/gd32f4xx_timer.h
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Include/gd32f4xx_tli.h
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Include/gd32f4xx_trng.h
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Include/gd32f4xx_usart.h
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Include/gd32f4xx_wwdgt.h
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Source/gd32f4xx_adc.c
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Source/gd32f4xx_can.c
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Source/gd32f4xx_crc.c
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Source/gd32f4xx_ctc.c
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Source/gd32f4xx_dac.c
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Source/gd32f4xx_dbg.c
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Source/gd32f4xx_dci.c
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Source/gd32f4xx_dma.c
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Source/gd32f4xx_enet.c
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Source/gd32f4xx_exmc.c
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Source/gd32f4xx_exti.c
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Source/gd32f4xx_fmc.c
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Source/gd32f4xx_fwdgt.c
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Source/gd32f4xx_gpio.c
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Source/gd32f4xx_i2c.c
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Source/gd32f4xx_ipa.c
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Source/gd32f4xx_iref.c
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Source/gd32f4xx_misc.c
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Source/gd32f4xx_pmu.c
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Source/gd32f4xx_rcu.c
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Source/gd32f4xx_rtc.c
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Source/gd32f4xx_sdio.c
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Source/gd32f4xx_spi.c
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Source/gd32f4xx_syscfg.c
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Source/gd32f4xx_timer.c
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Source/gd32f4xx_tli.c
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Source/gd32f4xx_trng.c
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Source/gd32f4xx_usart.c
        GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Source/gd32f4xx_wwdgt.c Application/delay.h Application/delay.c Application/ws2812_gd32_pwm.c Application/ws2812.h Application/amk_gpio.h Application/rgb_common.h Application/rgb_common.c Application/ws2812.c Application/test.c Application/platform_systick.h Application/platform_systick.c Application/RGB.c Application/RGB.h)
