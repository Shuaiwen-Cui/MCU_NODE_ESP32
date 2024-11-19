# ESP32 BUILT-IN THERMOMETER

## INTRODUCTION

!!! info
    The ESP32 chip has a built-in temperature sensor that can be used to measure the temperature of the chip.

## USE CASES

Measure the internal temperature of the ESP32 chip and display it on the LCD.

## INVOLVED RESOURCES

- ESP32 built-in temperature sensor
- 0.96-inch LCD
- LED (optional)

## CODE

### temp.h
    
```c
/**
 * @file temp.h
 * @author 
 * @brief This file is to drive the built-in temperature sensor of ESP32
 * @version 1.0
 * @date 2024-11-19
 * @ref Alientek Driver
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __SENSOR_H__
#define __SENSOR_H__

#include "esp_err.h"
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/temperature_sensor.h"

/* Parameter definitions */
#define SENSOR_RANGE_MIN    -10      /* Minimum temperature to be tested */
#define SENSOR_RANGE_MAX    80      /* Maximum temperature to be tested */

/* Function declarations */
void temperature_sensor_init(void); /* Initialize the internal temperature sensor */
short sensor_get_temperature(void); /* Get the temperature value from the internal temperature sensor */

#endif


```


### temp.c

```c
/**
 * @file temp.c
 * @author 
 * @brief This file is to drive the built-in temperature sensor of ESP32
 * @version 1.0
 * @date 2024-11-19
 * @ref Alientek Driver
 * @copyright Copyright (c) 2024
 * 
 */

#include "temp.h"

esp_err_t rev_flag;
temperature_sensor_handle_t temp_handle = NULL; /* Temperature sensor handle */

/**
 * @brief       Initialize the internal temperature sensor
 * @param       None
 * @retval      None
 */
void temperature_sensor_init(void)
{
    temperature_sensor_config_t temp_sensor;
    
    temp_sensor.range_min = SENSOR_RANGE_MIN;   /* Minimum temperature to be tested */
    temp_sensor.range_max = SENSOR_RANGE_MAX;   /* Maximum temperature to be tested */

    rev_flag |= temperature_sensor_install(&temp_sensor, &temp_handle);
    ESP_ERROR_CHECK(rev_flag);
}

/**
 * @brief       Get the temperature value from the internal temperature sensor
 * @param       None
 * @retval      Returns the internal temperature value
 */
short sensor_get_temperature(void)
{
    float temp;

    /* Enable the temperature sensor */
    rev_flag |= temperature_sensor_enable(temp_handle);

    /* Retrieve sensor data */
    rev_flag |= temperature_sensor_get_celsius(temp_handle, &temp);

    /* Disable the temperature sensor after use to save power */
    rev_flag |= temperature_sensor_disable(temp_handle);
    ESP_ERROR_CHECK(rev_flag);

    return temp;
}

```

!!! tip
    在CMakelists.txt中添加temp.h, temp.c所在路径，分别添加到头文件和源文件对应位置。

### main

```c
/**
 * @file main.c
 * @author
 * @brief Main application to demonstrate the use of ESP32 internal temperature sensor
 * @version 1.0
 * @date 2024-11-17
 *
 * @copyright Copyright (c) 2024
 *
 */

/* Dependencies */
// Basic
#include "esp_system.h"
#include "esp_chip_info.h"
#include "esp_psram.h"
#include "esp_flash.h"
#include "nvs_flash.h"
#include "esp_log.h"

// RTOS
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// BSP
#include "led.h"
#include "rgb.h"
#include "key.h"
#include "exit.h"
#include "lcd.h"
#include "spi.h"
#include "esp_rtc.h"
#include "temp.h"

void app_main(void)
{
    int16_t temp;
    esp_err_t ret;

    ret = nvs_flash_init(); /* Initialize NVS */

    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    led_init();                /* Initialize LED */
    spi2_init();               /* Initialize SPI2 */
    lcd_init();                /* Initialize LCD */
    temperature_sensor_init(); /* Initialize internal temperature sensor */

    lcd_show_string(0, 0, 200, 16, 16, "TEMPERATURE: 00.00C", BLUE);

    while (1)
    {
        temp = sensor_get_temperature(); /* Get temperature value as float */

        /* Display negative sign if temperature is below zero */
        if (temp < 0)
        {
            temp = -temp;
            lcd_show_string(0 + 10 * 8, 0, 16, 16, 16, "-", BLUE); /* Display '-' sign */
        }
        else
        {
            lcd_show_string(0 + 10 * 8, 0, 16, 16, 16, " ", BLUE); /* No sign for positive values */
        }

        /* Display integer part */
        lcd_show_xnum(0 + 11 * 8, 0, (int)temp, 2, 16, 0, BLUE); /* Convert temp to int for integer part */

        /* Display decimal point */
        lcd_show_string(0 + 13 * 8, 0, 16, 16, 16, ".", BLUE); /* Display decimal point */

        /* Display fractional part */
        lcd_show_xnum(0 + 14 * 8, 0, (int)(temp * 100) % 100, 2, 16, 0, BLUE); /* Multiply by 100 to shift two decimal places */

        led_toggle(); /* Toggle LED to indicate program is running */
        vTaskDelay(250);
    }
}

```