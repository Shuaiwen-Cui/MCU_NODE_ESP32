# RGB LED 灯模块

## 介绍

!!! note
    RGB LED 灯模块是一种集成了红、绿、蓝三种颜色的 LED 灯模块，对于本项目主控而言，该模块属于外接模块。

## Overview

我们在项目components目录下，新建了一个RGB目录，用于存放RGB LED灯的驱动代码，包括rgb.h和rgb.c文件。

## 引脚配置

由于是外接模块，没有相关图纸，请参考以下表格进行连线。

| RGB LED 模块引脚   | 主控引脚/电源      |
| ----------------- | ------------------|
| R                 | GPIO_NUM_19       |
| G                 | GPIO_NUM_20       |
| B                 | GPIO_NUM_21       |
| GND               | GND               |

![RGB_PIN](RGB_PIN.png){ width=800px }

## 代码

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

## 核心函数

### rgb_init()

!!! note
    初始化RGB灯。

### rgb(int r, int g, int b)

!!! note
    控制RGB灯。

### rgb_toggle()