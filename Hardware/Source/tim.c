/********************************************************************************
 * 文 件 名: bsp_basic_timer.c
 * 版 本 号: 初版
 * 修改作者: LC
 * 修改日期: 2022年04月18日
 * 功能介绍:
 ******************************************************************************
 * 注意事项:
 *********************************************************************************/

#include "tim.h"
#include "bsp_led.h"
#include "stdio.h"

void timer_clk_config()
{
    rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4); // 配置定时器时钟
}

/**
 * 配置Timer2
 * @param prescaler 时钟预分频值(-1会在函数内执行) 0-65535
 * @param period 自动重装载值(-1会在函数内执行)
 */
void tim2_config(uint16_t prescaler, uint16_t period)
{
    /* 一个周期的时间T = 1/f, 定时时间time = T * 周期
    设预分频值位pre,周期位per
    time = (prescaler + 1) * (period + 1) / psc_clk
    */
    timer_parameter_struct timere_initpara; // 定义定时器结构体
    /* 开启时钟 */
    rcu_periph_clock_enable(RCU_TIMER2);

    timer_deinit(TIMER2); // 复位定时器

    /* 配置定时器参数 */
    timere_initpara.prescaler        = prescaler - 1;      //  时钟预分频值 0-65535   psc_clk = CK_TIMER / prescaler
    timere_initpara.alignedmode      = TIMER_COUNTER_EDGE; // 边缘对齐
    timere_initpara.counterdirection = TIMER_COUNTER_UP;   // 向上计数
    timere_initpara.period           = period - 1;         // 周期

    /* 在输入捕获的时候使用  数字滤波器使用的采样频率之间的分频比例 */
    timere_initpara.clockdivision = TIMER_CKDIV_DIV1; // 分频因子

    /* 只有高级定时器才有 配置为x，就重复x+1次进入中断 */
    timere_initpara.repetitioncounter = 0; // 重复计数器 0-255

    timer_init(TIMER2, &timere_initpara); // 初始化定时器

    timer_autoreload_value_config(TIMER2, 0xFF);
    timer_auto_reload_shadow_enable(TIMER2);
    timer_master_output_trigger_source_select(TIMER2, TIMER_TRI_OUT_SRC_UPDATE); // 更新事件

    /* 无需中断 */
    /* 配置中断优先级 */
    //    nvic_irq_enable(BSP_TIMER_IRQ, 3, 2); // 设置中断优先级为 3,2
    /* 使能中断 */
    //    timer_interrupt_enable(BSP_TIMER, TIMER_INT_UP); // 使能更新事件中断
}
/**
 * @brief 使能 TIMER2 开始触发 ADC0
 *
 */
void tim2_enable()
{
    tim2_config(48000, 50000); // 10ms一次
    timer_enable(TIMER2);
}
/**
 * @brief 失能 TIMER2 停止触发 ADC0
 *
 */
void tim2_disable()
{
    timer_disable(TIMER2);
    rcu_periph_clock_disable(RCU_TIMER2);
}

/**
 * 配置Timer3
 * @param prescaler 时钟预分频值(-1会在函数内执行) 0-65535
 * @param period 自动重装载值(-1会在函数内执行)
 */
void tim3_config(uint16_t prescaler, uint16_t period)
{
    /* -----------------------------------------------------------------------
TIMER3 configuration: generate 3 PWM signals with 3 different duty cycles:
TIMER3CLK = SystemCoreClock / 200 = 1MHz

TIMER3 channel1 duty cycle = (4000/ 16000)* 100  = 25%
TIMER3 channel2 duty cycle = (8000/ 16000)* 100  = 50%
TIMER3 channel3 duty cycle = (12000/ 16000)* 100 = 75%
----------------------------------------------------------------------- */
    /* 一个周期的时间T = 1/f, 定时时间time = T * 周期
    设预分频值位pre,周期位per
    time = (prescaler + 1) * (period + 1) / psc_clk
    */
    timer_parameter_struct timere_initpara; // 定义定时器结构体
    timer_oc_parameter_struct timer_ocintpara;

    /* 开启时钟 */
    rcu_periph_clock_enable(RCU_TIMER3);

    /* CK_TIMERx = 4 x CK_APB1  = 4x60M = 240MHZ */
    rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4); // 配置定时器时钟倍频器

    timer_deinit(TIMER3); // 复位定时器

    /* 配置定时器参数 */
    timere_initpara.prescaler        = prescaler - 1;      //  时钟预分频值 0-65535   psc_clk = CK_TIMER / prescaler
    timere_initpara.alignedmode      = TIMER_COUNTER_EDGE; // 边缘对齐
    timere_initpara.counterdirection = TIMER_COUNTER_UP;   // 向上计数
    timere_initpara.period           = period - 1;         // 周期
    /* 在输入捕获的时候使用  数字滤波器使用的采样频率之间的分频比例 */
    timere_initpara.clockdivision = TIMER_CKDIV_DIV1; // 分频因子
    /* 只有高级定时器才有 配置为x，就重复x+1次进入中断 */
    timere_initpara.repetitioncounter = 0; // 重复计数器 0-255

    timer_init(TIMER3, &timere_initpara); // 初始化定时器

    /* PWM设置通道设置 注意对每个需要使用的通道都需要配置*/
    timer_ocintpara.ocpolarity   = TIMER_OC_POLARITY_HIGH;   // 通道输出极性TIMER_OC_POLARITY_HIGH,TIMER_OC_POLARITY_LOW
    timer_ocintpara.outputstate  = TIMER_CCX_ENABLE;         // 通道输出状态 TIMER_CCX_ENABLE, TIMER_CCX_DISABLE
    timer_ocintpara.ocnpolarity  = TIMER_OCN_POLARITY_HIGH;  // 互补通道输出极性TIMER_OCN_POLARITY_HIGH,TIMER_OCN_POLARITY_LOW
    timer_ocintpara.outputnstate = TIMER_CCXN_DISABLE;       // 互补通道输出状态TIMER_CCXN_ENABLE, TIMER_CCXN_DISABLE
    timer_ocintpara.ocidlestate  = TIMER_OC_IDLE_STATE_LOW;  // 空闲状态下通道输出TIMER_OC_IDLE_STATE_LOW,TIMER_OC_IDLE_STATE_HIGH
    timer_ocintpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW; // 空闲状态下互补通道输出TIMER_OCN_IDLE_STATE_LOW,TIMER_OCN_IDLE_STATE_HIGH
    /* 使用ch3 */
    timer_channel_output_config(TIMER3, TIMER_CH_3, &timer_ocintpara);

    /* CH1 configuration in PWM mode1,duty cycle 25% */
    // timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_1, 3999);
    // timer_channel_output_mode_config(TIMER1, TIMER_CH_1, TIMER_OC_MODE_PWM0);
    // timer_channel_output_shadow_config(TIMER1, TIMER_CH_1, TIMER_OC_SHADOW_DISABLE);

    /* CH2 configuration in PWM mode1,duty cycle 50% */
    // timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_2, 7999);
    // timer_channel_output_mode_config(TIMER1, TIMER_CH_2, TIMER_OC_MODE_PWM0);
    // timer_channel_output_shadow_config(TIMER1, TIMER_CH_2, TIMER_OC_SHADOW_DISABLE);

    /* CH3 configuration in PWM mode1,duty cycle ~0% */
    timer_channel_output_pulse_value_config(TIMER3, TIMER_CH_3, 10);
    timer_channel_output_mode_config(TIMER3, TIMER_CH_3, TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER3, TIMER_CH_3, TIMER_OC_SHADOW_DISABLE);

    /* auto-reload preload enable */
    timer_auto_reload_shadow_enable(TIMER3);
    timer_primary_output_config(TIMER3, ENABLE);

    // timer_autoreload_value_config(TIMER3, 0xFF);
    // timer_auto_reload_shadow_enable(TIMER3);
    // timer_master_output_trigger_source_select(TIMER3, TIMER_TRI_OUT_SRC_UPDATE); // 更新事件

    /* 无需中断 */
    /* 配置中断优先级 */
    //    nvic_irq_enable(BSP_TIMER_IRQ, 3, 2); // 设置中断优先级为 3,2
    /* 使能中断 */
    //    timer_interrupt_enable(BSP_TIMER, TIMER_INT_UP); // 使能更新事件中断
}
void tim3_enable()
{
    tim3_config(1200, 100); // 20kHz
    /* 使能定时器 */
    timer_enable(TIMER3);
}
void tim3_disable()
{
    timer_disable(TIMER3);
    rcu_periph_clock_disable(RCU_TIMER3);
}
/**
 * 配置Timer5
 * @param prescaler 时钟预分频值(-1会在函数内执行) 0-65535
 * @param period 自动重装载值(-1会在函数内执行)
 */
void tim5_config(uint16_t prescaler, uint16_t period)
{
    /* 一个周期的时间T = 1/f, 定时时间time = T * 周期
    设预分频值位pre,周期位per
    time = (prescaler + 1) * (period + 1) / psc_clk
    */
    timer_parameter_struct timere_initpara; // 定义定时器结构体
    /* 开启时钟 */
    rcu_periph_clock_enable(RCU_TIMER5);

    /* CK_TIMERx = 4 x CK_APB1  = 4x60M = 240MHZ */
    rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4); // 配置定时器时钟倍频器

    timer_deinit(BSP_TIMER); // 复位定时器

    /* 配置定时器参数 */
    timere_initpara.prescaler        = prescaler - 1;      //  时钟预分频值 0-65535   psc_clk = CK_TIMER / prescaler
    timere_initpara.alignedmode      = TIMER_COUNTER_EDGE; // 边缘对齐
    timere_initpara.counterdirection = TIMER_COUNTER_UP;   // 向上计数
    timere_initpara.period           = period - 1;         // 周期

    /* 在输入捕获的时候使用  数字滤波器使用的采样频率之间的分频比例 */
    timere_initpara.clockdivision = TIMER_CKDIV_DIV1; // 分频因子

    /* 只有高级定时器才有 配置为x，就重复x+1次进入中断 */
    timere_initpara.repetitioncounter = 0; // 重复计数器 0-255

    timer_init(TIMER5, &timere_initpara); // 初始化定时器

    timer_autoreload_value_config(TIMER5, 0xFF);
    timer_auto_reload_shadow_enable(TIMER5);
    timer_master_output_trigger_source_select(TIMER5, TIMER_TRI_OUT_SRC_UPDATE); // 更新事件

    /* 无需中断 */
    /* 配置中断优先级 */
    //    nvic_irq_enable(BSP_TIMER_IRQ, 3, 2); // 设置中断优先级为 3,2
    /* 使能中断 */
    //    timer_interrupt_enable(BSP_TIMER, TIMER_INT_UP); // 使能更新事件中断

    /* 使能定时器 */
    timer_enable(TIMER5);
}

///************************************************
// 函数名称 ： BSP_TIMER_IRQHandler
// 功    能 ： 基本定时器中断服务函数
// 参    数 ： 无
// 返 回 值 ： 无
// 作    者 ： LC
//*************************************************/
// void BSP_TIMER_IRQHANDLER(void)
//{
//     /* 这里是定时器中断 */
//     if (timer_interrupt_flag_get(BSP_TIMER, TIMER_INT_FLAG_UP) == SET) {
//         timer_interrupt_flag_clear(BSP_TIMER, TIMER_INT_FLAG_UP); // 清除中断标志位
//         /* 执行功能 */
//         gpio_bit_toggle(PORT_LED2, PIN_LED2); // 翻转led
//         // printf("BSP_TIMER_IRQHANDLER!\r\n");  // 串口打印BSP_TIMER_IRQHANDLER!
//     }
// }