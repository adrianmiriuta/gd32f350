#include "uart.h"
#include "./b_tp_stream/b_tp/inc/b_tp.h"


#ifndef NULL
#define NULL     ((void *)0)
#endif

volatile uint32_t v32_uartx = USART1;
uint8_t rx0_buf[256];
uint8_t rx1_buf[256];
#define USART1_RDATA_ADDRES    (USART1 + 0x24)
#define USART0_RDATA_ADDRES    (USART0 + 0x24)

void uart_init()
{
    dma_deinit(DMA_CH4);
    dma_deinit(DMA_CH2);
    usart_deinit(USART1);
    syscfg_dma_remap_disable(SYSCFG_DMA_REMAP_USART0RX);
    usart_baudrate_set(USART1,115200);
    usart_parity_config(USART1, USART_PM_NONE);
    usart_word_length_set(USART1, USART_WL_8BIT);
    usart_stop_bit_set(USART1, USART_STB_1BIT);
    usart_hardware_flow_rts_config(USART1, USART_RTS_DISABLE);
    usart_hardware_flow_cts_config(USART1, USART_CTS_DISABLE);
    usart_receive_config(USART1, USART_RECEIVE_ENABLE);
    usart_transmit_config(USART1, USART_TRANSMIT_ENABLE);
    usart_enable(USART1);
    
    
    dma_parameter_struct  dma_parameter;
    dma_parameter.direction = DMA_PERIPHERAL_TO_MEMORY;
    dma_parameter.memory_addr = (uint32_t)rx1_buf;
    dma_parameter.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
    dma_parameter.memory_width = DMA_MEMORY_WIDTH_8BIT;
    dma_parameter.periph_addr = USART1_RDATA_ADDRES;
    dma_parameter.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
    dma_parameter.periph_width = DMA_PERIPHERAL_WIDTH_8BIT;
    dma_parameter.priority = DMA_PRIORITY_ULTRA_HIGH;
    dma_parameter.number = 256;
    dma_init(DMA_CH4, dma_parameter);
    dma_circulation_disable(DMA_CH4);
    dma_memory_to_memory_disable(DMA_CH4);
    
    
    
    usart_deinit(USART0);
    usart_baudrate_set(USART0,115200);
    usart_parity_config(USART0, USART_PM_NONE);
    usart_word_length_set(USART0, USART_WL_8BIT);
    usart_stop_bit_set(USART0, USART_STB_1BIT);
    usart_hardware_flow_rts_config(USART0, USART_RTS_DISABLE);
    usart_hardware_flow_cts_config(USART0, USART_CTS_DISABLE);
    usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
    usart_receive_config(USART0, USART_RECEIVE_ENABLE);
    usart_enable(USART0);


    dma_parameter.direction = DMA_PERIPHERAL_TO_MEMORY;
    dma_parameter.memory_addr = (uint32_t)rx0_buf;
    dma_parameter.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
    dma_parameter.memory_width = DMA_MEMORY_WIDTH_8BIT;
    dma_parameter.periph_addr = USART0_RDATA_ADDRES;
    dma_parameter.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
    dma_parameter.periph_width = DMA_PERIPHERAL_WIDTH_8BIT;
    dma_parameter.priority = DMA_PRIORITY_ULTRA_HIGH;
    dma_parameter.number = 256;
    dma_init(DMA_CH2, dma_parameter);
    
    dma_circulation_disable(DMA_CH2);
    dma_memory_to_memory_disable(DMA_CH2);
    

    usart_interrupt_enable(USART1, USART_INT_IDLEIE);
    usart_interrupt_enable(USART0, USART_INT_IDLEIE);
    nvic_irq_enable(USART0_IRQn, 0, 2);
    nvic_irq_enable(USART1_IRQn, 0, 2);
    
    dma_channel_enable(DMA_CH4);
    dma_channel_enable(DMA_CH2);
    usart_dma_receive_config(USART1, USART_DENR_ENABLE);
    usart_dma_receive_config(USART0, USART_DENR_ENABLE);
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
    usart_data_transmit(USART0, c);
    while (RESET == usart_flag_get(USART0,USART_FLAG_TC));
}

void uart0_write(uint8_t *pbuf, uint32_t len)
{
    uint32_t i = 0;
    if(pbuf == NULL || len == 0)
    {
        return;
    }
    for(i = 0;i < len;i++)
    {
        uart0_write_ch(pbuf[i]);
    }
}


void USART0_IRQHandler()
{
//    uint8_t tmp = 0;
//    tmp = usart_data_receive(USART0);
//    if(v32_uartx == USART0)
//    {
//        b_tp_receive_data(&tmp, 1);
//    }
//    else
//    {
//        uart1_write_ch(tmp);
//    }
    uint32_t count = 0, tmp = 0;
    static uint32_t index = 0, count_last = 256;
    if(usart_interrupt_flag_get(USART0, USART_INT_IDLEIE_IDLEF) == SET)
    {
        usart_interrupt_flag_clear(USART0, USART_FLAG_IDLEF);
        count = dma_transfer_number_get(DMA_CH2);
        tmp = count_last - count;
        count_last = count;
        if(tmp > 0)
        {
            if(v32_uartx == USART0)
            {
                b_tp_receive_data(&rx0_buf[index], tmp);
            }
            else
            {
                uart1_write(&rx0_buf[index], tmp);
            } 
            index += tmp;
        }
        if(count < 30)
        {
            dma_channel_disable(DMA_CH2);
            dma_transfer_number_config(DMA_CH2, 256);
            dma_channel_enable(DMA_CH2);
            index = 0;
            count_last = 256;
        }
       
    }
}


void USART1_IRQHandler()
{
//    uint8_t tmp = 0;
//    tmp = usart_data_receive(USART1);

//    b_tp_receive_data(&tmp, 1);
//    uart0_write_ch(tmp);
    uint32_t count = 0, tmp = 0;
    static uint32_t index = 0, count_last = 256;
    if(usart_interrupt_flag_get(USART1, USART_INT_IDLEIE_IDLEF) == SET)
    {
        usart_interrupt_flag_clear(USART1, USART_FLAG_IDLEF);
        count = dma_transfer_number_get(DMA_CH4);
        tmp = count_last - count;
        count_last = count;
        if(tmp > 0)
        {
            b_tp_receive_data(&rx1_buf[index], tmp);
            uart0_write(&rx1_buf[index], tmp);
            index += tmp;
        }
        if(count < 30)
        {
            dma_channel_disable(DMA_CH4);
            dma_transfer_number_config(DMA_CH4, 256);
            dma_channel_enable(DMA_CH4);
            index = 0;
            count_last = 256;
        }
    }
    
}

