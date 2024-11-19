/**
 * @file temp.h
 * @author 
 * @brief This file is to drive the built-in temperature sensor of ESP32
 * @version 1.0
 * @date 2024-11-19
 * @ref Alientek Driver
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __SENSOR_H__
#define __SENSOR_H__

#include "esp_err.h"
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/temperature_sensor.h"

/* Parameter definitions */
#define SENSOR_RANGE_MIN    -10      /* Minimum temperature to be tested */
#define SENSOR_RANGE_MAX    80      /* Maximum temperature to be tested */

/* Function declarations */
void temperature_sensor_init(void); /* Initialize the internal temperature sensor */
short sensor_get_temperature(void); /* Get the temperature value from the internal temperature sensor */

#endif
