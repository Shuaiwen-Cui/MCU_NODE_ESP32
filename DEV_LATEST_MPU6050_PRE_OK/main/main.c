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

/* Variables */
uint8_t ID;								//定义用于存放ID号的变量
int16_t AX, AY, AZ, GX, GY, GZ;			//定义用于存放各个数据的变量

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
    lcd_clear(WHITE);

    lcd_show_string(0, 0, 200, 16, 16, "SD Initialized!", RED);

    sd_card_test_filesystem();                                        /* Run SD card test */


    MPU6050_Init();
    ID=MPU6050_GetID();//获取设备ID
    ESP_LOGI("MPU6050 ID","#%x\n",ID);

    // sd_card_unmount();

    while (1)
    {
        // led_toggle();
        // rgb_toggle();
        // vTaskDelay(1000);
		MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);//把六个变量的地址传递过去
        //显示六元组数据
        ESP_LOGI("MPU6050", "AccX:%d, AccY:%d, AccZ:%d, GyroX:%d, GyroY:%d, GyroZ:%d\n", AX, AY, AZ, GX, GY, GZ);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
