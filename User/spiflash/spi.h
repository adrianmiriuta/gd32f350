#ifndef __SPI_H__
#define __SPI_H__




#include "./platform/platform.h"



void spi0_init(void);
void spi0_write(uint8_t ch);
uint8_t spi0_read(void);

uint8_t spi0_rw_byte(uint8_t ch);

#endif


