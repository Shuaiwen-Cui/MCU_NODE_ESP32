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

    // lcd_show_string(0, 0, 200, 16, 16, "RNG Test", RED);
    // lcd_show_string(0, 20, 200, 16, 16, "BOOT:Get Random Num", RED);
    // lcd_show_string(0, 40, 200, 16, 16, "Num:", RED);
    // lcd_show_string(0, 60, 200, 16, 16, "Num[0-9]:", RED);

    /* Display test information */
    lcd_show_string(0, 0, 200, 16, 16, "SPIFFS TEST", RED);
    lcd_show_string(0, 20, 200, 16, 16, "Read file:", BLUE);

    spiffs_test();                                                  /* Run SPIFFS test */

    while (1)
    {
        // switch (background_color)
        // {
        //     case 0:
        //     {
        //         lcd_clear(WHITE);
        //         break;
        //     }
        //     case 1:
        //     {
        //         lcd_clear(BLACK);
        //         break;
        //     }
        //     case 2:
        //     {
        //         lcd_clear(BLUE);
        //         break;
        //     }
        //     case 3:
        //     {
        //         lcd_clear(RED);
        //         break;
        //     }
        //     case 4:
        //     {
        //         lcd_clear(MAGENTA);
        //         break;
        //     }
        //     case 5:
        //     {
        //         lcd_clear(GREEN);
        //         break;
        //     }
        //     case 6:
        //     {
        //         lcd_clear(CYAN);
        //         break;
        //     }
        //     case 7:
        //     {
        //         lcd_clear(YELLOW);
        //         break;
        //     }
        //     case 8:
        //     {
        //         lcd_clear(BRRED);
        //         break;
        //     }
        //     case 9:
        //     {
        //         lcd_clear(GRAY);
        //         break;
        //     }
        //     case 10:
        //     {
        //         lcd_clear(LGRAY);
        //         break;
        //     }
        //     case 11:
        //     {
        //         lcd_clear(BROWN);
        //         break;
        //     }
        // }

        // lcd_show_string(0, 0, 240, 32, 32, "ESP32", RED);
        // lcd_show_string(0, 33, 240, 24, 24, "SPILCD TEST", RED);
        // lcd_show_string(0, 60, 240, 16, 16, "CSW@NTU", RED);
        // background_color++;

        // if (background_color == 12)
        // {
        //     background_color = 0;
        // }

        led_toggle();
        rgb_toggle();
        vTaskDelay(1000);




        // t++;

        // if ((t % 10) == 0)              
        // {
        //     rtc_get_time();
        //     sprintf((char *)tbuf, "Time:%02d:%02d:%02d", calendar.hour, calendar.min, calendar.sec);
        //     printf("Time:%02d:%02d:%02d\r\n", calendar.hour, calendar.min, calendar.sec);
        //     lcd_show_string(0, 0, 210, 16, 16, (char *)tbuf,BLUE);
        //     sprintf((char *)tbuf, "Date:%04d-%02d-%02d", calendar.year, calendar.month, calendar.date);
        //     printf("Date:%02d-%02d-%02d\r\n",  calendar.year,  calendar.month,  calendar.date);
        //     lcd_show_string(0, 30, 210, 16, 16, (char *)tbuf,BLUE);
        //     sprintf((char *)tbuf, "Week:%s", weekdays[calendar.week - 1]);
        //     lcd_show_string(0, 60, 210, 16, 16, (char *)tbuf,BLUE);
        // }

        // if ((t % 20) == 0)
        // {
        //     led_toggle();               
        // }

        // key_val = key_scan(0);

        // if (key_val == gpio_get_level(BOOT_GPIO_PIN))                                         /* Get a random number and display on LCD */
        // {
        //     random_num = rng_get_random_num();
        //     lcd_show_num(30 + 8 * 5, 40, random_num, 10, 16, BLUE);
        // }

        // if ((t % 20) == 0)                                          /* Get a random number [0,9] and display on LCD */
        // {
        //     led_toggle();                                           /* Toggle LED every 200ms */
        //     random_num = rng_get_random_range(0, 9);                    /* Generate a random number in [0,9] range */
        //     lcd_show_num(32 + 8 * 11, 60, random_num, 1, 16, BLUE);     /* Display the random number */
        // }

        // vTaskDelay(10);
        // t++;
    }
}
