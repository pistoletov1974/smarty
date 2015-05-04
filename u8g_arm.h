/*
  
  u8g_arm.h
  
  Header file for u8g LPC122x utility procedures 

  Universal 8bit Graphics Library
  
  Copyright (c) 2013, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, 
  are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list 
    of conditions and the following disclaimer.
    
  * Redistributions in binary form must reproduce the above copyright notice, this 
    list of conditions and the following disclaimer in the documentation and/or other 
    materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  

*/
 
 
#ifndef _U8G_ARM_H
#define _U8G_ARM_H
 
#include "u8g.h"
#include "stm32f10x_conf.h"
 
#define SYS_CLK 24000000    /* in this example we use SPEED_HIGH = 48 MHz */
#define DELAY_TIM_FREQUENCY 1000000 /* = 1MHZ -> timer runs in microseconds */
#define SSD1306_I2C_ADDRESS   0x78	// 011110+SA0+RW - 0x3C or 0x3D
 
#define SSD1306_SEGREMAP 0xA0
#define SSD1306_COMSCANINC 0xC0
 
u8g_t u8g;
 
void delay_init(void);
void delay_system_ticks(uint32_t sys_ticks);	
void delay_micro_seconds(uint32_t us);
void I2C_stop(void);
void I2C_start( uint8_t address, uint8_t direction);
 
void i2c_init(uint32_t ns) U8G_NOINLINE;
void i2c_out(uint8_t data);
void i2c_command(uint8_t data);
uint8_t u8g_com_hw_i2c_fn(u8g_t *u8g, uint8_t msg, BitAction arg_val, void *arg_ptr);
 
#endif
 

