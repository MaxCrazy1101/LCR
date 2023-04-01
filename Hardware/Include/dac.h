#ifndef DAC_H
#define DAC_H
#include "gd32f4xx.h"
#define DAC_OUT_PORT GPIOA
#define DAC_OUT_PIN  GPIO_PIN_4
void dac_config();
#endif // DAC_H
