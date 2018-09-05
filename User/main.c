#include "./platform/platform.h"
#include "./uart/uart.h"
#include "./delay/delay.h"
#include "./spiflash/spi.h"
#include "./spiflash/flash_dev.h"
#include "./calendar/calendar.h"
#include "stdio.h"
#include "string.h"

int main()
{
    calendar_info_t calendar_info;
    uint8_t second = 0;
    uint8_t tmp[128];
    nvic_priority_group_set(NVIC_PRIGROUP_PRE0_SUB4);
    /** platform init   */
    platform_clock_enable();
    platform_gpio_init();
    delay_init();
    /** peripherals init   */
    uart_init();
    spi0_init();
    
    calendar_info.year = 18;
    calendar_info.month = 9;
    calendar_info.day = 5;
    calendar_info.week = 3;
    calendar_info.hour = 15;
    calendar_info.min = 26;
    calendar_info.second = 22;
    calendar_init(calendar_info);
    uart1_write((uint8_t *)"hello\n\r", 7);
    while(1)
    {
        calendar_get_date(&calendar_info);
        
        if(calendar_info.second != second)
        {
            sprintf((char *)tmp, "%2d-%2d-%2d %2d:%2d:%2d %2d\n\r", calendar_info.year, calendar_info.month, calendar_info.day, calendar_info.hour, calendar_info.min, calendar_info.second, calendar_info.week);
            uart1_write(tmp, strlen((char *)tmp));
            second = calendar_info.second;
        }
    }
}








