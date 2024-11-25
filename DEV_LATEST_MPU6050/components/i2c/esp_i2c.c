/**
 * @file i2c.c
 * @author 
 * @brief This is the source file for the I2C driver.
 * @version 1.0
 * @date 2024-11-24
 *
 * @copyright Copyright (c) 2024
 *
 */

/* DEPENDENCIES */
#include "esp_i2c.h"

/* DEFINITIONS */
static const char *TAG = "I2C";

/* FUNCTIONS */
// I2C0 INIT

/**
 * @description: I2C_NUM_0 Initialization
 * @param None
 * @return esp_err_t
 */
esp_err_t i2c_num0_init(void)
{
    uint8_t res;
    i2c_config_t i2c_config_InitStructure;
    i2c_config_InitStructure.clk_flags = 0;                         // Use default clock settings
    i2c_config_InitStructure.master.clk_speed = 50000;              // Communication speed, typically standard mode (100 kbps) or fast mode (400 kbps). Here, standard mode is used.
    i2c_config_InitStructure.mode = I2C_MODE_MASTER;                // Set to master mode
    i2c_config_InitStructure.scl_io_num = I2C_NUM0_SCL_PIN;         // Communication pin, SCL
    i2c_config_InitStructure.scl_pullup_en = GPIO_PULLUP_ENABLE;    // Enable pull-up for SCL
    i2c_config_InitStructure.sda_io_num = I2C_NUM0_SDA_PIN;         // Communication pin, SDA
    i2c_config_InitStructure.sda_pullup_en = GPIO_PULLUP_ENABLE;    // Enable pull-up for SDA

    res = i2c_param_config(I2C_NUM_0, &i2c_config_InitStructure);   // Configure I2C parameters
    if (res == ESP_OK)
    {
        ESP_LOGI(TAG, "i2c_param_config success");
    }
    else
    {
        ESP_LOGE(TAG, "i2c_param_config failed with error: %d", res);
    }

    res = i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0);   // Install the I2C driver
    if (res == ESP_OK)
    {
        ESP_LOGI(TAG, "i2c_driver_install success");
    }
    else
    {
        ESP_LOGE(TAG, "i2c_driver_install failed with error: %d", res);
    }

    return res;
}
