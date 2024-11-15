/**
 ****************************************************************************************************
 * @file        led.h
 * @author      ALIENTEK
 * @version     V1.0
 * @date        2023-08-26
 * @brief       LED driver code
 * @license     Copyright (c) 2020-2032, Guangzhou Xingyi Electronics Co., Ltd.
 ****************************************************************************************************
 * @attention
 *
 * Development Board: ALIENTEK ESP32-S3 Minimum System Board
 * Online Videos: www.yuanzige.com
 * Technical Forum: www.openedv.com
 * Official Website: www.alientek.com
 * Purchase Link: openedv.taobao.com
 * 
 ****************************************************************************************************
 */

#ifndef __LED_H_
#define __LED_H_

#include "driver/gpio.h"

/* GPIO pin definition */
#define LED_GPIO_PIN    GPIO_NUM_1  /* GPIO port connected to LED */

/* Output state of the GPIO pin */
enum GPIO_OUTPUT_STATE
{
    PIN_RESET,
    PIN_SET
};

/* LED control macro */
#define LED(x)          do { x ?                                      \
                             gpio_set_level(LED_GPIO_PIN, PIN_SET) :  \
                             gpio_set_level(LED_GPIO_PIN, PIN_RESET); \
                        } while(0)  /* LED control */

/* LED toggle macro */
#define LED_TOGGLE()    do { gpio_set_level(LED_GPIO_PIN, !gpio_get_level(LED_GPIO_PIN)); } while(0)  /* LED toggle */

/* Function declarations */
void led_init(void);    /* Initialize LED */

#endif
