#ifndef _BSP_LED_H
#define _BSP_LED_H

#include "gd32f4xx.h"
#include "main.h"

#define LED1_ON     gpio_bit_set(PORT_LED1, PIN_LED1)
#define LED1_OFF    gpio_bit_reset(PORT_LED1, PIN_LED1)
#define LED1_TOGGLE gpio_bit_toggle(PORT_LED1, PIN_LED1)
#define LED2_ON     gpio_bit_set(PORT_LED2, PIN_LED2)
#define LED2_OFF    gpio_bit_reset(PORT_LED2, PIN_LED2)
#define LED3_ON     gpio_bit_set(PORT_LED3, PIN_LED3)
#define LED3_OFF    gpio_bit_reset(PORT_LED3, PIN_LED3)
#define LED4_ON     gpio_bit_set(PORT_LED4, PIN_LED4)
#define LED4_OFF    gpio_bit_reset(PORT_LED4, PIN_LED4)

#endif /* BSP_LED_H */