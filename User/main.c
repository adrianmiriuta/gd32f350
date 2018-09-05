#include "./platform/platform.h"
#include "./uart/uart.h"
#include "./delay/delay.h"
#include "./spiflash/spi.h"
#include "./spiflash/flash_dev.h"




int main()
{
    uint8_t tmp_table[16];
    nvic_priority_group_set(NVIC_PRIGROUP_PRE0_SUB4);
    /** platform init   */
    platform_clock_enable();
    platform_gpio_init();
    delay_init();
    /** peripherals init   */
    uart_init();
    uart1_write((uint8_t *)"hello world\n\r", 13);
    
    spi0_init();
    flash_erase_xsector(0x0, 1);
    flash_write_buf((uint8_t *)"liklon gd32f350", 0, 15);
    flash_read_buf(tmp_table, 0, 15);
    uart1_write(tmp_table, 15);
    while(1)
    {

    }
}








