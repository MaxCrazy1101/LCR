#ifndef _BSP_USART_H
#define _BSP_USART_H

#include "gd32f4xx.h"
#include "systick.h"

#define BSP_USART         USART0

#define BSP_USART_RCU     RCU_USART0 // usart0 时钟
#define BSP_USART_TX_RCU  RCU_GPIOA  // tx引脚端口
#define BSP_USART_RX_RCU  RCU_GPIOA  // rx引脚端口
#define BSP_USART_TX_PORT GPIOA
#define BSP_USART_TX_PIN  GPIO_PIN_9
#define BSP_USART_RX_PORT GPIOA
#define BSP_USART_RX_PIN  GPIO_PIN_10
#define BSP_USART_AF      GPIO_AF_7 // 串口是引脚复用功能7

void usart_gpio_config(void);           // led gpio引脚配置
void usart_send_data(uint8_t ucch);     // 使用[BSP_USART]发送一个字符
uint8_t usart_receive_data();     // 使用[BSP_USART]接收一个字符
void usart_send_String(uint8_t *ucstr); // 使用]BSP_USART]发送一个字符串

#endif /* _BSP_USART_H */