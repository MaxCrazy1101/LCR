#include "bsp_usart.h"
#include "stdio.h"

void usart_gpio_config()
{
    // 端口时钟
    rcu_periph_clock_enable(BSP_USART_RCU);    // 开启串口时钟
    rcu_periph_clock_enable(BSP_USART_TX_RCU); // 开启端口时钟
    rcu_periph_clock_enable(BSP_USART_RX_RCU); // 开启端口时钟

    // 端口复用
    gpio_af_set(BSP_USART_TX_PORT, BSP_USART_AF, BSP_USART_TX_PIN);
    gpio_af_set(BSP_USART_RX_PORT, BSP_USART_AF, BSP_USART_RX_PIN);

    // 配置引脚模式
    /* 配置TX为复用模式 上拉模式 */
    gpio_mode_set(BSP_USART_TX_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, BSP_USART_TX_PIN);
    /* 配置RX为复用模式 上拉模式 */
    gpio_mode_set(BSP_USART_RX_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, BSP_USART_RX_PIN);
    /* 配置TX为推挽输出 50MHZ */
    gpio_output_options_set(BSP_USART_TX_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, BSP_USART_TX_PIN);
    /* 配置RX为推挽输出 50MHZ */
    gpio_output_options_set(BSP_USART_RX_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, BSP_USART_RX_PIN);

    /* 配置串口的参数 */
    usart_deinit(BSP_USART);                         // 复位串口
    usart_baudrate_set(BSP_USART, 115200U);          // 设置波特率
    usart_parity_config(BSP_USART, USART_PM_NONE);   // 没有校验位
    usart_word_length_set(BSP_USART, USART_WL_8BIT); // 8位数据位
    usart_stop_bit_set(BSP_USART, USART_STB_1BIT);   // 1位停止位
    /* 使能串口 */
    usart_transmit_config(BSP_USART, USART_TRANSMIT_ENABLE); // 使能串口发送
    usart_receive_config(BSP_USART, USART_RECEIVE_ENABLE);   // 使能串口接收
    usart_enable(BSP_USART);                                 // 使能串口
}

void usart_send_data(uint8_t ucch)
{
    usart_data_transmit(BSP_USART, (uint8_t)ucch);
    while (RESET == usart_flag_get(BSP_USART, USART_FLAG_TBE))
        ; // 等待发送数据缓冲区标志置位
}

uint8_t usart_receive_data()
{
    return usart_data_receive(BSP_USART);
}

void usart_send_String(uint8_t *ucstr)
{
    while (ucstr && *ucstr) // 地址为空或者值为空跳出
    {
        usart_send_data(*ucstr++);
    }
}

/**
 * 串口重定向
 * @param ch
 * @param f
 * @return
 */
int fputc(int ch, FILE *f)
{
    usart_data_transmit(BSP_USART, (uint8_t)ch);
    while (RESET == usart_flag_get(BSP_USART, USART_FLAG_TBE))
        ;
    return ch;
}