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
#include "rng.h"

void app_main(void)
{
    uint8_t key;
    uint32_t random;
    uint8_t t = 0;
    esp_err_t ret;
    
    ret = nvs_flash_init();                                         /* Initialize NVS */

    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    led_init();                                                     /* Initialize LED */
    spi2_init();                                                    /* Initialize SPI2 */
    lcd_init();                                                     /* Initialize LCD */
    key_init();                                                     /* Initialize keys */
    
    lcd_show_string(0, 0, 200, 16, 16, "RNG Test", RED);
    lcd_show_string(0, 20, 200, 16, 16, "BOOT:Get Random Num", RED);
    lcd_show_string(0, 40, 200, 16, 16, "Num:", RED);
    lcd_show_string(0, 60, 200, 16, 16, "Num[0-9]:", RED);

    while(1)
    {
        key = key_scan(0);
        
        if (key == BOOT)                                            /* Get a random number and display on LCD */
        {
            random = rng_get_random_num();
            lcd_show_num(30 + 8 * 5, 40, random, 10, 16, BLUE);
        }
        
        if ((t % 20) == 0)                                          /* Get a random number [0,9] and display on LCD */
        {
            led_toggle();                                           /* Toggle LED every 200ms */
            random = rng_get_random_range(0, 9);                    /* Generate a random number in [0,9] range */
            lcd_show_num(32 + 8 * 11, 60, random, 1, 16, BLUE);     /* Display the random number */
        }

        vTaskDelay(10);
        t++;
    }
}
