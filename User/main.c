#include "./platform/platform.h"
#include "./uart/uart.h"
#include "./delay/delay.h"
#include "./spiflash/spi.h"
#include "./spiflash/flash_dev.h"
#include "./calendar/calendar.h"
#include "./protocol/protocol_handle.h"
#include "./timer/timer.h"
#include "./mpu/mpu_dev.h"
int main()
{
    nvic_priority_group_set(NVIC_PRIGROUP_PRE0_SUB4);
    /** platform init   */
    platform_clock_enable();
    platform_gpio_init();
    delay_init();
    /** peripherals init   */
    uart_init();
    spi0_init();
//    pro_init();
    timer1_init();
    mpu_init();
    while(1)
    {
//        pro_main();
        
    }
}








