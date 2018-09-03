#include "./platform/platform.h"
#include "./uart/uart.h"






int main()
{
    nvic_priority_group_set(NVIC_PRIGROUP_PRE0_SUB4);
    /** platform init   */
    platform_clock_enable();
    platform_gpio_init();
    /** peripherals init   */
    uart_init();
    uart1_write((uint8_t *)"hello world\n\r", 13);
    while(1)
    {
        ;
    }
    return 0;
}








