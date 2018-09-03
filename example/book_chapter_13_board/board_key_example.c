#include "example.h"

#if (EVB_EXAMPLE == CH13_BOARD_KEY_EXAMPLE)

/* 处理器BOOT之后会调用main函数，必须提供 */
int main(void)
{
    int i = 0;
    
    EvbLedConfig();
    EvbKeyConfigPoll();
    
    while(1)
    {
        if (EvbKeyScanPoll() == 1) 
        {
            for (i =0; i<0xfffff; i++);   
            
            EvbLedControl(LED1, LED_ON);
            EvbLedControl(LED2, LED_ON);
            EvbLedControl(LED3, LED_ON);
            
            for (i =0; i<0xfffff; i++);  
            EvbLedControl(LED1, LED_OFF);
            EvbLedControl(LED2, LED_OFF);
            EvbLedControl(LED3, LED_OFF);
        }
        else
        {
            EvbLedControl(LED1, LED_OFF);
            EvbLedControl(LED2, LED_OFF);
            EvbLedControl(LED3, LED_OFF);
        }
    }

    return 1;
}

#endif
