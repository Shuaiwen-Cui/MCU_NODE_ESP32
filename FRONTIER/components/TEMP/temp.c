/**
 * @file temp.c
 * @author 
 * @brief This file is to drive the built-in temperature sensor of ESP32
 * @version 1.0
 * @date 2024-11-19
 * @ref Alientek Driver
 * @copyright Copyright (c) 2024
 * 
 */

#include "temp.h"

esp_err_t rev_flag;
temperature_sensor_handle_t temp_handle = NULL; /* Temperature sensor handle */

/**
 * @brief       Initialize the internal temperature sensor
 * @param       None
 * @retval      None
 */
void temperature_sensor_init(void)
{
    temperature_sensor_config_t temp_sensor;
    
    temp_sensor.range_min = SENSOR_RANGE_MIN;   /* Minimum temperature to be tested */
    temp_sensor.range_max = SENSOR_RANGE_MAX;   /* Maximum temperature to be tested */

    rev_flag |= temperature_sensor_install(&temp_sensor, &temp_handle);
    ESP_ERROR_CHECK(rev_flag);
}

/**
 * @brief       Get the temperature value from the internal temperature sensor
 * @param       None
 * @retval      Returns the internal temperature value
 */
short sensor_get_temperature(void)
{
    float temp;

    /* Enable the temperature sensor */
    rev_flag |= temperature_sensor_enable(temp_handle);

    /* Retrieve sensor data */
    rev_flag |= temperature_sensor_get_celsius(temp_handle, &temp);

    /* Disable the temperature sensor after use to save power */
    rev_flag |= temperature_sensor_disable(temp_handle);
    ESP_ERROR_CHECK(rev_flag);

    return temp;
}
