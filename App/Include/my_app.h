#ifndef MY_APP_H
#define MY_APP_H
#ifdef __cplusplus
extern "C" {
#endif
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/**
 * @brief 创建任务
 */
void app_create_task();

void app_main();

#ifdef __cplusplus
}
#endif
#endif /* MY_APP_H */