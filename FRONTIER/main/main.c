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
