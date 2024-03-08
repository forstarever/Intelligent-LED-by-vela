/*!
    \file  i2c.h
    \brief the header file of I2C
*/



#ifndef I2C_H
#define I2C_H

#include "gd32f4xx.h"

#define I2C0_SPEED              100000
#define I2C0_SLAVE_ADDRESS7     0xA0
#define I2C_PAGE_SIZE           8

#define I2C1_SPEED              100000
#define I2C1_SLAVE_ADDRESS7     0xA0

#define I2C2_SPEED              100000
#define I2C2_SLAVE_ADDRESS7     0xA0

#define I2C_OK                 0
#define I2C_FAIL               1


typedef struct
{
	 uint8_t flag;
	 uint32_t periph;
	 uint8_t addr;
}i2c_addr_def;

void i2c_delay(uint32_t time);
void i2c0_gpio_config(void);
void i2c0_config(void);
void i2c1_gpio_config(void);
void i2c1_config(void);
void i2c2_gpio_config(void);
void i2c2_config(void);

uint8_t i2c_addr_poll(uint32_t i2c_periph,uint8_t poll_addr);
void i2c_cmd_write(uint32_t i2c_periph,uint8_t cmd,uint8_t addr);
void i2c_byte_write(uint32_t i2c_periph,uint8_t i2c_addr,uint8_t write_address,uint8_t buffer);
void i2c_write(uint32_t i2c_periph,uint8_t i2c_addr,uint8_t write_address,uint8_t* p_buffer,  uint8_t number_of_byte);
uint8_t i2c_read(uint32_t i2c_periph,uint8_t i2c_addr,uint8_t read_address,uint8_t* p_buffer,  uint16_t number_of_byte);
void i2c_direct_read(uint32_t i2c_periph,uint8_t i2c_addr,uint8_t* p_buffer,  uint16_t number_of_byte);
void init_i2c(void);
i2c_addr_def get_board_address(uint8_t address);
void i2c_delay_byte_write(uint32_t i2c_periph,uint8_t i2c_addr,uint8_t write_address,uint8_t buffer);
uint8_t i2c_delay_read(uint32_t i2c_periph,uint8_t i2c_addr,uint8_t read_address,uint8_t* p_buffer,  uint16_t number_of_byte);
void i2c_delay_write(uint32_t i2c_periph,uint8_t i2c_addr,uint8_t write_address,uint8_t* p_buffer,  uint8_t number_of_byte);



/* I2C read and write functions */
void i2c2_addr_init(uint8_t addr);
void i2c2_cmd_write(uint8_t cmd);
void i2c2_byte_write(uint8_t write_address,uint8_t buffer);
void i2c2_write(uint8_t write_address,uint8_t* p_buffer,  uint8_t number_of_byte);
void i2c2_read(uint8_t read_address,uint8_t* p_buffer,  uint16_t number_of_byte);
#endif  /* I2C_H */
