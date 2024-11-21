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
    spi3_init();
    lcd_init();
    esptim_int_init(1000000); // 1s enable timer, of which the callback function toggles the LED
    rtc_set_time(2024,11,20,18,22,00); 
    spiffs_init("storage", DEFAULT_MOUNT_POINT, DEFAULT_FD_NUM);    /* Initialize SPIFFS */
    adxl355_config_spi();                                           /* Configure SPI for ADXL355 */
    adxl355_100hz_rate();                                           /* Configure ADXL355 sampling rate */
    adxl355_range_conf();                                           /* Configure ADXL355 range */

    printf("ADXL355 initialized and configured successfully.\n");

    // lcd_show_string(0, 0, 200, 16, 16, "RNG Test", RED);
    // lcd_show_string(0, 20, 200, 16, 16, "BOOT:Get Random Num", RED);
    // lcd_show_string(0, 40, 200, 16, 16, "Num:", RED);
    // lcd_show_string(0, 60, 200, 16, 16, "Num[0-9]:", RED);

    /* Display test information */
    // lcd_show_string(0, 0, 200, 16, 16, "SPIFFS TEST", RED);
    // lcd_show_string(0, 20, 200, 16, 16, "Read file:", BLUE);

    // spiffs_test();                                                  /* Run SPIFFS test */
    while (sd_card_init())                               /* SD card not detected */
    {
        lcd_show_string(0, 0, 200, 16, 16, "SD Card Error!", RED);
        vTaskDelay(500);
        lcd_show_string(0, 20, 200, 16, 16, "Please Check!", RED);
        vTaskDelay(500);
    }

    // clean the screen
    // lcd_clear(WHITE);

    lcd_show_string(0, 0, 200, 16, 16, "SD Initialized!", RED);

    sd_card_test_filesystem();                                        /* Run SD card test */

    vTaskDelay(pdMS_TO_TICKS(10000));

    // sd_card_unmount();

    // Variables to hold acceleration data
    uint8_t accel_data[9]; // 9 bytes: X, Y, Z data (3 bytes each)

    while (1) {
        // Read acceleration data
        adxl355_read_accl(accel_data, sizeof(accel_data));

        // Process the received data
        int32_t accel_x = ((accel_data[0] << 16) | (accel_data[1] << 8) | accel_data[2]) >> 4;
        int32_t accel_y = ((accel_data[3] << 16) | (accel_data[4] << 8) | accel_data[5]) >> 4;
        int32_t accel_z = ((accel_data[6] << 16) | (accel_data[7] << 8) | accel_data[8]) >> 4;

        // Convert raw data to physical units (e.g., g)
        float scale_factor = 0.0000039; // Example scale factor for ±2g range
        float x_g = accel_x * scale_factor;
        float y_g = accel_y * scale_factor;
        float z_g = accel_z * scale_factor;

        // Print acceleration values
        printf("X: %.5f g, Y: %.5f g, Z: %.5f g\n", x_g, y_g, z_g);

        // Showing on the LCD
        lcd_show_string(0, 0, 200, 16, 16, "ADXL355 Test", RED);
        lcd_show_string(0, 20, 200, 16, 16, "X:", RED);
        lcd_show_string(0, 40, 200, 16, 16, "Y:", RED);
        lcd_show_string(0, 60, 200, 16, 16, "Z:", RED);

        // Delay before next read (e.g., 100 ms)
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

}
