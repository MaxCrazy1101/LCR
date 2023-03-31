#include "stdio.h"
#include "stdarg.h"

#include "math.h"
#include "arm_math.h"

#include "my_app.h"
#include "bsp_lcd.h"
#include "bsp_led.h"
#include "bsp_key.h"
#include "adc.h"

#include "lvgl.h"
#include "lv_port_disp.h"

#include "gui_guider.h"
#include "events_init.h"

// #include "lv_demos.h"
// #include "lv_examples.h"
/*
**********************************************************************************************************
                                            宏定义
**********************************************************************************************************
*/
#define TEMPERATURE_ADJUST -22

/*
**********************************************************************************************************
                                            函数声明
**********************************************************************************************************
*/
// static void vTaskGUI(void *pvParameters);
static void task_led(void *pvParameters);
static void task_adc0(void *pvParameters);
static void task_start(void *pvParameters);
static void task_user_if(void *pvParameters);
static void task_lcr(void *pvParameters);
static void task_gui(void *pvParameters);

static void task_test_only_once(void *pvParameters);

static void vTaskMsgPro(void *pvParameters);
static void vTaskStart(void *pvParameters);
static void app_create_object(void);
static void thread_safe_printf(char *format, ...);

/*
**********************************************************************************************************
                                            变量声明
**********************************************************************************************************
*/
/* GUI */
lv_ui gui_guider;
/* 任务句柄 */
static TaskHandle_t xHandleTaskLED    = NULL;
static TaskHandle_t xHandleTaskADC0   = NULL;
static TaskHandle_t xHandleTaskLCR    = NULL;
static TaskHandle_t xHandleTaskScan   = NULL;
static TaskHandle_t xHandleTaskUserIF = NULL;
static TaskHandle_t xHandleTaskGUI    = NULL;
static TaskHandle_t xHandleTaskTEST   = NULL;
// static TaskHandle_t xHandleTaskMsgPro = NULL;
// static TaskHandle_t xHandleTaskStart  = NULL;

/* 互斥量句柄 */
static SemaphoreHandle_t xMutex       = NULL;
EventGroupHandle_t xCreatedEventGroup = NULL;

arm_rfft_fast_instance_f32 S;
uint32_t fft_size = 2048;

static void vTaskUsageRate(void)
{
}

/*!
    \brief    app_create_task function
    \param[in]  none
    \param[out] none
    \retval     none
*/
void app_create_task(void)
{
    /*进入临界区*/
    taskENTER_CRITICAL();
    /*创建LED任务*/
    xTaskCreate((TaskFunction_t)task_led,
                (const char *)"led_toggle",
                (uint16_t)128,
                (void *)NULL,
                (UBaseType_t)1,
                (TaskHandle_t *)&xHandleTaskLED);

    /*创建LED任务*/
    xTaskCreate((TaskFunction_t)task_user_if,
                (const char *)"task_user_if",
                (uint16_t)512,
                (void *)NULL,
                (UBaseType_t)2,
                (TaskHandle_t *)&xHandleTaskUserIF);
    /*创建GUI任务*/
    xTaskCreate((TaskFunction_t)task_gui,
                (const char *)"app_gui",
                (uint16_t)512,
                (void *)NULL,
                (UBaseType_t)3,
                (TaskHandle_t *)&xHandleTaskGUI);
    /*创建按键扫描任务*/
    xTaskCreate((TaskFunction_t)task_start,
                (const char *)"task_scan",
                (uint16_t)512,
                (void *)NULL,
                (UBaseType_t)4,
                (TaskHandle_t *)&xHandleTaskScan);
    /*创建ADC0任务*/
    xTaskCreate((TaskFunction_t)task_adc0,
                (const char *)"app_adc0",
                (uint16_t)512,
                (void *)NULL,
                (UBaseType_t)14,
                (TaskHandle_t *)&xHandleTaskADC0);
    /*创建TEST任务*/
    xTaskCreate((TaskFunction_t)task_test_only_once,
                (const char *)"app_test",
                (uint16_t)512,
                (void *)NULL,
                (UBaseType_t)15,
                (TaskHandle_t *)&xHandleTaskTEST);
    /*创建LCR任务*/
    xTaskCreate((TaskFunction_t)task_lcr,
                (const char *)"app_lcr",
                (uint16_t)512,
                (void *)NULL,
                (UBaseType_t)15,
                (TaskHandle_t *)&xHandleTaskLCR);

    /*退出临界区,任务级临界区不允许嵌套,中断级允许 */
    taskEXIT_CRITICAL();
}

/**
 * @brief LCR测量 优先级
 *
 * @param pvParameters
 */
static void task_lcr(void *pvParameters)
{
    /* 实数rfft点数 */
    fft_size = 2048;

    /* 初始化结构体S中的参数 */
    arm_rfft_fast_init_f32(&S, fft_size);
    while (1) {
        //     if (os_evt_wait_or(StartTaskWaitFlag, 0xFFFF) == OS_R_EVT) {
        //         xResult = os_evt_get();

        //         switch (xResult) {
        //             case DspFFT2048Pro_15:
        //                 /* 读取的是ADC3的位置 */
        //                 g_DSO1->usCurPos = 10240 - DMA2_Stream1->NDTR;

        //                 /* 读取的是ADC1的位置 */
        //                 g_DSO2->usCurPos = 10240 - DMA2_Stream0->NDTR;

        //                 DSO2_WaveTrig(g_DSO2->usCurPos);
        //                 DSO1_WaveTrig(g_DSO1->usCurPos);
        //                 DSO2_WaveProcess();
        //                 DSO1_WaveProcess();
        //                 break;

        //             case DspMultiMeterPro_0:
        //                 g_uiAdcAvgSample = ADC_GetSampleAvgN();
        //                 break;

        //             /* 其它位暂未使用 */
        //             default:
        //                 printf_taskdbg("xResult = %x\r\n", xResult);
        //                 break;
        //         }
        //     }
        vTaskDelay(1000);
    }
}

/**
 * @brief adc0信息处理
 *
 * @param pvParameters
 */
static void task_adc0(void *pvParameters)
{
    float battery_value;
    float temperature;
    float vref_value;
    vTaskDelay(1000);
    while (1) {
        battery_value = (adc0_data[0] * 3.3f * 2 / 4096 - 3.0f) / 1.2f * 100;
        temperature   = (1.43f - adc0_data[1] * 3.3f / 4096) * 1000 / 4.3f + 25 + TEMPERATURE_ADJUST;
        vref_value    = (adc0_data[2] * 3.3f / 4096);

        // printf("The temperature origin data is %d \r ,Battery Voltage origin data: %d \n", adc0_data[0], adc0_data[1]);
        thread_safe_printf("Battery: %5.2f V, Temperature: %2.0f degrees Celsius, Vref: %5.2fV.\r\n", adc0_data[0] * 3.3f * 2 / 4096, temperature, vref_value);
        if (battery_value < 0) {
            battery_value = 0;
        } else if (battery_value > 100) {
            battery_value = 100;
        }

        // printf("ADC1 Data[1]:%d\n", adc1_data[1]);
        /* 修改电量数据 */
        lv_bar_set_value(gui_guider.screen_battery_bar, (int32_t)battery_value, LV_ANIM_ON);
        lv_label_set_text_fmt(gui_guider.screen_battery_text, "%3d%%", (int32_t)battery_value);
        lv_label_set_text_fmt(gui_guider.screen_vref, "%1.2fV", vref_value);
        lv_label_set_text_fmt(gui_guider.screen_temperature, "%2.0fC", temperature);

        vTaskDelay(10000);
    }
}

static void task_user_if(void *pvParameters)
{
    uint8_t ucKeyCode;
    uint8_t pcWriteBuffer[500];

    while (1) {
        ucKeyCode = bsp_key_dequeue();

        if (ucKeyCode != KEY_NONE) {
            switch (ucKeyCode) {
                /* K1键按下 打印任务执行情况 */
                case KEY_DOWN_K1:
                    /* 任务运行状态的定义如下，跟上面串口打印字母X, B, R, D, S对应：
                     * #define tskRUNNING_CHAR      ( 'X' )  运行
                     * #define tskBLOCKED_CHAR		( 'B' )  阻塞
                     * #define tskREADY_CHAR		( 'R' )  就绪
                     * #define tskDELETED_CHAR		( 'D' )  删除
                     * #define tskSUSPENDED_CHAR	( 'S' )  挂起 */

                    thread_safe_printf("=================================================\r\n");
                    thread_safe_printf("任务名      任务状态 优先级   剩余栈 任务序号\r\n");
                    vTaskList((char *)&pcWriteBuffer);
                    thread_safe_printf("%s\r\n", pcWriteBuffer);

                    thread_safe_printf("\r\n任务名       运行计数         使用率\r\n");
                    vTaskGetRunTimeStats((char *)&pcWriteBuffer);
                    thread_safe_printf("%s\r\n", pcWriteBuffer);
                    printf("当前动态内存剩余大小 = %d字节\r\n", xPortGetFreeHeapSize());
                    break;

                /* 其他的键值不处理 */
                default:
                    break;
            }
        }

        vTaskDelay(20);
    }
}

/**
 * @brief 用于测试,代码只会执行一次 优先级
 *
 * @param pvParameters
 */
static void task_test_only_once(void *pvParameters)
{
    while (1) {

        vTaskDelay(100);
    }
}

/**
 * @brief LVGL 循环
 *
 * @param pvParameters
 */
static void task_gui(void *pvParameters)
{
    LCD_Fill(0, 0, LCD_W, LCD_H, WHITE);
    LCD_Fill(0, 0, LCD_W, LCD_H, BLUE);
    LCD_Fill(0, 0, LCD_W, LCD_H, RED);

    lv_init();
    lv_port_disp_init();
    /* GUI Guider init */
    setup_ui(&gui_guider);
    events_init(&gui_guider);
    // lv_demo_benchmark();
    while (1) {
        lv_task_handler();
        vTaskDelay(10);
    }
}

/**
 * @brief LED闪烁 优先级
 *
 * @param pvParameters
 */
static void task_led(void *pvParameters)
{
    while (1) {
        LED1_TOGGLE;
        vTaskDelay(1000);
    }
}
/**
 * @brief 启动任务，也就是最高优先级任务。主要实现按键检测和触摸检测。
 *
 * @param pvParameters
 */
static void task_start(void *pvParameters)
{
    // uint8_t ucCount  = 0;
    // uint8_t ucCount1 = 0;

    while (1) {
        /* 10ms 一次按键扫描 */
        bsp_KeyScan();
        vTaskDelay(10);

        // /* 1ms一次触摸扫描，电阻触摸屏 */
        // if (g_tTP.Enable == 1) {
        //     TOUCH_Scan();

        //     /* 按键扫描 */
        //     ucCount++;
        //     if (ucCount == 10) {
        //         ucCount = 0;
        //         bsp_KeyScan();
        //     }
        //     vTaskDelay(1);
        // }

        // /* 10ms一次触摸扫描，电容触摸屏GT811 */
        // if (g_GT811.Enable == 1) {
        //     bsp_KeyScan();
        //     ucCount1++;
        //     if (ucCount1 == 2) {
        //         ucCount1 = 0;
        //         GT811_OnePiontScan();
        //     }
        //     vTaskDelay(10);
        // }

        // /* 10ms一次触摸扫描，电容触摸屏FT5X06 */
        // if (g_tFT5X06.Enable == 1) {
        //     bsp_KeyScan();
        //     FT5X06_OnePiontScan();
        //     vTaskDelay(10);
        // }
    }
}

/**
 * @brief 线程安全的printf方式
 *
 * @param format 同printf的参数。
 * @param ... 在C中，当无法列出传递函数的所有实参的类型和数目时,可以用省略号指定参数表
 */
static void thread_safe_printf(char *format, ...)
{
    char buf_str[200 + 1];
    va_list v_args;

    va_start(v_args, format);
    (void)vsnprintf((char *)&buf_str[0],
                    (size_t)sizeof(buf_str),
                    (char const *)format,
                    v_args);
    va_end(v_args);

    /* 互斥信号量 */
    xSemaphoreTake(xMutex, portMAX_DELAY);

    printf("%s", buf_str);

    xSemaphoreGive(xMutex);
}

void os_error_print()
{
    printf("OS STARTUP ERROR!\r\n");
}

/**
 * @brief 任务通信变量初始化
 *
 */
static void app_create_object(void)
{
    /* 创建互斥信号量 */
    xMutex = xSemaphoreCreateMutex();

    if (xMutex == NULL) {
        /* 没有创建成功，用户可以在这里加入创建失败的处理机制 */
        os_error_print();
    }
    /* 创建事件标志组 */
    xCreatedEventGroup = xEventGroupCreate();

    if (xCreatedEventGroup == NULL) {
        /* 没有创建成功，用户可以在这里加入创建失败的处理机制 */
        os_error_print();
    }
}

void app_main()
{
    /* 1. 初始化一个定时器中断，精度高于滴答定时器中断，这样才可以获得准确的系统信息 仅供调试目的，
     *实际项目中不要使用，因为这个功能比较影响系统实时性。
     *2. 为了正确获取 FreeRTOS 的调试信息，可以考虑将上面的关闭中断指令__set_PRIMASK(1); 注释掉。*/
    // vSetupSysInfoTest();

    /* 创建app任务 */
    app_create_task();
    /* 创建app信号量 */
    app_create_object();
    /* 开始任务调度 */
    vTaskStartScheduler();
}