#include "FreeRTOS.h"
#include "task.h"
#include "stdio.h"


#if configCHECK_FOR_STACK_OVERFLOW
/**
 * @brief 栈溢出钩子函数
 *
 * @param xTask 任务句柄
 * @param pcTaskName 任务名
 */

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    printf("任务：%s 发现栈溢出\r\n", pcTaskName);
}
#endif