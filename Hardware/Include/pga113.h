#ifndef PGA113_H
#define PGA113_H
#ifdef __cplusplus
extern "C" {
#endif
#include "gd32f4xx.h"
#include "main.h"
// 1, 2, 5,10,20,50,100,200
/* PGA11x commands (PGA112/PGA113) */
#define PGA11X_CMD_READ    0x6a00
#define PGA11X_CMD_WRITE   0x2a00
#define PGA11X_CMD_NOOP    0x0000
#define PGA11X_CMD_SDN_DIS 0xe100
#define PGA11X_CMD_SDN_EN  0xe1f1

#define PGA113_CH0_GAIN1   PGA11X_CMD_WRITE | PGA11X_GAIN1_GAIN1 << 4 | PGA11X_CHAN_CAL1

typedef enum {
    PGA11X_GAIN1   = 0,
    PGA11X_GAIN2   = 1,
    PGA11X_GAIN4   = 2,
    PGA11X_GAIN5   = 2,
    PGA11X_GAIN8   = 3,
    PGA11X_GAIN10  = 3,
    PGA11X_GAIN16  = 4,
    PGA11X_GAIN20  = 4,
    PGA11X_GAIN32  = 5,
    PGA11X_GAIN50  = 5,
    PGA11X_GAIN64  = 6,
    PGA11X_GAIN100 = 6,
    PGA11X_GAIN128 = 7,
    PGA11X_GAIN200 = 7,
} PGA11X_GAIN;

typedef enum {
    PGA11X_CH0_VCAL = 0,  /* VCAL/CH0 */
    PGA11X_CH1      = 1,  /* CH1 */
    PGA11X_CH2      = 2,  /* CH2 (PGA116/PGA117 only) */
    PGA11X_CH3      = 3,  /* CH3 (PGA116/PGA117 only) */
    PGA11X_CH4      = 4,  /* CH4 (PGA116/PGA117 only) */
    PGA11X_CH5      = 5,  /* CH5 (PGA116/PGA117 only) */
    PGA11X_CH6      = 6,  /* CH6 (PGA116/PGA117 only) */
    PGA11X_CH7      = 7,  /* CH7 (PGA116/PGA117 only) */
    PGA11X_CH8      = 8,  /* CH8 (PGA116/PGA117 only) */
    PGA11X_CH9      = 9,  /* CH9 (PGA116/PGA117 only) */
    PGA11X_CAL1     = 12, /* CAL1: connects to GND */
    PGA11X_CAL2     = 13, /* CAL2: connects to 0.9VCAL */
    PGA11X_CAL3     = 14, /* CAL3: connects to 0.1VCAL */
    PGA11X_CAL4     = 15, /* CAL4: connects to VREF */
} PGA11X_CH;

void pga11x_config();
void pga113_set_gain(uint16_t);
#ifdef __cplusplus
}
#endif
#endif /* PGA113_H */