#include "pga113.h"
#include "stdio.h"
// 定义增益数组
// 记住写指令的 十六进制 表示：0x2a00（0x0010 1010 0000 0000），
// 0010 1010: 表示 写(write)模式；
// 第一个0000: 表示增益放大倍数；
// 第二个0000: 表示选择的通道数
uint16_t gainBuffer[8] = {0x2a00, 0x2a10, 0x2a20, 0x2a30,
                          0x2a40, 0x2a50, 0x2a60, 0x2a70};
// 分别对应系统放大:
// 对应数组下标：0, 1, 2, 3, 4, 5,  6,  7
//   二进制增益：1, 2, 4, 8,16,32, 64,128 PGA112
//	   增益范围：1, 2, 5,10,20,50,100,200 PGA113

void pga11x_config()
{

    /* 开启外设时钟 */
    rcu_periph_clock_enable(RCU_SPI2);

    /* 配置SPI2 */
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOB);

    /* GPIO复用设置
     * SPI2 NSS | PA15
     * SPI2 CLK | PB3
     * SPI2 MOSI| PB5
     */
    {
        // Initialize Pin Output
        PAout(15) = 1;
        PBout(3)  = 0;
        PBout(5)  = 0;
        /* PB3 CLK | PB5 MOSI */
        uint32_t config_pin  = GPIO_PIN_3 | GPIO_PIN_5;
        uint32_t config_port = GPIOB;
        gpio_af_set(config_port, GPIO_AF_6, config_pin); // 复用SPI2
        gpio_mode_set(config_port, GPIO_MODE_AF, GPIO_PUPD_NONE, config_pin);
        gpio_output_options_set(config_port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, config_pin);
        /* PA15 NSS */
        config_pin  = GPIO_PIN_15;
        config_port = GPIOA;
        gpio_af_set(config_port, GPIO_AF_6, config_pin); // 复用SPI2
        gpio_mode_set(config_port, GPIO_MODE_AF, GPIO_PUPD_NONE, config_pin);
        gpio_output_options_set(config_port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, config_pin);
        gpio_bit_set(config_port, config_pin);
    }
    /* 配置SPI2 */
    {
        spi_i2s_deinit(SPI2);
        spi_parameter_struct spi_init_struct;
        spi_init_struct.trans_mode           = SPI_TRANSMODE_BDTRANSMIT; // 工作在只发送模式
        spi_init_struct.device_mode          = SPI_MASTER;               // 主机模式
        spi_init_struct.frame_size           = SPI_FRAMESIZE_16BIT;      // 16bit帧结构
        spi_init_struct.clock_polarity_phase = SPI_CK_PL_LOW_PH_1EDGE;   // 空闲时clk低电平 第1个边沿捕获
        spi_init_struct.nss                  = SPI_NSS_SOFT;             // NSS信号软件管理
        spi_init_struct.prescale             = SPI_PSC_32;               // 预分频
        spi_init_struct.endian               = SPI_ENDIAN_MSB;           // 高位先行
        spi_init(SPI2, &spi_init_struct);
    }
    // 开启SPI2
    // spi_dma_enable(SPI2, SPI_DMA_TRANSMIT);
    spi_nss_output_enable(SPI2);
    spi_enable(SPI2);
}
// 定义函数控制增益放大倍数
void pga113_set_gain(uint16_t gain)
{
    __IO uint8_t tmp = 16;

    PAout(15) = 1;
    while (tmp--) {
    };
    tmp = 16;
    // spi_nss_internal_low(SPI2);
    PAout(15) = 0;

    spi_i2s_data_transmit(SPI2, gain);
    while (spi_i2s_flag_get(SPI2, SPI_FLAG_TBE) == RESET) { printf("Wait TBE\r\n"); };
    while (tmp--) {
    };
    // spi_nss_internal_high(SPI2);
    PAout(15) = 1;
}