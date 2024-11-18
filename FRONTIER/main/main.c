/**
 * @file main.c
 * @author SHUAIWEN CUI (SHUAIWEN001@e.ntu.edu.sg)
 * @brief 
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

/* Global variables */
char* weekdays[]={"Sunday","Monday","Tuesday","Wednesday",
                  "Thursday","Friday","Saterday"};

/**
 * @brief Entry point of the program
 * @param None
 * @retval None
 */
void app_main(void)
{
    esp_err_t ret;
    uint8_t tbuf[40];
    uint8_t t = 0;
    

    ret = nvs_flash_init();             

    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    led_init();                         
    spi2_init();                        
    lcd_init();                         
    rtc_set_time(2024,10,18,00,00,00);   

    while (1)
    {
        t++;

        if ((t % 10) == 0)              
        {
            rtc_get_time();
            sprintf((char *)tbuf, "Time:%02d:%02d:%02d", calendar.hour, calendar.min, calendar.sec);
            printf("Time:%02d:%02d:%02d\r\n", calendar.hour, calendar.min, calendar.sec);
            lcd_show_string(0, 0, 210, 16, 16, (char *)tbuf,BLUE);
            sprintf((char *)tbuf, "Date:%04d-%02d-%02d", calendar.year, calendar.month, calendar.date);
            printf("Date:%02d-%02d-%02d\r\n",  calendar.year,  calendar.month,  calendar.date);
            lcd_show_string(0, 30, 210, 16, 16, (char *)tbuf,BLUE);
            sprintf((char *)tbuf, "Week:%s", weekdays[calendar.week - 1]);
            lcd_show_string(0, 60, 210, 16, 16, (char *)tbuf,BLUE);
        }

        if ((t % 20) == 0)
        {
            led_toggle();               
        }

        vTaskDelay(10);
    }
}