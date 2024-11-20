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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <sys/time.h>

// ESP
#include "esp_system.h" // ESP32 System
// #include "nvs_flash.h"  // ESP32 NVS
// #include "esp_chip_info.h" // ESP32 Chip Info
// #include "esp_psram.h" // ESP32 PSRAM
// #include "esp_flash.h" // ESP32 Flash
#include "esp_timer.h"         // ESP32 Timer
#include "esp_log.h"           // ESP32 Logging
#include "esp_err.h"           // ESP32 Error
#include "driver/gpio.h"       // ESP32 GPIO
#include "driver/spi_master.h" // ESP32 SPI
#include "sdkconfig.h"         // ESP32 SDK Configuration

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
#define LED_GPIO_PIN GPIO_NUM_1 /* GPIO port connected to LED */

// RGB
#define RGB_R_GPIO_PIN GPIO_NUM_4 /* GPIO port connected to RGB Red */
#define RGB_G_GPIO_PIN GPIO_NUM_5 /* GPIO port connected to RGB Green */
#define RGB_B_GPIO_PIN GPIO_NUM_6 /* GPIO port connected to RGB Blue */

// KEY
#define BOOT_GPIO_PIN GPIO_NUM_0     /* GPIO port connected to BOOT key */
#define BOOT_INT_GPIO_PIN GPIO_NUM_0 /* GPIO port connected to BOOT key interrupt */

// SPI
#define SPI_MOSI_GPIO_PIN GPIO_NUM_11 /* SPI2_MOSI */
#define SPI_CLK_GPIO_PIN GPIO_NUM_12  /* SPI2_CLK */
#define SPI_MISO_GPIO_PIN GPIO_NUM_13 /* SPI2_MISO */

// LCD
#define LCD_NUM_RST GPIO_NUM_38 /* Reset pin */
#define LCD_NUM_CS GPIO_NUM_39  /* Chip select pin */
#define LCD_NUM_WR GPIO_NUM_40  /* Write control pin */
#define LCD_NUM_BL GPIO_NUM_41  /* Backlight control pin */

/* GPIO States */

// LED
#define LED_PIN_RESET 0
#define LED_PIN_SET 1

// RGB
#define RGB_PIN_RESET 0
#define RGB_PIN_SET 1

// KEY
#define BOOT_PRES 1

/* VARIBLES */

// Time Structure
typedef struct
{
    uint8_t hour; /* Hour */
    uint8_t min;  /* Minute */
    uint8_t sec;  /* Second */
    /* Gregorian year, month, day, and week */
    uint16_t year; /* Year */
    uint8_t month; /* Month */
    uint8_t date;  /* Day */
    uint8_t week;  /* Weekday */
} _calendar_obj;

extern _calendar_obj calendar; /* Time structure */

#endif /* __SETUP_H__ */