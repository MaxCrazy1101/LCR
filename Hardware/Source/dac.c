//
// Created by Captain.L on 2023/3/17.
//

#include "dac.h"

void dac_config(void)
{
    /* 打开外设时钟 */
    rcu_periph_clock_enable(RCU_DAC);

    /* 配置DAC0 */
    dac_deinit();
    dac_trigger_source_config(DAC0, DAC_TRIGGER_T5_TRGO); // 配置触发源Timer5_TRGO
    dac_trigger_enable(DAC0);                             // 使能外部触发
    dac_wave_mode_config(DAC0, DAC_WAVE_DISABLE);         // 不使用波形发生器
    dac_output_buffer_enable(DAC0);                       // 使能输出缓冲区

    /* 开启DAC */
    dac_enable(DAC0);     // DAC0使能
    dac_dma_enable(DAC0); // DAC0的DMA功能使能
}
