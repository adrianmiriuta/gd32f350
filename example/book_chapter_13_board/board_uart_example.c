#include "example.h"

#if (EVB_EXAMPLE == CH13_BOARD_UART_EXAMPLE)

int main(void)
{
    int i;
    
    EvbUart1Config();
    while(1)
    {
        for (i =0;  i<0xffff; i++);        
        EvbUart1WriteStr("Hello liklon GD32F350Rx\n\r");
    }

    return 1;
}

#endif

