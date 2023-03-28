#include "spi.h"

void bsp_spi_config()
{
    /* 开启外设时钟 */
    rcu_periph_clock_enable(RCU_SPI4);

    /* 配置SPI1 */
    rcu_periph_clock_enable(RCU_GPIOB);

    // GPIO复用设置
    // SPI 除了CS 引脚不需要上拉。
    // CS引脚已经在外部电路硬件上拉
    {
        /* PB10 CLK | PB15 MOSI */
        uint32_t config_pin = GPIO_PIN_10 | GPIO_PIN_15;
        gpio_af_set(GPIOB, GPIO_AF_5, config_pin); // 复用spi1
        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, config_pin);
        gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, config_pin);
        /* PB11 LCD_RES| PB12 LCD_DC | PB13 LCD_BLK */
        config_pin = GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13;
        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, config_pin);
        gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, config_pin);
    }
    /* 配置SPI1 */
    {
        spi_i2s_deinit(SPI1);
        spi_parameter_struct spi_init_struct;
        spi_init_struct.trans_mode           = SPI_TRANSMODE_BDTRANSMIT; // 工作在只发送模式
        spi_init_struct.device_mode          = SPI_MASTER;               // 主机模式
        spi_init_struct.frame_size           = SPI_FRAMESIZE_8BIT;       // 8bit帧结构
        spi_init_struct.clock_polarity_phase = SPI_CK_PL_HIGH_PH_2EDGE;  // 空闲时clk高 第二个边沿捕获
        spi_init_struct.nss                  = SPI_NSS_SOFT;             // NSS信号软件管理
        spi_init_struct.prescale             = SPI_PSC_8;                // 预分频
        spi_init_struct.endian               = SPI_ENDIAN_MSB;           // 高位先行
        spi_init(SPI1, &spi_init_struct);
    }
    // 开启SPI4
    // TODO: dma配置
    spi_nss_output_enable(SPI1);
    spi_enable(SPI1);
}