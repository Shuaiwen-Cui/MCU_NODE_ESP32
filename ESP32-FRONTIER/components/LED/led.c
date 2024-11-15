/**
 ****************************************************************************************************
 * @file        led.c
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

    LED(1);                                                 /* Turn off the LED */
}
