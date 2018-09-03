#include "uart.h"



void uart_init()
{
    
    usart_deinit(USART1);
    usart_baudrate_set(USART1,115200);
    usart_receive_config(USART1, USART_RECEIVE_ENABLE);
    usart_transmit_config(USART1, USART_TRANSMIT_ENABLE);
    
    usart_deinit(USART0);
    usart_baudrate_set(USART0,115200);
    usart_receive_config(USART0, USART_RECEIVE_ENABLE);
    usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
    
    usart_interrupt_enable(USART1, USART_INT_RBNEIE);
    usart_interrupt_enable(USART0, USART_INT_RBNEIE);
    
    usart_enable(USART0);  
    usart_enable(USART1);
}




void uart1_write_ch(uint8_t c)
{
    usart_data_transmit(USART1, c);
    while (RESET == usart_flag_get(USART1,USART_FLAG_TC));
}



void USART0_IRQHandler()
{
    uint8_t tmp = 0;
    tmp = usart_data_receive(USART0);
}


void USART1_IRQHandler()
{
    uint8_t tmp = 0;
    tmp = usart_data_receive(USART1);
    uart1_write_ch(tmp);
}

