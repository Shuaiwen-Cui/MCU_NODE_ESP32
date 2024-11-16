# RGB LED

## Introduction

!!! note
    In this section, we will talk about the onboard RGB LED light on the DNESP32S3M development board.

## Overview

In the project, we created a new directory named `RGB` under the `components` directory to store the RGB LED driver code, including the `rgb.h` and `rgb.c` files.

## Pin Configuration

Please refer to the following table for the connection.

| RGB LED Module Pin | Main Control Pin |
| ------------------- | ---------------- |
| R                   | GPIO_NUM_19      |
| G                   | GPIO_NUM_20      |
| B                   | GPIO_NUM_21      |
| GND                 | GND              |

![RGB_PIN](RGB_PIN.png){ width=800px }

## Code

### RGB.h
    
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

/* Dependencies */
#include "driver/gpio.h"

/* GPIO Pin Definition */
#define RGB_R_GPIO_PIN  GPIO_NUM_19  /* GPIO port connected to RGB Red */
#define RGB_G_GPIO_PIN  GPIO_NUM_20  /* GPIO port connected to RGB Green */
#define RGB_B_GPIO_PIN  GPIO_NUM_21  /* GPIO port connected to RGB Blue */

/* GPIO States */
#define RGB_PIN_RESET   0
#define RGB_PIN_SET     1

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

#endif
```

### RGB.c

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

/* Dependencies */
#include "rgb.h"

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

## Core Functions

### rgb_init()

!!! note
    Initialize the RGB LED.

### rgb(int r, int g, int b)

!!! note
    Control the RGB LED.

### rgb_toggle()

!!! note
    Toggle the RGB LED.