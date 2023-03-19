#ifndef ADC_H
#define ADC_H
#include "gd32f4xx.h"
#define ADC0_CHANNEL_LENGTH 2
extern uint16_t adc0_data[ADC0_CHANNEL_LENGTH];
extern uint16_t adc1_data[1024];
void adc_config();
#endif // ADC_H
