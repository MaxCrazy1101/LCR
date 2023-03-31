#include "bsp_lcd.h"

#define LCD_TOTAL_BUF_SIZE (LCD_H * LCD_W * 2)
#define LCD_Buf_Size       1152
static __attribute__((section("EXTSDRAM"))) uint8_t lcd_buf[LCD_Buf_Size];

#define lcd_delay(n) delay_1ms(n)

void LCD_Init(void)
{
#ifdef LCD_SOFT_SPI
    rcu_periph_clock_enable(RCU_GPIOB);
    uint32_t config_pin = GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_15;
    gpio_mode_set(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, config_pin);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, config_pin);
    gpio_bit_set(GPIOB, GPIO_PIN_10);
    gpio_bit_set(GPIOB, GPIO_PIN_11);
    gpio_bit_set(GPIOB, GPIO_PIN_12);
    gpio_bit_set(GPIOB, GPIO_PIN_13);
    gpio_bit_set(GPIOB, GPIO_PIN_15);
#endif
    lcd_delay(1000);
    LCD_DC_Set();

    LCD_RES_Clr(); // 重置LCD
    lcd_delay(100);
    LCD_RES_Set();
    lcd_delay(100);
    LCD_BLK_Set(); // 打开LCD背光
    lcd_delay(100);
    /* 关闭睡眠模式 */
    st7789_transmit_cmd(ST7789_SLPOUT);
    lcd_delay(120);

    /* 开始设置显存扫描模式，数据格式等 */
    st7789_transmit_cmd(ST7789_MADCTL);
    if (USE_HORIZONTAL == 0)
        st7789_transmit_data8(0x00);
    else if (USE_HORIZONTAL == 1)
        st7789_transmit_data8(0xC0);
    else if (USE_HORIZONTAL == 2)
        st7789_transmit_data8(0x70);
    else
        st7789_transmit_data8(0xA0);
    /* RGB 5-6-5-bit格式  */
    st7789_transmit_cmd(ST7789_COLMOD);
    st7789_transmit_data8(0x65);
    /* porch 设置 */
    st7789_transmit_cmd(0xB2);
    st7789_transmit_data8(0x0C);
    st7789_transmit_data8(0x0C);
    st7789_transmit_data8(0x00);
    st7789_transmit_data8(0x33);
    st7789_transmit_data8(0x33);
    /* VGH设置 */
    st7789_transmit_cmd(0xB7);
    st7789_transmit_data8(0x72);
    /* VCOM 设置 */
    st7789_transmit_cmd(0xBB);
    st7789_transmit_data8(0x3D);
    /* LCM 设置 */
    st7789_transmit_cmd(0xC0);
    st7789_transmit_data8(0x2C);
    /* VDV and VRH 设置 */
    st7789_transmit_cmd(0xC2);
    st7789_transmit_data8(0x01);
    /* VRH 设置 */
    st7789_transmit_cmd(0xC3);
    st7789_transmit_data8(0x19);
    /* VDV 设置 */
    st7789_transmit_cmd(0xC4);
    st7789_transmit_data8(0x20);
    /* 普通模式下显存速率设置 60Mhz */
    st7789_transmit_cmd(0xC6);
    st7789_transmit_data8(0x0F);
    /* 电源控制 */
    st7789_transmit_cmd(0xD0);
    st7789_transmit_data8(0xA4);
    st7789_transmit_data8(0xA1);
    /* 电压设置 */
    st7789_transmit_cmd(0xE0);
    st7789_transmit_data8(0xD0);
    st7789_transmit_data8(0x04);
    st7789_transmit_data8(0x0D);
    st7789_transmit_data8(0x11);
    st7789_transmit_data8(0x13);
    st7789_transmit_data8(0x2B);
    st7789_transmit_data8(0x3F);
    st7789_transmit_data8(0x54);
    st7789_transmit_data8(0x4C);
    st7789_transmit_data8(0x18);
    st7789_transmit_data8(0x0D);
    st7789_transmit_data8(0x0B);
    st7789_transmit_data8(0x1F);
    st7789_transmit_data8(0x23);
    /* 电压设置 */
    st7789_transmit_cmd(0xE1);
    st7789_transmit_data8(0xD0);
    st7789_transmit_data8(0x04);
    st7789_transmit_data8(0x0C);
    st7789_transmit_data8(0x11);
    st7789_transmit_data8(0x13);
    st7789_transmit_data8(0x2C);
    st7789_transmit_data8(0x3F);
    st7789_transmit_data8(0x44);
    st7789_transmit_data8(0x51);
    st7789_transmit_data8(0x2F);
    st7789_transmit_data8(0x1F);
    st7789_transmit_data8(0x1F);
    st7789_transmit_data8(0x20);
    st7789_transmit_data8(0x23);
    /* 显示开 */
    st7789_transmit_cmd(0x21);
    st7789_transmit_cmd(0x29);
}
/******************************************************************************
函数说明:在指定区域填充颜色入口数据:
 xsta,ysta 起始坐标
 xend, yend 终止坐标
color 要填充的颜色
返回值: 无

******************************************************************************/
void LCD_Fill(uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend, uint16_t color)
{
#ifdef LCD_SOFT_SPI
    uint16_t i, j;
    st7789_set_address(xsta, ysta, xend - 1, yend - 1);
    for (i = ysta; i < yend; i++) {
        for (j = xsta; j < xend; j++) {
            st7789_transmit_data16(color);
        }
    }
#else
    // uint16_t i, j;
    // uint8_t data[2] = {0}; // color是16bit的，每个像素点需要两个字节的显存

    // /* 将16bit的color值分开为两个单独的字节 */
    // data[0] = color >> 8;
    // data[1] = color;

    // /* 显存的值需要逐字节写入 */
    // for (j = 0; j < LCD_Buf_Size / 2; j++) {
    //     lcd_buf[j * 2]     = data[0];
    //     lcd_buf[j * 2 + 1] = data[1];
    // }
    // /* 指定显存操作地址为全屏幕 */
    // st7789_set_address(0, 0, LCD_W - 1, LCD_H - 1);
    // /* 指定接下来的数据为数据 */
    // /* 将显存缓冲区的数据全部写入缓冲区 */
    // for (i = 0; i < (LCD_TOTAL_BUF_SIZE / LCD_Buf_Size); i++) {
    //     for (size_t j = 0; j < LCD_Buf_Size; j++) {
    //         st7789_transmit_data8(lcd_buf[j]);
    //     }
    // }
    uint16_t i, j;
    st7789_set_address(xsta, ysta, xend - 1, yend - 1);
    for (i = ysta; i < yend; i++) {
        for (j = xsta; j < xend; j++) {
            st7789_transmit_data16(color);
        }
    }
#endif
}

void LCD_DrawPoint(uint16_t x, uint16_t y, uint16_t color)
{
    st7789_set_address(x, y, x, y); // 设置地址
    st7789_transmit_data16(color);
}

void lcd_dma_enable(uint16_t *color_p, uint32_t size)
{
    dma_memory_address_config(DMA0, DMA_CH4, DMA_MEMORY_0, (uint32_t)color_p);
    dma_transfer_number_config(DMA0, DMA_CH4, size);
    dma_interrupt_enable(DMA0, DMA_CH4, DMA_CHXCTL_FTFIE); // 开启中断
    dma_channel_enable(DMA0, DMA_CH4);
}