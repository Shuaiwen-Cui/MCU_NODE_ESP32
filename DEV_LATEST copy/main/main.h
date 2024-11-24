/**
 * @file main.h
 * @author SHUAIWEN CUI (SHUAIWEN001@e.ntu.edu.sg)
 * @brief 
 * @version 1.0
 * @date 2024-11-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __MAIN_H__
#define __MAIN_H__

/* DEPENDENCIES */
// ESP
#include "esp_system.h" // ESP32 System
#include "nvs_flash.h"  // ESP32 NVS
#include "esp_chip_info.h" // ESP32 Chip Info
#include "esp_psram.h" // ESP32 PSRAM
#include "esp_flash.h" // ESP32 Flash
#include "esp_log.h" // ESP32 Logging

// BSP
#include "led.h"
#include "rgb.h"
#include "key.h"
#include "exit.h"
#include "spi.h"
#include "lcd.h"
#include "tim.h"
#include "esp_rtc.h"
#include "rng.h"
#include "spiffs.h"
#include "spi_sdcard.h"


/* CONSTANTS */


/* MACROS */


/* VARIABLES */

// LCD Background Color 
uint8_t background_color = 0;

// Weekdays
char* weekdays[]={"Sunday","Monday","Tuesday","Wednesday",
                  "Thursday","Friday","Saterday"};

// Time buffer
uint8_t tbuf[40];
uint8_t t = 0;

// Random Number
uint32_t random_num;

// Key Value
uint8_t key_val;


#endif /* __MAIN_H__ */