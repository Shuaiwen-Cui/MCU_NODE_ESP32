/**
 * @file setup.h
 * @author SHUAIWEN CUI (SHUAIWEN001@e.ntu.edu.sg)
 * @brief This file contains the configurations to setup the node. SETUP -> BSP/TINYSHM -> MAIN.H -> APP -> MAIN.C
 * @version 1.0
 * @date 2024-11-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __SETUP_H__
#define __SETUP_H__

/* DEPENDENCIES */

// C Stardard Libraries
#include <inttypes.h>

// ESP
#include "esp_system.h" // ESP32 System
// #include "nvs_flash.h"  // ESP32 NVS
// #include "esp_chip_info.h" // ESP32 Chip Info
// #include "esp_psram.h" // ESP32 PSRAM
// #include "esp_flash.h" // ESP32 Flash
#include "esp_log.h" // ESP32 Logging
#include "driver/gpio.h" // ESP32 GPIO
#include "esp_err.h"
#include "sdkconfig.h"

// FreeRTOS
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "freertos/event_groups.h"

/* CONSTANTS */


/* MACROS */

/* GPIO*/

// LED
#define LED_GPIO_PIN    GPIO_NUM_1  /* GPIO port connected to LED */

// RGB
#define RGB_R_GPIO_PIN  GPIO_NUM_4  /* GPIO port connected to RGB Red */
#define RGB_G_GPIO_PIN  GPIO_NUM_5  /* GPIO port connected to RGB Green */
#define RGB_B_GPIO_PIN  GPIO_NUM_6  /* GPIO port connected to RGB Blue */

// KEY
#define BOOT_GPIO_PIN   GPIO_NUM_0  /* GPIO port connected to BOOT key */
#define BOOT_INT_GPIO_PIN   GPIO_NUM_0 /* GPIO port connected to BOOT key interrupt */

/* GPIO States */

// LED
#define LED_PIN_RESET       0
#define LED_PIN_SET         1

// RGB
#define RGB_PIN_RESET       0
#define RGB_PIN_SET         1

// KEY
#define BOOT_PRES           1 










/* VARIBLES */


#endif /* __SETUP_H__ */