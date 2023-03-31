#include "st7789.h"

#ifdef LCD_SOFT_SPI
#define LCD_SCLK_Clr() PBout(10) = 0 // SCL=SCLK
#define LCD_SCLK_Set() PBout(10) = 1

#define LCD_MOSI_Clr() PBout(15) = 0 // SDA=MOSI
#define LCD_MOSI_Set() PBout(15) = 1

void st7789_write_bus(uint8_t data)
{
    uint8_t i;
    for (i = 0; i < 8; i++) {
        LCD_SCLK_Clr();
        if (data & 0x80) {
            LCD_MOSI_Set();
        } else {
            LCD_MOSI_Clr();
        }
        LCD_SCLK_Set();
        data <<= 1;
    }
}
#endif
void st7789_transmit_data8(uint8_t data)
{
    volatile uint16_t tmp = 16;
    LCD_CS_Clr();
#ifdef LCD_SOFT_SPI
    st7789_write_bus(data);
#else
    while (spi_i2s_flag_get(LCD_SPI, SPI_FLAG_TBE) == RESET) {}; // 检查发送空标志位
    spi_i2s_data_transmit(LCD_SPI, data);
    while (tmp--) {
    }
    // spi_i2s_data_receive(LCD_SPI);
    // while (spi_i2s_flag_get(LCD_SPI, SPI_FLAG_TBE) == RESET) {}; // 检查发送空标志位
#endif
    LCD_CS_Set();
}

void st7789_transmit_data16(uint16_t data)
{
    st7789_transmit_data8(data >> 8);
    st7789_transmit_data8(data);
}

void st7789_transmit_cmd(uint8_t data)
{
    LCD_DC_Clr(); // 传输命令
    st7789_transmit_data8(data);
    LCD_DC_Set(); // 传输数据
}
/**
 * @brief 设置起始和结束位置
 *
 * @param x1 列起始地址
 * @param y1 行起始地址
 * @param x2 列结束地址
 * @param y2 行结束地址
 */
void st7789_set_address(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    if (USE_HORIZONTAL == 0) {
        st7789_transmit_cmd(0x2a); // 列地址设置
        st7789_transmit_data16(x1);
        st7789_transmit_data16(x2);
        st7789_transmit_cmd(0x2b); // 行地址设置
        st7789_transmit_data16(y1);
        st7789_transmit_data16(y2);
        st7789_transmit_cmd(0x2c); // 存储器写
    } else if (USE_HORIZONTAL == 1) {
        st7789_transmit_cmd(0x2a); // 列地址设置
        st7789_transmit_data16(x1);
        st7789_transmit_data16(x2);
        st7789_transmit_cmd(0x2b); // 行地址设置
        st7789_transmit_data16(y1 + 80);
        st7789_transmit_data16(y2 + 80);
        st7789_transmit_cmd(0x2c); // 存储器写
    } else if (USE_HORIZONTAL == 2) {
        st7789_transmit_cmd(0x2a); // 列地址设置
        st7789_transmit_data16(x1);
        st7789_transmit_data16(x2);
        st7789_transmit_cmd(0x2b); // 行地址设置
        st7789_transmit_data16(y1);
        st7789_transmit_data16(y2);
        st7789_transmit_cmd(0x2c); // 存储器写
    } else {
        st7789_transmit_cmd(0x2a); // 列地址设置
        st7789_transmit_data16(x1 + 80);
        st7789_transmit_data16(x2 + 80);
        st7789_transmit_cmd(0x2b); // 行地址设置
        st7789_transmit_data16(y1);
        st7789_transmit_data16(y2);
        st7789_transmit_cmd(0x2c); // 存储器写
    }
}
