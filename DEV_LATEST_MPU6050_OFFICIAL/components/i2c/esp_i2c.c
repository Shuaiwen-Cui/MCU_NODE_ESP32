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
 * @description: I2C_BUS0 Initialization
 * @param None
 * @return esp_err_t
 */
esp_err_t i2c_bus0_init(void)
{
    uint8_t ret;
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = (gpio_num_t)I2C_MASTER_SDA_IO;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_io_num = (gpio_num_t)I2C_MASTER_SCL_IO;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = I2C_MASTER_FREQ_HZ;
    conf.clk_flags = I2C_SCLK_SRC_FLAG_FOR_NOMAL;

    ret = i2c_param_config(I2C_MASTER_NUM, &conf);
    TEST_ASSERT_EQUAL_MESSAGE(ESP_OK, ret, "I2C config returned error");

    ret = i2c_driver_install(I2C_MASTER_NUM, conf.mode, 0, 0, 0);
    TEST_ASSERT_EQUAL_MESSAGE(ESP_OK, ret, "I2C install returned error");

    if(ret == ESP_OK)
    {
        ESP_LOGI(TAG, "I2C0 Initialized");
    }
    else
    {
        ESP_LOGE(TAG, "I2C0 Initialization Failed");
    }
    
    return ret;
}