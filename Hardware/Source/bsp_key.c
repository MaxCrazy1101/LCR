#include "bsp_key.h"

#define HARD_KEY_NUM                    1
#define SOFT_KEY_NUM                    0
#define KEY_COUNT                       (HARD_KEY_NUM + SOFT_KEY_NUM) /* 按键个数, 8个独立建 + 2个组合键 */

#define GPIO_PORT_K1                    BSP_KEY_PORT
#define GPIO_PIN_K1                     BSP_KEY_PIN
#define GPIO_IDR_CAL(port_base, bitnum) (0x42000000 + (((port_base + 0x10) - 0x40000000) * 32) + (bitnum * 4))

/* 依次定义GPIO */
typedef struct
{
    uint32_t ISTAT_BIT_ADDR; /* 位带地址 */
    uint8_t ActiveLevel;     /* 激活电平 */
} X_GPIO_T;

/* GPIO和PIN定义 */
static const X_GPIO_T s_gpio_list[HARD_KEY_NUM] = {
    {GPIO_IDR_CAL(GPIOA, 0), 1}, /* K1 */
                                 // {GPIOC, GPIO_PIN_13, 0}, /* K2 */
                                 // {GPIOH, GPIO_PIN_4, 0},  /* K3 */
                                 // {GPIOG, GPIO_PIN_2, 0},  /* JOY_U */
                                 // {GPIOB, GPIO_PIN_0, 0},  /* JOY_D */
                                 // {GPIOG, GPIO_PIN_3, 0},  /* JOY_L */
                                 // {GPIOG, GPIO_PIN_7, 0},  /* JOY_R */
                                 // {GPIOI, GPIO_PIN_11, 0}, /* JOY_OK */
};

static key_t s_tbtn[KEY_COUNT];
static keyFIFO_t s_tKey; /* 按键FIFO变量,结构体 */

static void bsp_InitKeyVar(void);
static void bsp_DetectKey(uint8_t i);

/**
 * @brief 判断某个按键是否被按下
 *
 * @param _id
 * @return uint8_t
 */
static uint8_t is_key_pressed(uint8_t _id)
{
    uint8_t level;
    // *(volatile unsigned long *)(0x42000000 + (GPIOD_OCTL_OFFSET * 32) + (7 * 4)) = 1;

    if ((*(volatile unsigned long *)(s_gpio_list[_id].ISTAT_BIT_ADDR)) == 0) {
        level = 0;
    } else {
        level = 1;
    }

    if (level == s_gpio_list[_id].ActiveLevel) {
        return 1;
    } else {
        return 0;
    }
}
/**
 * @brief 判断按键是否按下。
 * 单键和组合键区分: 单键事件不允许有其他键按下。
 *
 * @param _id 按键代码
 * @return uint8_t 0释放 1导通
 */
static uint8_t is_key_down(uint8_t _id)
{
    /* 实体单键 */
    if (_id < HARD_KEY_NUM) {
        uint8_t i;
        uint8_t count = 0;
        uint8_t save  = 255;

        /* 判断有几个键按下 */
        for (i = 0; i < HARD_KEY_NUM; i++) {
            if (is_key_pressed(i)) {
                count++;
                save = i;
            }
        }

        if (count == 1 && save == _id) {
            return 1; /* 只有1个键按下时才有效 */
        }

        return 0;
    }

    // /* 组合键 K1K2 */
    // if (_id == HARD_KEY_NUM + 0) {
    //     if (KeyPinActive(KID_K1) && KeyPinActive(KID_K2)) {
    //         return 1;
    //     } else {
    //         return 0;
    //     }
    // }

    // /* 组合键 K2K3 */
    // if (_id == HARD_KEY_NUM + 1) {
    //     if (KeyPinActive(KID_K2) && KeyPinActive(KID_K3)) {
    //         return 1;
    //     } else {
    //         return 0;
    //     }
    // }

    return 0;
}

/**
 * @brief 这个函数将被bsp_init()调用
 *
 */
void bsp_key_config(void)
{
    bsp_InitKeyVar(); /* 初始化按键变量 */
}

/**
 * @brief 把一个按键加入FIFO缓冲区
 *
 * @param _KeyCode 按键代码
 */
void bsp_key_enqueue(uint8_t _KeyCode)
{
    s_tKey.Buf[s_tKey.Write] = _KeyCode;

    if (++s_tKey.Write >= KEY_FIFO_SIZE) {
        s_tKey.Write = 0;
    }
}

/**
 * @brief 从按键FIFO缓冲区读取一个键值。
 *
 * @return uint8_t 按键代码
 */
uint8_t bsp_key_dequeue(void)
{
    uint8_t ret;

    if (s_tKey.Read == s_tKey.Write) {
        return KEY_NONE;
    } else {
        ret = s_tKey.Buf[s_tKey.Read];

        if (++s_tKey.Read >= KEY_FIFO_SIZE) {
            s_tKey.Read = 0;
        }
        return ret;
    }
}

/**
 * @brief 从按键FIFO缓冲区根据2号读取指针读取一个键值。
 *
 * @return uint8_t 按键代码
 */
uint8_t bsp_key_dequeue2(void)
{
    uint8_t ret;

    if (s_tKey.Read2 == s_tKey.Write) {
        return KEY_NONE;
    } else {
        ret = s_tKey.Buf[s_tKey.Read2];

        if (++s_tKey.Read2 >= KEY_FIFO_SIZE) {
            s_tKey.Read2 = 0;
        }
        return ret;
    }
}

/**
 * @brief 读取按键的状态
 *
 * @param _ucKeyID 按键ID，从0开始
 * @return uint8_t 1 表示按下， 0 表示未按下
 */
uint8_t bsp_GetKeyState(KEY_ID_E _ucKeyID)
{
    return s_tbtn[_ucKeyID].State;
}

/**
 * @brief 设置按键参数
 *
 * @param _ucKeyID 按键ID，从0开始
 * @param _LongTime 长按事件时间
 * @param _RepeatSpeed 连发速度
 */
void bsp_SetKeyParam(uint8_t _ucKeyID, uint16_t _LongTime, uint8_t _RepeatSpeed)
{
    s_tbtn[_ucKeyID].LongTime    = _LongTime;    /* 长按时间 0 表示不检测长按键事件 */
    s_tbtn[_ucKeyID].RepeatSpeed = _RepeatSpeed; /* 按键连发的速度，0表示不支持连发 */
    s_tbtn[_ucKeyID].RepeatCount = 0;            /* 连发计数器 */
}

/**
 * @brief 清空按键FIFO缓冲区
 *
 */
void bsp_ClearKey(void)
{
    s_tKey.Read = s_tKey.Write;
    // s_tKey.Read2 = s_tKey.Write; //TODO:需要加这一行吗
}

/**
 * @brief 初始化全局变量
 *
 */
static void bsp_InitKeyVar(void)
{
    uint8_t i;

    /* 对按键FIFO读写指针清零 */
    s_tKey.Read  = 0;
    s_tKey.Write = 0;
    s_tKey.Read2 = 0;

    /* 给每个按键结构体成员变量赋一组缺省值 */
    for (i = 0; i < KEY_COUNT; i++) {
        s_tbtn[i].LongTime    = KEY_LONG_TIME;       /* 长按时间 0 表示不检测长按键事件 */
        s_tbtn[i].Count       = KEY_FILTER_TIME / 2; /* 计数器设置为滤波时间的一半 */
        s_tbtn[i].State       = 0;                   /* 按键缺省状态，0为未按下 */
        s_tbtn[i].RepeatSpeed = 0;                   /* 按键连发的速度，0表示不支持连发 */
        s_tbtn[i].RepeatCount = 0;                   /* 连发计数器 */
    }
}

/**
 * @brief 检测一个按键。非阻塞状态，必须被周期性的调用。
 *
 * @param i 按键代码
 */
static void bsp_DetectKey(uint8_t i)
{
    static key_t *pBtn;

    pBtn = &s_tbtn[i];
    if (is_key_down(i)) {
        if (pBtn->Count < KEY_FILTER_TIME) {
            pBtn->Count = KEY_FILTER_TIME;
        } else if (pBtn->Count < 2 * KEY_FILTER_TIME) {
            pBtn->Count++;
        } else {
            /* 按键上一个状态是释放状态 */
            if (pBtn->State == 0) {
                pBtn->State = 1;

                /* 发送按钮按下的消息 */
                bsp_key_enqueue((uint8_t)(3 * i + 1));
            }
            /* 按键长时间按下 */
            if (pBtn->LongTime > 0) {
                if (pBtn->LongCount < pBtn->LongTime) {
                    /* 发送按钮持续按下的消息 */
                    if (++pBtn->LongCount == pBtn->LongTime) {
                        /* 键值放入按键FIFO */
                        bsp_key_enqueue((uint8_t)(3 * i + 3));
                    }
                } else {
                    /* 允许多次发送按下消息 */
                    if (pBtn->RepeatSpeed > 0) {
                        if (++pBtn->RepeatCount >= pBtn->RepeatSpeed) {
                            pBtn->RepeatCount = 0;
                            /* 常按键后，每隔(RepeatSpeed)*10ms发送1个按键 */
                            bsp_key_enqueue((uint8_t)(3 * i + 1));
                        }
                    }
                }
            } /* END 按键长时间按下 */
        }
    } else { /* 按键未按下 */
        if (pBtn->Count > KEY_FILTER_TIME) {
            pBtn->Count = KEY_FILTER_TIME;
        } else if (pBtn->Count != 0) {
            /* 滤波中 */
            pBtn->Count--;
        } else { /* pBtn->Count==0 */
            if (pBtn->State == 1) {
                pBtn->State = 0;

                /* 发送按钮弹起的消息 */
                bsp_key_enqueue((uint8_t)(3 * i + 2));
            }
        }

        pBtn->LongCount   = 0;
        pBtn->RepeatCount = 0;
    }
}

/*
*********************************************************************************************************
*	函 数 名: bsp_KeyScan
*	功能说明: 扫描所有按键。非阻塞，被systick中断周期性的调用
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_KeyScan(void)
{
    uint8_t i;
    for (i = 0; i < KEY_COUNT; i++) {
        bsp_DetectKey(i);
    }
}
