#ifndef __UART_H__
#define __UART_H__

#include "gd32f3x0.h"






void uart_init(void);

void uart0_write_ch(uint8_t c);
void uart1_write_ch(uint8_t c);

void uart0_write(uint8_t *pbuf, uint32_t len);
void uart1_write(uint8_t *pbuf, uint32_t len);


extern volatile uint32_t v32_uartx;

#endif





