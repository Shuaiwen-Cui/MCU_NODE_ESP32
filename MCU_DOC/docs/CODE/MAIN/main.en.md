# `main.h` & `main.c`

!!! info
    Regarding programming, the `main.c` file can be quite different from app to app. The following is an example of a `main.c` file that initializes the ESP32 and the board peripherals, and then runs a test on the SD card and SPIFFS.
## main.h   

```c
/**
 * @file main.h
 * @author SHUAIWEN CUI (SHUAIWEN001@e.ntu.edu.sg)
 * @brief 
 * @version 1.0
 * @date 2024-11-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __MAIN_H__
#define __MAIN_H__

/* DEPENDENCIES */
// ESP
#include "esp_system.h" // ESP32 System
#include "nvs_flash.h"  // ESP32 NVS
#include "esp_chip_info.h" // ESP32 Chip Info
#include "esp_psram.h" // ESP32 PSRAM
#include "esp_flash.h" // ESP32 Flash
#include "esp_log.h" // ESP32 Logging

// BSP
#include "led.h"
#include "rgb.h"
#include "key.h"
#include "exit.h"
#include "spi.h"
#include "lcd.h"
#include "tim.h"
#include "esp_rtc.h"
#include "rng.h"
#include "spiffs.h"
#include "spi_sdcard.h"

/* CONSTANTS */


/* MACROS */


/* VARIABLES */

// LCD Background Color 
uint8_t background_color = 0;

// Weekdays
char* weekdays[]={"Sunday","Monday","Tuesday","Wednesday",
                  "Thursday","Friday","Saterday"};

// Time buffer
uint8_t tbuf[40];
uint8_t t = 0;

// Random Number
uint32_t random_num;

// Key Value
uint8_t key_val;


#endif /* __MAIN_H__ */

```

## main.c

```c
/**
 * @file main.c
 * @author SHUAIWEN CUI (SHUAIWEN001@e.ntu.edu.sg)
 * @brief 
 * @version 1.0
 * @date 2024-11-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */

/* Dependencies */  
#include "main.h"

/**
 * @brief Entry point of the program
 * @param None
 * @retval None
 */
void app_main(void)
{
    esp_err_t ret;
    uint32_t flash_size;
    esp_chip_info_t chip_info;

    // Initialize NVS
    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase()); // Erase if needed
        ret = nvs_flash_init();
    }

    // Get FLASH size
    esp_flash_get_size(NULL, &flash_size);
    esp_chip_info(&chip_info);

    // Display CPU core count
    printf("CPU Cores: %d\n", chip_info.cores);

    // Display FLASH size
    printf("Flash size: %ld MB flash\n", flash_size / (1024 * 1024));

    // Display PSRAM size
    printf("PSRAM size: %d bytes\n", esp_psram_get_size());

    // BSP Initialization
    led_init();
    rgb_init();
    key_init();
    exit_init();
    spi2_init();
    lcd_init();
    // esptim_int_init(1000000); // 1s enable timer, of which the callback function toggles the LED
    rtc_set_time(2024,11,20,18,22,00); 
    spiffs_init("storage", DEFAULT_MOUNT_POINT, DEFAULT_FD_NUM);    /* Initialize SPIFFS */

    // spiffs_test();                                                  /* Run SPIFFS test */
    while (sd_card_init())                               /* SD card not detected */
    {
        lcd_show_string(0, 0, 200, 16, 16, "SD Card Error!", RED);
        vTaskDelay(500);
        lcd_show_string(0, 20, 200, 16, 16, "Please Check!", RED);
        vTaskDelay(500);
    }

    // clean the screen
    lcd_clear(WHITE);

    lcd_show_string(0, 0, 200, 16, 16, "SD Initialized!", RED);

    sd_card_test_filesystem();                                        /* Run SD card test */

    // sd_card_unmount();

    while (1)
    {
        led_toggle();
        rgb_toggle();
        vTaskDelay(1000);
    }
}

```