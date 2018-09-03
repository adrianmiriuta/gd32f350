#include "example.h"

#if (EVB_EXAMPLE == CH13_BOARD_LED_EXAMPLE)

int main(void)
{
    int i;
    
    EvbLedConfig();
    while(1)
    {
        for (i =0;  i<0xfffff; i++);        
        EvbLedControl(LED1, LED_ON);
        EvbLedControl(LED2, LED_ON);
        EvbLedControl(LED3, LED_ON);
        
        for (i =0;  i<0xfffff; i++);  
        EvbLedControl(LED1, LED_OFF);
        EvbLedControl(LED2, LED_OFF);
        EvbLedControl(LED3, LED_OFF);
    }

    return 1;
}

#endif

