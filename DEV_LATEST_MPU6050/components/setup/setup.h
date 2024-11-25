/**
 * @file setup.h
 * @author SHUAIWEN
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

// C Standard Libraries
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
#include "driver/i2c.h"        // ESP32 I2C
#include "driver/i2c_master.h"        // ESP32 I2C
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
#define SPI2_MOSI_GPIO_PIN GPIO_NUM_11 /* SPI2_MOSI */
#define SPI2_CLK_GPIO_PIN GPIO_NUM_12  /* SPI2_CLK */
#define SPI2_MISO_GPIO_PIN GPIO_NUM_13 /* SPI2_MISO */

#define SPI3_MOSI_GPIO_PIN GPIO_NUM_40 /* SPI3_MOSI */
#define SPI3_MISO_GPIO_PIN GPIO_NUM_41 /* SPI3_MISO */
#define SPI3_CLK_GPIO_PIN GPIO_NUM_42  /* SPI3_CLK */

// LCD
#define LCD_NUM_RST GPIO_NUM_38 /* Reset pin */
#define LCD_NUM_CS GPIO_NUM_39  /* Chip select pin */
#define LCD_NUM_WR GPIO_NUM_40  /* Write control pin */
#define LCD_NUM_BL GPIO_NUM_41  /* Backlight control pin */

// SD - note the pins below are actually the same as the SPI pins.
#define USE_SPI_MODE
#ifdef USE_SPI_MODE
// When using SPI mode, the pin mapping allows the SD card to be used in both SPI mode and 1-line SD mode.
// Note: When in SD mode, a pull-up resistor is required on the CS line.
#define SD_PIN_NUM_CS    GPIO_NUM_2
#define SD_PIN_NUM_MOSI  GPIO_NUM_11
#define SD_PIN_NUM_CLK   GPIO_NUM_12
#define SD_PIN_NUM_MISO  GPIO_NUM_13
#endif //USE_SPI_MODE

// SPI3 - ADXL355
#define CS_ADXL355           GPIO_NUM_39
#define ADXL355_PIN_NUM_MOSI GPIO_NUM_40
#define ADXL355_PIN_NUM_MISO GPIO_NUM_41
#define ADXL355_PIN_NUM_CLK  GPIO_NUM_42

// I2C
#define I2C_NUM0_SCL_PIN GPIO_NUM_1
#define I2C_NUM0_SDA_PIN GPIO_NUM_2

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

// Note: When testing SD and SPI modes, remember that once the card has been initialized in SPI mode, 
// it cannot be reinitialized in SD mode without switching card power.

/* VARIABLES */

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
