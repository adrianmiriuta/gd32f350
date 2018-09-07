#ifndef __LED_H__
#define __LED_H__



#include "./platform/platform.h"


#define LED1_ON()           gpio_bit_set(LED_PORT, LED1_PIN)
#define LED1_OFF()          gpio_bit_reset(LED_PORT, LED1_PIN)

#define LED2_ON()           gpio_bit_set(LED_PORT, LED2_PIN)
#define LED2_OFF()          gpio_bit_reset(LED_PORT, LED2_PIN)

#define LED3_ON()           gpio_bit_set(LED_PORT, LED3_PIN)
#define LED3_OFF()          gpio_bit_reset(LED_PORT, LED3_PIN)


void led_1s_toggle(void);
void led2_control(uint8_t n);
void led3_control(uint8_t n);

#endif


