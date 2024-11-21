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
#include <stdint.h>
#include <stddef.h>
#include <inttypes.h>
#include <sys/unistd.h>
#include <sys/time.h>
#include <sys/param.h>
#include <sys/stat.h>

// ESP
#include "esp_system.h" // ESP32 System
// #include "nvs_flash.h"  // ESP32 NVS
#include "esp_chip_info.h" // ESP32 Chip Info
// #include "esp_psram.h" // ESP32 PSRAM
// #include "esp_flash.h" // ESP32 Flash
#include "esp_random.h"        // ESP32 Random
#include "esp_timer.h"         // ESP32 Timer
#include "esp_log.h"           // ESP32 Logging
#include "esp_err.h"           // ESP32 Error
#include "driver/gpio.h"       // ESP32 GPIO
#include "driver/spi_master.h" // ESP32 SPI
#include "driver/sdspi_host.h" // ESP32 SD SPI
#include "driver/spi_common.h" // ESP32 SPI Common
#include "driver/sdmmc_host.h" // ESP32 SDMMC
#include "sdkconfig.h"         // ESP32 SDK Configuration
#include "esp_attr.h"         // ESP32 Attribute
#include "esp_cpu.h"         // ESP32 CPU
#include "soc/wdev_reg.h"   // ESP32 WDEV Register
#include "esp_private/esp_clk.h" // ESP32 Clock
#include "esp_vfs.h" // ESP32 VFS
#include "esp_spiffs.h" // ESP32 SPIFFS
#include "esp_vfs_fat.h" // ESP32 VFS FAT
#include "sdmmc_cmd.h" // ESP32 SDMMC

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

// SD - note the pins below are actually the same as the SPI pins.
#define USE_SPI_MODE
#ifdef USE_SPI_MODE
// 使用SPI模式时的引脚映射通过此映射，SD卡既可以在SPI模式下使用，也可以在1线SD模式下使用。
// 请注意，在SD模式下，需要在CS线上上拉。
#define PIN_NUM_MISO  GPIO_NUM_13
#define PIN_NUM_MOSI  GPIO_NUM_11
#define PIN_NUM_CLK   GPIO_NUM_12
#define PIN_NUM_CS    GPIO_NUM_2
#endif //USE_SPI_MODE

/* GPIO States */

// LED
#define LED_PIN_RESET 0
#define LED_PIN_SET 1

// RGB
#define RGB_PIN_RESET 0
#define RGB_PIN_SET 1

// KEY
#define BOOT_PRES 1

/* File System */

// SPIFFS
#define DEFAULT_FD_NUM          5
#define DEFAULT_MOUNT_POINT     "/spiffs"
#define WRITE_DATA              "ESP32-S3\r\n"

// SD Card
#define MOUNT_POINT     "/sdcard" 
#define SD_MAX_CHAR_SIZE    64

// SPI DMA Channel
#ifndef SPI_DMA_CHAN
#define SPI_DMA_CHAN    1
#endif //SPI_DMA_CHAN

// 在测试SD和SPI模式时，请记住，一旦在SPI模式下初始化了卡，就无法在没有切换卡电源的情况下在SD模式下重新将其初始化。

/* VARIBLES */

// TAGs
extern const char *TAG_SD;

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