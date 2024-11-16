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
#include "dht11.h"

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

    int temp, humidity;

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

    // BSP
    led_init();
    rgb_init();
    DHT11_Init();

    while (1)
    {
        // printf("Hello-ESP32\r\n");
        led_toggle();
        rgb(1, 0, 0);
        vTaskDelay(200);
        rgb(0, 1, 0);
        vTaskDelay(200);
        rgb(0, 0, 1);
        vTaskDelay(200);
        rgb(1, 1, 0);
        vTaskDelay(200);
        rgb(1, 0, 1);
        vTaskDelay(200);
        rgb(0, 1, 1);
        vTaskDelay(200);
        rgb(1, 1, 1);
        vTaskDelay(200);
        DHT11_StartGet(&temp, &humidity);
        ESP_LOGI("dht11","Temperature: %d, Humidity: %d", temp/10, humidity);
    }

}