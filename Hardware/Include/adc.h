#ifndef ADC_H
#define ADC_H
#include "gd32f4xx.h"

#define ADC_BITS        12   // 采样值位数
#define ADC_REF_VOLTAGE 3.3f // 参考电压

/* ADC通道长度 */
#define ADC0_CHANNEL_LENGTH 3

/* ADC数据缓存大小 */
#define ADC0_BUFFER_LENGTH ADC0_CHANNEL_LENGTH
#define ADC1_BUFFER_LENGTH 2048

extern uint16_t adc0_data[ADC0_BUFFER_LENGTH];
extern uint16_t adc1_data[ADC1_BUFFER_LENGTH];

void adc_config();
#endif // ADC_H
