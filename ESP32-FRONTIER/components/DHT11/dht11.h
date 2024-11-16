/**
 * @file dht11.h
 * @author 
 * SHUAIWEN CUI (SHUAIWEN001@e.ntu.edu.sg)
 * @brief DHT11 sensor driver header file
 * @version 1.0
 * @date 2024-11-16
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef __DHT11_H__
#define __DHT11_H__
#include <stdint.h>

#define DHT11_GPIO_PIN GPIO_NUM_4

/** 
 * @brief Initialize the DHT11 sensor.
 * @param void
 * @return None
 */
void DHT11_Init(void);

/**
 * @brief Retrieve data from the DHT11 sensor.
 * @param temp_x10 Pointer to store the temperature value multiplied by 10.
 * @param humidity Pointer to store the humidity value.
 * @return int Status of the operation (0 for success, -1 for error).
 */
int DHT11_StartGet(int *temp_x10, int *humidity);

#endif /*__DHT11_H__*/
