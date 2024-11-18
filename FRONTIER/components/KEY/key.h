/**
 * @file key.h
 * @author SHUAIWEN CUI (SHUAIWEN001@e.ntu.edu.sg)
 * @brief This file is for the onboard key.
 * @version 1.0
 * @date 2024-11-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __KEY_H__
#define __KEY_H__

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

/* Pin Definition */
#define BOOT_GPIO_PIN   GPIO_NUM_0

/* IO Operation */
#define BOOT            gpio_get_level(BOOT_GPIO_PIN)

/* Key Press Definition */
#define BOOT_PRES       1       /* BOOT key pressed */

/* Function declarations */
/**
 * @brief       Initialize the key
 * @param       None
 * @retval      None
 */
void key_init(void);            /* Initialize the key */

/**
 * @brief       Key scan function
 * @param       mode: 0 / 1, with the following meanings:
 *              0: Non-continuous press (returns key value only on the first press.
 *                 Must release and press again to return a value).
 *              1: Continuous press supported (returns key value each time the function is called while the key is pressed).
 * @retval      Key value, defined as follows:
 *              BOOT_PRES, 1, BOOT key pressed
 */
uint8_t key_scan(uint8_t mode); /* Key scan function */

#endif
