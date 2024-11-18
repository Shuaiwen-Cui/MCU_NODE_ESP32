// /**
//  * @file main.c
//  * @author SHUAIWEN CUI (SHUAIWEN001@e.ntu.edu.sg)
//  * @brief 
//  * @version 1.0
//  * @date 2024-11-17
//  * 
//  * @copyright Copyright (c) 2024
//  * 
//  */

// /* Dependencies */
// // Basic
// #include "esp_system.h"
// #include "esp_chip_info.h"
// #include "esp_psram.h"
// #include "esp_flash.h"
// #include "nvs_flash.h"
// #include "esp_log.h"

// // RTOS
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"

// // BSP
// #include "led.h"
// #include "rgb.h"
// #include "key.h"
// #include "exit.h"
// #include "tim.h"
// #include "lcd.h"
// #include "spi.h"

// /**
//  * @brief Entry point of the program
//  * @param None
//  * @retval None
//  */
// void app_main(void)
// {
//     esp_err_t ret;
//     uint32_t flash_size;
//     esp_chip_info_t chip_info;

//     // uint8_t key;

//     uint8_t x = 0; // for lcd

//     // Initialize NVS
//     ret = nvs_flash_init();
//     if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
//     {
//         ESP_ERROR_CHECK(nvs_flash_erase()); // Erase if needed
//         ret = nvs_flash_init();
//     }

//     // Get FLASH size
//     esp_flash_get_size(NULL, &flash_size);
//     esp_chip_info(&chip_info);

//     // Display CPU core count
//     printf("CPU Cores: %d\n", chip_info.cores);

//     // Display FLASH size
//     printf("Flash size: %ld MB flash\n", flash_size / (1024 * 1024));

//     // Display PSRAM size
//     printf("PSRAM size: %d bytes\n", esp_psram_get_size());

//     // BSP
//     led_init();
//     rgb_init();
//     // key_init();
//     exit_init();
//     esptim_int_init(1000000); // 1s enable timer, of which the callback function toggles the LED
//     spi2_init();
//     lcd_init();
//     vTaskDelay(500);

//     // while (1)
//     // {
//     //     printf("Hello-ESP32\r\n");
//     //     // led_toggle();
//     //     // rgb(1, 0, 0);
//     //     // vTaskDelay(200);
//     //     // rgb(0, 1, 0);
//     //     // vTaskDelay(200);
//     //     // rgb(0, 0, 1);
//     //     // vTaskDelay(200);
//     //     // rgb(1, 1, 0);
//     //     // vTaskDelay(200);
//     //     // rgb(1, 0, 1);
//     //     // vTaskDelay(200);
//     //     // rgb(0, 1, 1);
//     //     // vTaskDelay(200);
//     //     // rgb(1, 1, 1);
//     //     // vTaskDelay(200);

//     //     // key = key_scan(0);

//     //     // switch(key)
//     //     // {
//     //     //     case BOOT_PRES:
//     //     //         led_toggle();
//     //     //         rgb_toggle();
//     //     //         break;
//     //     //     default:
//     //     //         break;
//     //     // }

//     //     vTaskDelay(1000);

//     // }

//     while (1)
//     {
//         switch (x)
//         {
//             case 0:
//             {
//                 lcd_clear(WHITE);
//                 break;
//             }
//             case 1:
//             {
//                 lcd_clear(BLACK);
//                 break;
//             }
//             case 2:
//             {
//                 lcd_clear(BLUE);
//                 break;
//             }
//             case 3:
//             {
//                 lcd_clear(RED);
//                 break;
//             }
//             case 4:
//             {
//                 lcd_clear(MAGENTA);
//                 break;
//             }
//             case 5:
//             {
//                 lcd_clear(GREEN);
//                 break;
//             }
//             case 6:
//             {
//                 lcd_clear(CYAN);
//                 break;
//             }
//             case 7:
//             {
//                 lcd_clear(YELLOW);
//                 break;
//             }
//             case 8:
//             {
//                 lcd_clear(BRRED);
//                 break;
//             }
//             case 9:
//             {
//                 lcd_clear(GRAY);
//                 break;
//             }
//             case 10:
//             {
//                 lcd_clear(LGRAY);
//                 break;
//             }
//             case 11:
//             {
//                 lcd_clear(BROWN);
//                 break;
//             }
//         }

//         lcd_show_string(0, 0, 240, 32, 32, "ESP32", RED);
//         lcd_show_string(0, 33, 240, 24, 24, "SPILCD TEST", RED);
//         lcd_show_string(0, 60, 240, 16, 16, "CSW@NTU", RED);
//         x++;

//         if (x == 12)
//         {
//             x = 0;
//         }

//         // rgb_toggle();
//         vTaskDelay(500);
//     }

// }


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


/**
 * @brief Entry point of the program
 * @param None
 * @retval None
 */
void app_main(void)
{
    uint8_t x = 0;
    esp_err_t ret;
    
    
    ret = nvs_flash_init();             /* 初始化NVS */

    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    led_init();                         /* 初始化LED */
    spi2_init();                        /* 初始化SPI2 */
    lcd_init();                         /* 初始化LCD */
    vTaskDelay(500);
    
    while (1)
    {
        switch (x)
        {
            case 0:
            {
                lcd_clear(WHITE);
                break;
            }
            case 1:
            {
                lcd_clear(BLACK);
                break;
            }
            case 2:
            {
                lcd_clear(BLUE);
                break;
            }
            case 3:
            {
                lcd_clear(RED);
                break;
            }
            case 4:
            {
                lcd_clear(MAGENTA);
                break;
            }
            case 5:
            {
                lcd_clear(GREEN);
                break;
            }
            case 6:
            {
                lcd_clear(CYAN);
                break;
            }
            case 7:
            {
                lcd_clear(YELLOW);
                break;
            }
            case 8:
            {
                lcd_clear(BRRED);
                break;
            }
            case 9:
            {
                lcd_clear(GRAY);
                break;
            }
            case 10:
            {
                lcd_clear(LGRAY);
                break;
            }
            case 11:
            {
                lcd_clear(BROWN);
                break;
            }
        }

        lcd_show_string(0, 0, 240, 32, 32, "ESP32", RED);
        lcd_show_string(0, 33, 240, 24, 24, "SPILCD TEST", RED);
        lcd_show_string(0, 60, 240, 16, 16, "CSW@NTU", RED);
        x++;

        if (x == 12)
        {
            x = 0;
        }

        rgb_toggle();
        vTaskDelay(500);
    }
}