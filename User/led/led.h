#ifndef __LED_H__
#define __LED_H__



#include "./platform/platform.h"


#define LED1_ON()           gpio_bit_set(LED_PORT, LED1_PIN)
#define LED1_OFF()          gpio_bit_reset(LED_PORT, LED1_PIN)




void led_1s_toggle(void);


#endif


