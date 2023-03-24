#include "gpio.h"

#include "gd32f4xx_direct_io.h"
void gpio_config()
{
    /* 开启GPIO时钟 */
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_GPIOD);
    rcu_periph_clock_enable(RCU_GPIOE);
    rcu_periph_clock_enable(RCU_GPIOF);
    rcu_periph_clock_enable(RCU_GPIOG);

    /* GPIO 默认输出设置 */
    PDout(7) = 0;
    PEout(3) = 0;
    /* GPIO 引脚功能设置 */

    /* DAC引脚配置 PA4 */
    /* once enabled the DAC, the corresponding GPIO pin is connected to the DAC converter automatically */
    gpio_mode_set(GPIOA, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_PIN_4);

    /* ADC引脚配置 PC5 */
    gpio_mode_set(GPIOC, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_PIN_5);

    /* LED 引脚配置 */
    /* 配置为输出模式 浮空模式 */
    gpio_mode_set(PORT_LED1, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, PIN_LED1);
    gpio_mode_set(PORT_LED2, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, PIN_LED2);
    gpio_mode_set(PORT_LED3, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, PIN_LED3);
    gpio_mode_set(PORT_LED4, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, PIN_LED4);
    /* 配置为推挽输出 50MHZ */
    gpio_output_options_set(PORT_LED1, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, PIN_LED1);
    gpio_output_options_set(PORT_LED2, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, PIN_LED2);
    gpio_output_options_set(PORT_LED3, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, PIN_LED3);
    gpio_output_options_set(PORT_LED4, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, PIN_LED4);

    /* 按键 引脚配置 下拉输入*/
    gpio_mode_set(BSP_KEY_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLDOWN, BSP_KEY_PIN); // 默认低电平 下拉
    /* 使能NVIC中断 中断分组为2位抢占优先级，2位子优先级 */
    // nvic_irq_enable(EXTI0_IRQn, 3U, 3U); // 抢占优先级3，子优先级3
    // /* 连接中断线到GPIO */
    // syscfg_exti_line_config(EXTI_SOURCE_GPIOA, EXTI_SOURCE_PIN0);
    // /* 初始化中断线 */
    // exti_init(EXTI_0, EXTI_INTERRUPT, EXTI_TRIG_BOTH);
    // /* 使能中断 */
    // exti_interrupt_enable(EXTI_0);
    // /* 清除中断标志位 */
    // exti_interrupt_flag_clear(EXTI_0);
}