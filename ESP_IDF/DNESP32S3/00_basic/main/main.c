#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "esp_system.h"
#include "esp_chip_info.h"
#include "esp_psram.h"
#include "esp_flash.h"

/**
 * @brief   Program entry point
 * @param   None
 * @retval  None
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
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    // Get FLASH size
    esp_flash_get_size(NULL, &flash_size);
    // Define a variable for chip information structure
    esp_chip_info(&chip_info);
    // Retrieve and display the number of CPU cores
    printf("Cores: %d\n", chip_info.cores);
    printf("FLASH size: %ld MB\n", flash_size / (1024 * 1024));
    // Retrieve and display PSRAM size
    printf("PSRAM size: %d bytes\n", esp_psram_get_size());

    while(1)
    {
        printf("Hello-ESP32\r\n");
        vTaskDelay(1000);
    }
}
