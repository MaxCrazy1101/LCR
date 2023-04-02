#include "dma.h"
#include "adc.h"
const uint16_t SinWaveTable[100] = {0x800, 0x880, 0x900, 0x97f, 0x9fd, 0xa78, 0xaf1, 0xb67, 0xbda, 0xc49, 0xcb3, 0xd19, 0xd79, 0xdd4,
                                    0xe2a, 0xe78, 0xec1, 0xf02, 0xf3d, 0xf70, 0xf9b, 0xfbf, 0xfdb, 0xfef, 0xffb, 0xfff, 0xffb, 0xfef,
                                    0xfdb, 0xfbf, 0xf9b, 0xf70, 0xf3d, 0xf02, 0xec1, 0xe78, 0xe2a, 0xdd4, 0xd79, 0xd19, 0xcb3, 0xc49,
                                    0xbda, 0xb67, 0xaf1, 0xa78, 0x9fd, 0x97f, 0x900, 0x880, 0x7ff, 0x77f, 0x6ff, 0x680, 0x602, 0x587,
                                    0x50e, 0x498, 0x425, 0x3b6, 0x34c, 0x2e6, 0x286, 0x22b, 0x1d5, 0x187, 0x13e, 0xfd, 0xc2, 0x8f,
                                    0x64, 0x40, 0x24, 0x10, 0x4, 0x0, 0x4, 0x10, 0x24, 0x40, 0x64, 0x8f, 0xc2, 0xfd, 0x13e, 0x187,
                                    0x1d5, 0x22b, 0x286, 0x2e6, 0x34c, 0x3b6, 0x425, 0x498, 0x50e, 0x587, 0x602, 0x680, 0x6ff, 0x77f};

void dma_config()
{
    /* 开启DMA时钟 */
    rcu_periph_clock_enable(RCU_DMA0);
    rcu_periph_clock_enable(RCU_DMA1);

    /* DMA中断配置 */
    dma_single_data_parameter_struct dma_struct;
    /* 清空中断标志位 */

    dma_flag_clear(DMA0, DMA_CH4, DMA_INTF_FEEIF);
    dma_flag_clear(DMA0, DMA_CH4, DMA_INTF_SDEIF);
    dma_flag_clear(DMA0, DMA_CH4, DMA_INTF_TAEIF);
    dma_flag_clear(DMA0, DMA_CH4, DMA_INTF_HTFIF);
    dma_flag_clear(DMA0, DMA_CH4, DMA_INTF_FTFIF);

    /* 配置 DMA0 channel 4 LCD_SPI*/
    dma_channel_subperipheral_select(DMA0, DMA_CH4, DMA_SUBPERI0);
    dma_struct.periph_addr = (uint32_t)&SPI_DATA(SPI1); // 外设地址 SPI1 data register
    // dma_struct.memory0_addr        =;//暂不设置传输地址
    dma_struct.direction = DMA_MEMORY_TO_PERIPH;
    // dma_struct.number              = 100;//传输数量留空
    dma_struct.periph_inc          = DMA_PERIPH_INCREASE_DISABLE;
    dma_struct.memory_inc          = DMA_MEMORY_INCREASE_ENABLE; // 内存地址自加
    dma_struct.periph_memory_width = DMA_PERIPH_WIDTH_8BIT;      // 位宽
    dma_struct.priority            = DMA_PRIORITY_LOW;           // 优先级最高
    dma_struct.circular_mode       = DMA_CIRCULAR_MODE_DISABLE;  // 失能循环模式
    dma_single_data_mode_init(DMA0, DMA_CH4, &dma_struct);
    nvic_irq_enable(DMA0_Channel4_IRQn, 9, 0); // 设置中断优先级
    // dma_channel_enable(DMA0, DMA_CH4);//暂不开启

    /* 配置 DMA0 channel 5  DAC*/
    dma_deinit(DMA0, DMA_CH5);
    dma_flag_clear(DMA0, DMA_CH5, DMA_INTF_FEEIF);
    dma_flag_clear(DMA0, DMA_CH5, DMA_INTF_SDEIF);
    dma_flag_clear(DMA0, DMA_CH5, DMA_INTF_TAEIF);
    dma_flag_clear(DMA0, DMA_CH5, DMA_INTF_HTFIF);
    dma_flag_clear(DMA0, DMA_CH5, DMA_INTF_FTFIF);

    dma_channel_subperipheral_select(DMA0, DMA_CH5, DMA_SUBPERI7);
    dma_struct.periph_addr         = 0x40007408; // 外设地址 DAC0右对齐12位保持寄存器
    dma_struct.memory0_addr        = (uint32_t)SinWaveTable;
    dma_struct.direction           = DMA_MEMORY_TO_PERIPH;
    dma_struct.number              = 100;
    dma_struct.periph_inc          = DMA_PERIPH_INCREASE_DISABLE;
    dma_struct.memory_inc          = DMA_MEMORY_INCREASE_ENABLE; // 内存地址自加
    dma_struct.periph_memory_width = DMA_PERIPH_WIDTH_16BIT;     // 位宽半字
    dma_struct.priority            = DMA_PRIORITY_ULTRA_HIGH;    // 优先级最高
    dma_struct.circular_mode       = DMA_CIRCULAR_MODE_ENABLE;   // 使能循环模式
    dma_single_data_mode_init(DMA0, DMA_CH5, &dma_struct);

    dma_channel_enable(DMA0, DMA_CH5);

    /* 配置 DMA1 Channel 0 */
    dma_deinit(DMA1, DMA_CH0);

    /* 清空中断标志位 */
    dma_flag_clear(DMA1, DMA_CH0, DMA_INTF_FEEIF);
    dma_flag_clear(DMA1, DMA_CH0, DMA_INTF_SDEIF);
    dma_flag_clear(DMA1, DMA_CH0, DMA_INTF_TAEIF);
    dma_flag_clear(DMA1, DMA_CH0, DMA_INTF_HTFIF);
    dma_flag_clear(DMA1, DMA_CH0, DMA_INTF_FTFIF);

    /* enable DMA circulation mode */
    dma_circulation_enable(DMA1, DMA_CH0);

    dma_channel_subperipheral_select(DMA1, DMA_CH0, DMA_SUBPERI0);
    dma_struct.periph_addr         = (uint32_t)(&ADC_RDATA(ADC0)); // 外设地址 ADC0右对齐12位输出寄存器
    dma_struct.memory0_addr        = (uint32_t)adc0_data;
    dma_struct.direction           = DMA_PERIPH_TO_MEMORY;        // 方向外设-->内存
    dma_struct.number              = ADC0_CHANNEL_LENGTH;         // DMA通道数据传输数
    dma_struct.periph_inc          = DMA_PERIPH_INCREASE_DISABLE; // 外设地址不变
    dma_struct.memory_inc          = DMA_MEMORY_INCREASE_ENABLE;  // 内存地址自加
    dma_struct.periph_memory_width = DMA_PERIPH_WIDTH_16BIT;      // 位宽半字
    dma_struct.priority            = DMA_PRIORITY_LOW;            // 优先级最低
    dma_struct.circular_mode       = DMA_CIRCULAR_MODE_ENABLE;    // 使能循环模式
    dma_single_data_mode_init(DMA1, DMA_CH0, &dma_struct);
    dma_channel_subperipheral_select(DMA1, DMA_CH0, DMA_SUBPERI0);

    dma_channel_enable(DMA1, DMA_CH0);

    /* 配置 DMA1 Channel 3 */
    /* ADC1 位于ch3 peri1 */

    /* 清空中断标志位 */
    dma_flag_clear(DMA1, DMA_CH3, DMA_INTF_FEEIF);
    dma_flag_clear(DMA1, DMA_CH3, DMA_INTF_SDEIF);
    dma_flag_clear(DMA1, DMA_CH3, DMA_INTF_TAEIF);
    dma_flag_clear(DMA1, DMA_CH3, DMA_INTF_HTFIF);
    dma_flag_clear(DMA1, DMA_CH3, DMA_INTF_FTFIF);

    dma_channel_subperipheral_select(DMA1, DMA_CH3, DMA_SUBPERI1);
    dma_struct.periph_addr         = (uint32_t)(&ADC_RDATA(ADC1)); // 外设地址 ADC0右对齐12位输出寄存器
    dma_struct.memory0_addr        = (uint32_t)adc1_data;
    dma_struct.direction           = DMA_PERIPH_TO_MEMORY;
    dma_struct.number              = ADC1_BUFFER_LENGTH;
    dma_struct.periph_inc          = DMA_PERIPH_INCREASE_DISABLE; // 外设地址不变
    dma_struct.memory_inc          = DMA_MEMORY_INCREASE_ENABLE;  // 内存地址自加
    dma_struct.periph_memory_width = DMA_PERIPH_WIDTH_16BIT;      // 位宽半字
    dma_struct.priority            = DMA_PRIORITY_ULTRA_HIGH;     // 优先级最高
    dma_struct.circular_mode       = DMA_CIRCULAR_MODE_ENABLE;    // 使能循环模式
    dma_single_data_mode_init(DMA1, DMA_CH3, &dma_struct);
    /* 配置ADC1采样中断 */
    nvic_irq_enable(DMA1_Channel3_IRQn, 14, 0);
    dma_interrupt_enable(DMA1, DMA_CH3, DMA_CHXCTL_FTFIE);

    dma_channel_enable(DMA1, DMA_CH3);
}
