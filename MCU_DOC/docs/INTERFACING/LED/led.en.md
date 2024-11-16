# LED

## Introduction

!!! note
    In this section, we will talk about the onboard LED light on the DNESP32S3M development board.

![LED](LED.png){ width=800px }

## Overview

In the project, we created a new directory named `LED` under the `components` directory to store the LED driver code, including the `led.h` and `led.c` files.

## Pin Configuration

According to the schematic, the onboard LED light is connected to GPIO1.

![LED_CIRCUIT](LED_CIRCUIT.png){ width=800px }

## Code

### LED.h
    
```c
/**
 * @file led.h
 * @author SHUAIWEN CUI (SHUAIWEN001@e.ntu.edu.sg)
 * @brief The led here indicates the onboard red led on the Alientek DNESP32S3M minimal development board.
 * @version 1.0
 * @date 2024-11-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __LED_H__
#define __LED_H__

/* Dependencies */
#include "driver/gpio.h"

/* GPIO Pin Definition */
#define LED_GPIO_PIN    GPIO_NUM_1  /* GPIO port connected to LED */

/* GPIO States */
#define LED_PIN_RESET       0
#define LED_PIN_SET         1

/**
 * @brief       Initialize the LED
 * @param       None
 * @retval      None
 */
void led_init(void);

/**
 * @brief       Control the LED
 * @param       x: 1 for on, 0 for off
 * @retval      None
 */
void led(int x);

/**
 * @brief       Toggle the LED
 * @param       None
 * @retval      None
 */
void led_toggle(void);

#endif

```

### LED.c

```c
/**
 * @file led.c
 * @author SHUAIWEN CUI (SHUAIWEN001@e.ntu.edu.sg)
 * @brief The led here indicates the onboard red led on the Alientek DNESP32S3M minimal development board.
 * @version 1.0
 * @date 2024-11-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */

/* Dependencies */
#include "led.h"

/**
 * @brief       Initialize the LED
 * @param       None
 * @retval      None
 */
void led_init(void)
{
    gpio_config_t gpio_init_struct = {0};

    gpio_init_struct.intr_type = GPIO_INTR_DISABLE;         /* Disable GPIO interrupt */
    gpio_init_struct.mode = GPIO_MODE_INPUT_OUTPUT;         /* Set GPIO mode to input-output */
    gpio_init_struct.pull_up_en = GPIO_PULLUP_ENABLE;       /* Enable pull-up resistor */
    gpio_init_struct.pull_down_en = GPIO_PULLDOWN_DISABLE;  /* Disable pull-down resistor */
    gpio_init_struct.pin_bit_mask = 1ull << LED_GPIO_PIN;   /* Set pin bit mask for the configured pin */
    gpio_config(&gpio_init_struct);                         /* Configure GPIO */

    led(1); /* Turn on the LED */
}

/**
 * @brief       Control the LED
 * @param       x: 1 for on, 0 for off
 * @retval      None
 */
void led(int x)
{
    if(x)
    {
        gpio_set_level(LED_GPIO_PIN, LED_PIN_RESET);
    }
    else
    {
        gpio_set_level(LED_GPIO_PIN, LED_PIN_SET);
    }
}

/**
 * @brief       Toggle the LED
 * @param       None
 * @retval      None
 */
void led_toggle(void)
{
    gpio_set_level(LED_GPIO_PIN, !gpio_get_level(LED_GPIO_PIN));
}
```

## Core Functions

### led_init()

!!! note
    初始化LED灯。

### led()

!!! note
    控制LED灯。

### led_toggle()

!!! note
    翻转LED灯。