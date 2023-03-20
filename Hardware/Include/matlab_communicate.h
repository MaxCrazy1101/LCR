#ifndef MATLAB_COMMUNICATE_H
#define MATLAB_COMMUNICATE_H
#ifdef __cplusplus
extern "C" {
#endif
#include "gd32f4xx.h"
__PACKED typedef struct
{
    uint16_t data1;
    uint16_t data2;
    uint16_t data3;
    uint8_t data4;
    uint8_t data5;
    uint8_t data6;
    uint8_t data7;
} SENDPARAM_T;
SENDPARAM_T g_SendData;

#ifdef __cplusplus
}
#endif
#endif /* MATLAB_COMMUNICATE_H */