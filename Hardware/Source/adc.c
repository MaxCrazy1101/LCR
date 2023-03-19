#include "adc.h"
#include "systick.h"
uint16_t adc0_data[ADC0_CHANNEL_LENGTH];
uint16_t adc1_data[1024];
void adc0_config();
void adc1_config();
void adc_config()
{
    /* ADC 时钟来源配置 240/6=40MHz */
    adc_clock_config(ADC_ADCCK_HCLK_DIV6);
    // rcu_periph_clock_enable(RCU_ADC2);
    /* 复位ADC */
    adc_deinit();

    adc_sync_mode_config(ADC_SYNC_MODE_INDEPENDENT); // ADC独立工作模式

    /* ADC0配置 用于温度和电池电压检测*/
    adc0_config();

    /* ADC1配置 用于高速采样信号 */
    adc1_config();
}

void adc0_config()
{
    /* 开启外设时钟 */
    rcu_periph_clock_enable(RCU_ADC0);

    /* ADC contineous function disable */
    adc_special_function_config(ADC0, ADC_CONTINUOUS_MODE, DISABLE);
    /* ADC scan mode enable */
    adc_special_function_config(ADC0, ADC_SCAN_MODE, ENABLE);

    /* ADC data alignment config */
    adc_data_alignment_config(ADC0, ADC_DATAALIGN_RIGHT);
    /* 配置精度 12bit */
    adc_resolution_config(ADC0, ADC_RESOLUTION_12B);

    /* ADC channel length config */
    adc_channel_length_config(ADC0, ADC_ROUTINE_CHANNEL, ADC0_CHANNEL_LENGTH);
    /* ADC routine channel config */
    adc_routine_channel_config(ADC0, 0, ADC_CHANNEL_16, ADC_SAMPLETIME_56);
    adc_routine_channel_config(ADC0, 1, ADC_CHANNEL_17, ADC_SAMPLETIME_56);
    // adc_routine_channel_config(ADC0, 2, ADC_CHANNEL_18, ADC_SAMPLETIME_15);

    /* ADC trigger config */
    adc_external_trigger_config(ADC0, ADC_ROUTINE_CHANNEL, EXTERNAL_TRIGGER_RISING); // 外部上升沿触发
    adc_external_trigger_source_config(ADC0, ADC_ROUTINE_CHANNEL, ADC_EXTTRIG_ROUTINE_T2_TRGO);

    /* 只有adc0有通道16-18 */
    /* ADC temperature and Vref enable */
    adc_channel_16_to_18(ADC_TEMP_VREF_CHANNEL_SWITCH, ENABLE);
    /* ADC Vbat channel disable */
    adc_channel_16_to_18(ADC_VBAT_CHANNEL_SWITCH, DISABLE);

    /* ADC DMA 功能使能 */
    adc_dma_request_after_last_enable(ADC0); // 当DMA=1时，在每个规则通道转换结束后提出一个DMA请求
    adc_dma_mode_enable(ADC0);

    /* enable ADC interface */
    adc_enable(ADC0);
    /* wait for ADC stability */
    delay_1ms(1);
    /* ADC0 自动校准 */
    adc_calibration_enable(ADC0);

    /* 不启用ADC0软件触发 */
    // adc_software_trigger_enable(ADC0, ADC_ROUTINE_CHANNEL);
}

void adc1_config()
{
    rcu_periph_clock_enable(RCU_ADC1);

    /* ADC 连续转换模式失能 */
    adc_special_function_config(ADC1, ADC_CONTINUOUS_MODE, DISABLE);

    /* ADC 数据对齐方式配置 */
    adc_data_alignment_config(ADC1, ADC_DATAALIGN_RIGHT);
    /* 配置精度12bit */
    adc_resolution_config(ADC1, ADC_RESOLUTION_12B);

    /* ADC 常规转换通道配置 */
    adc_channel_length_config(ADC1, ADC_ROUTINE_CHANNEL, 1);
    adc_routine_channel_config(ADC1, 0, ADC_CHANNEL_15, ADC_SAMPLETIME_56);

    /* ADC 外部触发配置 */
    adc_external_trigger_config(ADC1, ADC_ROUTINE_CHANNEL, EXTERNAL_TRIGGER_RISING); // 常规序列外部上升沿触发
    /* ADC 外部触发源配置 */
    adc_external_trigger_source_config(ADC1, ADC_ROUTINE_CHANNEL, ADC_EXTTRIG_ROUTINE_T3_CH3); // 常规序列Timer3 Channel3触发
    /* ADC DMA模式使能 */
    adc_dma_request_after_last_enable(ADC1); // FIXME: 不确定是否需要
    adc_dma_mode_enable(ADC1);

    /* enable ADC interface */
    adc_enable(ADC1);
    delay_1ms(1);

    /* ADC校准 */
    adc_calibration_enable(ADC1);

    // /* ADC 中断使能 */
    // adc_interrupt_flag_clear(ADC1, ADC_INT_FLAG_EOC);
    // adc_interrupt_enable(ADC1, ADC_INT_EOC);

    /* 使能 ADC 软件触发 */
    //    adc_software_trigger_enable(ADC1, ADC_ROUTINE_CHANNEL);
}
