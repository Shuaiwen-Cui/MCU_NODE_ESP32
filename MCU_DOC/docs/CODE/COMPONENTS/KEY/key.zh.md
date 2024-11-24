# `key.h` 和 `key.c`

!!! info
    `key.h` & `key.c` 提供了板载按键的驱动。

!!! tip
    本文中提供的驱动是轮询方式，更好的方式是使用中断方式。请参考EXIT组件。

## KEY.H

```c
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

/* DEPENDENCIES */
#include "setup.h"

/* FUNCTION DECLARATIONS */
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

```

## KEY.C

```c
/**
 * @file key.c
 * @author SHUAIWEN CUI (SHUAIWEN001@e.ntu.edu.sg)
 * @brief This file is for the onboard key.
 * @version 1.0
 * @date 2024-11-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */

/* DEPENDENCIES */
#include "key.h"

/* FUNCTION DEFINITIONS */
/**
 * @brief       Initialize the key
 * @param       None
 * @retval      None
 */
void key_init(void)
{
    gpio_config_t gpio_init_struct;

    gpio_init_struct.intr_type = GPIO_INTR_DISABLE;         /* Disable pin interrupt */
    gpio_init_struct.mode = GPIO_MODE_INPUT;                /* Input mode */
    gpio_init_struct.pull_up_en = GPIO_PULLUP_ENABLE;       /* Enable pull-up */
    gpio_init_struct.pull_down_en = GPIO_PULLDOWN_DISABLE;  /* Disable pull-down */
    gpio_init_struct.pin_bit_mask = 1ull << BOOT_GPIO_PIN;  /* BOOT key pin */
    gpio_config(&gpio_init_struct);                         /* Configure and enable */
}

/**
 * @brief       Key scan function
 * @param       mode: 0 / 1, with the following meanings:
 *              0: Non-continuous press (returns key value only on the first press.
 *                 Must release and press again to return a value).
 *              1: Continuous press supported (returns key value each time the function is called while the key is pressed).
 * @retval      Key value, defined as follows:
 *              BOOT_PRES, 1, BOOT key pressed
 */
uint8_t key_scan(uint8_t mode)
{
    uint8_t keyval = 0;
    static uint8_t key_boot = 1;    /* Key release flag */

    if(mode)
    {
        key_boot = 1;
    }

    if (key_boot && (gpio_get_level(BOOT_GPIO_PIN) == 0))    /* Key release flag is 1 and any key is pressed */
    {
        vTaskDelay(10);             /* Debounce */
        key_boot = 0;

        if (gpio_get_level(BOOT_GPIO_PIN) == 0)
        {
            keyval = BOOT_PRES;
        }
    }
    else if (gpio_get_level(BOOT_GPIO_PIN) == 1)
    {
        key_boot = 1;
    }

    return keyval;                  /* Return key value */
}

```

