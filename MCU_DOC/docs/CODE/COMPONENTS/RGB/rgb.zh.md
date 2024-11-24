# `rgb.h`和`rgb.c`

!!! info
    `rgb.h`和`rgb.c`提供了控制RGB灯的相关函数。

## RGB.H

```c
/**
 * @file rgb.h
 * @author SHUAIWEN CUI (SHUAIWEN001@e.ntu.edu.sg)
 * @brief This driver can be used for external RGB LED modules.
 * @version 1.0
 * @date 2024-11-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __RGB_H__
#define __RGB_H__

/* DEPENDENCIES */
#include "setup.h"

/* FUNCTION PROTOTYPES */
/**
 * @brief       Initialize the RGB LED
 * @param       None
 * @retval      None
 */
void rgb_init(void);

/**
 * @brief       Control the RGB LED
 * @param       r: 1 for on, 0 for off
 * @param       g: 1 for on, 0 for off
 * @param       b: 1 for on, 0 for off
 * @retval      None
 */
void rgb(int r, int g, int b);

/**
 * @brief       Toggle the RGB LED
 * @param       None
 * @retval      None
 */
void rgb_toggle(void);

#endif /*__RGB_H__*/
```

## RGB.C

```c
/**
 * @file rgb.c
 * @author SHUAIWEN CUI (SHUAIWEN001@e.ntu.edu.sg)
 * @brief This driver can be used for external RGB LED modules.
 * @version 1.0
 * @date 2024-11-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */

/* DEPENDENCIES */
#include "rgb.h"

/* FUNCTION DEFINITIONS */
/**
 * @brief       Initialize the RGB LED
 * @param       None
 * @retval      None
 */
void rgb_init(void)
{
    gpio_config_t gpio_init_struct = {0};

    gpio_init_struct.intr_type = GPIO_INTR_DISABLE;         /* Disable GPIO interrupt */
    gpio_init_struct.mode = GPIO_MODE_INPUT_OUTPUT;         /* Set GPIO mode to input-output */
    gpio_init_struct.pull_up_en = GPIO_PULLUP_ENABLE;       /* Enable pull-up resistor */
    gpio_init_struct.pull_down_en = GPIO_PULLDOWN_DISABLE;  /* Disable pull-down resistor */
    gpio_init_struct.pin_bit_mask = 1ull << RGB_R_GPIO_PIN; /* Set pin bit mask for the configured pin */
    gpio_init_struct.pin_bit_mask |= 1ull << RGB_G_GPIO_PIN; /* Set pin bit mask for the configured pin */
    gpio_init_struct.pin_bit_mask |= 1ull << RGB_B_GPIO_PIN; /* Set pin bit mask for the configured pin */
    gpio_config(&gpio_init_struct);                         /* Configure GPIO */

    rgb(1, 1, 1); /* Turn on the RGB LED */
}

/**
 * @brief       Control the RGB LED
 * @param       r: 1 for on, 0 for off
 * @param       g: 1 for on, 0 for off
 * @param       b: 1 for on, 0 for off
 * @retval      None
 */
void rgb(int r, int g, int b)
{
    if(r)
    {
        gpio_set_level(RGB_R_GPIO_PIN, RGB_PIN_SET);
    }
    else
    {
        gpio_set_level(RGB_R_GPIO_PIN, RGB_PIN_RESET);
    }

    if(g)
    {
        gpio_set_level(RGB_G_GPIO_PIN, RGB_PIN_SET);
    }
    else
    {
        gpio_set_level(RGB_G_GPIO_PIN, RGB_PIN_RESET);
    }

    if(b)
    {
        gpio_set_level(RGB_B_GPIO_PIN, RGB_PIN_SET);
    }
    else
    {
        gpio_set_level(RGB_B_GPIO_PIN, RGB_PIN_RESET);
    }
}

/**
 * @brief       Toggle the RGB LED
 * @param       None
 * @retval      None
 */
void rgb_toggle(void)
{
    gpio_set_level(RGB_R_GPIO_PIN, !gpio_get_level(RGB_R_GPIO_PIN));
    gpio_set_level(RGB_G_GPIO_PIN, !gpio_get_level(RGB_G_GPIO_PIN));
    gpio_set_level(RGB_B_GPIO_PIN, !gpio_get_level(RGB_B_GPIO_PIN));
}
```

