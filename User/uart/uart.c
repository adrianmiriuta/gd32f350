#include "uart.h"
#include "./b_tp_stream/b_tp/inc/b_tp.h"


#ifndef NULL
#define NULL     ((void *)0)
#endif

volatile uint32_t v32_uartx = USART1;

void uart_init()
{
    
    usart_deinit(USART1);
    usart_baudrate_set(USART1,115200);
    usart_parity_config(USART1, USART_PM_NONE);
    usart_word_length_set(USART1, USART_WL_8BIT);
    usart_stop_bit_set(USART1, USART_STB_1BIT);
    usart_receive_config(USART1, USART_RECEIVE_ENABLE);
    usart_transmit_config(USART1, USART_TRANSMIT_ENABLE);
    
    
    usart_interrupt_enable(USART1, USART_INT_RBNEIE);
    nvic_irq_enable(USART1_IRQn, 0, 2);
    
    usart_enable(USART1);
}




void uart1_write_ch(uint8_t c)
{
    usart_data_transmit(USART1, c);
    while (RESET == usart_flag_get(USART1,USART_FLAG_TC));
}

void uart1_write(uint8_t *pbuf, uint32_t len)
{
    uint32_t i = 0;
    if(pbuf == NULL || len == 0)
    {
        return;
    }
    for(i = 0;i < len;i++)
    {
        uart1_write_ch(pbuf[i]);
    }
}



void uart0_write_ch(uint8_t c)
{
//    usart_data_transmit(USART0, c);
//    while (RESET == usart_flag_get(USART0,USART_FLAG_TC));
}

void uart0_write(uint8_t *pbuf, uint32_t len)
{
//    uint32_t i = 0;
//    if(pbuf == NULL || len == 0)
//    {
//        return;
//    }
//    for(i = 0;i < len;i++)
//    {
//        uart0_write_ch(pbuf[i]);
//    }
}




void USART1_IRQHandler()
{
   
}

