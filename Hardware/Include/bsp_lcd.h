#ifndef BSP_LCD_H
#define BSP_LCD_H
#ifdef __cplusplus
extern "C" {
#endif
#include "st7789.h"

// 定义显示屏长宽
#define LCD_W 240
#define LCD_H 240

// »­±ÊÑÕÉ«
#define WHITE      0xFFFF
#define BLACK      0x0000
#define BLUE       0x001F
#define BRED       0XF81F
#define GRED       0XFFE0
#define GBLUE      0X07FF
#define RED        0xF800
#define MAGENTA    0xF81F
#define GREEN      0x07E0
#define CYAN       0x7FFF
#define YELLOW     0xFFE0
#define BROWN      0XBC40 // ×ØÉ«
#define BRRED      0XFC07 // ×ØºìÉ«
#define GRAY       0X8430 // »ÒÉ«
#define DARKBLUE   0X01CF // ÉîÀ¶É«
#define LIGHTBLUE  0X7D7C // Ç³À¶É«
#define GRAYBLUE   0X5458 // »ÒÀ¶É«
#define LIGHTGREEN 0X841F // Ç³ÂÌÉ«
#define LGRAY      0XC618 // Ç³»ÒÉ«(PANNEL),´°Ìå±³¾°É«
#define LGRAYBLUE  0XA651 // Ç³»ÒÀ¶É«(ÖÐ¼ä²ãÑÕÉ«)
#define LBBLUE     0X2B12 // Ç³×ØÀ¶É«(Ñ¡ÔñÌõÄ¿µÄ·´É«)

void LCD_Init(void); // LCD初始化
/* 启动dma */
void lcd_dma_enable(uint16_t *color_p, uint32_t size);
void LCD_Fill(uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend,
              uint16_t color);                              // 指定区域填充颜色
void LCD_DrawPoint(uint16_t x, uint16_t y, uint16_t color); // 指定位置画一个点

#ifdef __cplusplus
}
#endif
#endif /* BSP_LCD_H */