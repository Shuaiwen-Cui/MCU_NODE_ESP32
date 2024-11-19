# TF CARD (SD CARD) Operation - SPI Mode

## Introduction

!!! info "SD Card Overview"
    Many microcontroller systems require high-capacity storage devices to store data. Common options include USB drives, FLASH chips, and SD cards. Each has its advantages, but overall, SD cards are the most suitable for microcontroller systems. They offer large capacities (over 32GB), support SPI/SDIO interfaces, and come in various sizes (standard SD card and Micro SD card sizes), meeting the requirements of different applications.

    With just a few IO pins, you can extend storage capacity to 32GB or more, with a wide range of choices from tens of megabytes to tens of gigabytes. They are easy to replace, simple to program, and are the preferred choice for large-capacity external storage in microcontroller systems.

    The ZD Atom ESP32-S3 minimal system board uses a Micro SD card interface with a self-locking card slot. The SD SPI host driver is implemented based on the SPI Master Driver. With the SPI host driver, the SD card and other SPI devices can share the same SPI bus. The SPI host driver handles exclusive access from different tasks.

!!! info
    A complete SD card operation process involves the host (e.g., a microcontroller) initiating a "command." The SD card determines whether to send a response or data based on the command's content. For read/write operations, the host must also send a command to stop reading/writing data to end the operation. This means that after the host sends a command, the SD card may not respond or provide data, depending on the command's meaning.

!!! info "Card Modes"
    SD cards have two effective operation modes: "Card Identification Mode" and "Data Transfer Mode." Based on the operation method, there are SD mode and SPI mode. The ZD Atom ESP32-S3 minimal system board uses SPI mode.

## Key Steps

1. SD card initialization (SPI mode/SDIO mode)
2. SD card read/write operations

!!! warning
    The ESP32's SDIO driver mode and SPI driver mode are not compatible. You can only choose one driver mode.

## Use Case

This experiment introduces the following functionality: After a series of initializations, an SD card initialization condition is used within a `while` loop to check whether the SD card is successfully initialized. If initialization succeeds, SD card parameters will be output to the serial terminal or VSCode terminal, and the total capacity and remaining capacity will be displayed on the LCD. The LED blinks to indicate the program is running.

## Resources Used

1. **LED**
   - LED: IO0
2. **0.96-inch LCD**
3. **SD Card**
   - CS: IO2
   - SCK: IO12
   - MOSI: IO11
   - MISO: IO13

## Connection Diagram

This experiment connects the SD card to the ESP32-S3 using the SPI interface. The DNESP32S3M minimal system board has an onboard Micro SD card slot for connecting the SD card. The schematic for connecting the SD card to the ESP32-S3 is shown below.

![TF](TF.png)

## ESP-IDF API

To use SD card-related functionality, you must first import the required files.

```c
#include "driver/sdspi_host.h"
#include "driver/spi_common.h"
#include "sdmmc_cmd.h"
#include "driver/sdmmc_host.h"
#include "spi.h"
```

## Key Functions

### Mount SD Card

```c
esp_err_t esp_vfs_fat_sdspi_mount(const char* base_path,
                                  const sdmmc_host_t* host_config_input,
                                  const sdspi_device_config_t* slot_config,
                                  const esp_vfs_fat_mount_config_t*mount_config,
                                  sdmmc_card_t** out_card);
```



| Parameter         | Description                                                                                                             |
| :---------------- | :---------------------------------------------------------------------------------------------------------------------- |
| `base_path`       | Mount point, the path where the partition should be registered (e.g., "/sdcard").                                       |
| `host_config_input` | SDMMC host configuration, a pointer to a structure describing the SDMMC host. This structure can be initialized using the `SDSPI_HOST_DEFAULT` macro. |
| `slot_config`     | SD card configuration, a pointer to a structure with slot configuration. For SPI peripherals, pass a pointer to an `sdspi_device_config_t` structure initialized using `sdspi_device_config_DEFAULT`. |
| `mount_config`    | Mount configuration, a pointer to an `esp_vfs_fat_mount_config_t` structure to configure the FAT file system mount options. |
| `out_card`        | If not `NULL`, a pointer to the card information structure will be returned through this parameter.                      |


| Return Value               | Description                                                                                                   |
| :------------------------- | :----------------------------------------------------------------------------------------------------------- |
| `ESP_OK`                   | Operation succeeded.                                                                                         |
| `ESP_ERR_INVALID_STATE`    | Invalid state, if `esp_vfs_fat_sdmmc_mount` has already been called.                                         |
| `ESP_ERR_NO_MEM`           | Memory allocation failure.                                                                                   |
| `ESP_FAIL`                 | If the partition cannot be mounted, other error codes from the SDMMC or SPI driver, SDMMC protocol, or FATFS driver. |

### Unmount SD Card

```c
esp_err_t esp_vfs_fat_sdspi_unmount(const char* base_path, sdmmc_card_t* card);
```

## Parameter Description

| Parameter   | Description                                                   |
| :---------- | :------------------------------------------------------------ |
| `base_path` | Mount point, the path where the partition should be registered (e.g., "/sdcard"). |
| `card`      | SD/MMC card structure.                                        |

## Return Value Description

| Return Value           | Description                                                  |
| :--------------------- | :----------------------------------------------------------- |
| `ESP_OK`               | Operation succeeded.                                         |
| `ESP_ERR_INVALID_ARG`  | If the `card` parameter is not registered.                   |
| `ESP_ERR_INVALID_STATE`| If `esp_vfs_fat_sdmmc_mount` has not been called yet.        |

## Driver Code

### spi_sdcard.h

```c
/**
 * @file spi_sdcard.h
 * @author SHUAIWEN CUI (SHUAIWEN001@e.ntu.edu.sg)
 * @brief This file is for SD card initialization and related functions
 * @version 1.0
 * @date 2024-11-19
 * @ref Alientek SD card driver.
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __SPI_SDCARD_H__
#define __SPI_SDCARD_H__

#include <unistd.h>
#include "esp_vfs_fat.h"
#include "driver/sdspi_host.h"
#include "driver/spi_common.h"
#include "sdmmc_cmd.h"
#include "driver/sdmmc_host.h"
#include "spi.h"


/* Pin definitions */
#define SD_NUM_CS       GPIO_NUM_2
#define MOUNT_POINT     "/0:"

/* Function declarations */
esp_err_t sd_spi_init(void);                                                /* Initialize SD card */
void sd_get_fatfs_usage(size_t *out_total_bytes, size_t *out_free_bytes);   /* Get SD card usage information */

#endif

```

### spi_sdcard.c

```c
/**
 * @file spi_sdcard.c
 * @author SHUAIWEN CUI
 * @brief This file is for SD card initialization and related functions
 * @version 1.0
 * @date 2024-11-19
 * @ref Alientek SD card driver.
 */

#include "spi_sdcard.h"

spi_device_handle_t MY_SD_Handle = NULL;                            /* SD card handle */
sdmmc_card_t *card;                                                 /* SD/MMC card structure */
const char mount_point[] = MOUNT_POINT;                             /* Mount point/root directory */
esp_err_t ret = ESP_OK;
esp_err_t mount_ret = ESP_OK;

/**
 * @brief       Initialize SD card
 * @param       None
 * @retval      esp_err_t
 */
esp_err_t sd_spi_init(void)
{
    if (MY_SD_Handle != NULL)                                       /* Re-mount or reinitialize SD card */
    {
        spi_bus_remove_device(MY_SD_Handle);                        /* Remove SD card device from SPI bus */

        if (mount_ret == ESP_OK)
        {
            esp_vfs_fat_sdcard_unmount(mount_point, card);          /* Unmount file system */
        }
    }

    /* SPI driver interface configuration. SPI SD card clock is 20-25MHz */
    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = 20 * 1000 * 1000,                         /* SPI clock speed */
        .mode = 0,                                                  /* SPI mode 0 */
        .spics_io_num = SD_NUM_CS,                                  /* Chip select pin */
        .queue_size = 7,                                            /* Queue size: 7 transactions */
    };

    /* Add SPI bus device */
    ret = spi_bus_add_device(SPI2_HOST, &devcfg, &MY_SD_Handle);

    /* File system mount configuration */
    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = false,                            /* If mounting fails: true to reformat, false otherwise */
        .max_files = 5,                                             /* Maximum number of open files */
        .allocation_unit_size = 4 * 1024 * sizeof(uint8_t)          /* Allocation unit size of disk clusters */
    };

    /* SD card host configuration */
    sdmmc_host_t host = SDSPI_HOST_DEFAULT();

    /* SD card pin configuration */
    sdspi_device_config_t slot_config = {0};
    slot_config.host_id   = host.slot;
    slot_config.gpio_cs   = SD_NUM_CS;
    slot_config.gpio_cd   = GPIO_NUM_NC;
    slot_config.gpio_wp   = GPIO_NUM_NC;
    slot_config.gpio_int  = GPIO_NUM_NC;

    mount_ret = esp_vfs_fat_sdspi_mount(mount_point, &host, &slot_config, &mount_config, &card);      /* Mount file system */
    ret |= mount_ret;

    return ret;
}

/**
 * @brief       Get SD card usage information
 * @param       out_total_bytes: Total size
 * @param       out_free_bytes: Free size
 * @retval      None
 */
void sd_get_fatfs_usage(size_t *out_total_bytes, size_t *out_free_bytes)
{
    FATFS *fs;
    size_t free_clusters;
    int res = f_getfree("0:", (DWORD *)&free_clusters, &fs);
    assert(res == FR_OK);
    size_t total_sectors = (fs->n_fatent - 2) * fs->csize;
    size_t free_sectors = free_clusters * fs->csize;

    size_t sd_total = total_sectors / 1024;
    size_t sd_total_KB = sd_total * fs->ssize;
    size_t sd_free = free_sectors / 1024;
    size_t sd_free_KB = sd_free * fs->ssize;

    /* Assuming total size is less than 4GiB, which should be true for SPI flash */
    if (out_total_bytes != NULL)
    {
        *out_total_bytes = sd_total_KB;
    }
    
    if (out_free_bytes != NULL)
    {
        *out_free_bytes = sd_free_KB;
    }
}

```

### main.c

```c
/**
 * @file main.c
 * @author
 * @brief Main application to demonstrate the use of ESP32 internal temperature sensor
 * @version 1.0
 * @date 2024-11-17
 *
 * @copyright Copyright (c) 2024
 *
 */

/* Dependencies */
// Basic
#include "esp_system.h"
#include "esp_chip_info.h"
#include "esp_psram.h"
#include "esp_flash.h"
#include "nvs_flash.h"
#include "esp_log.h"

// RTOS
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// BSP
#include "led.h"
#include "rgb.h"
#include "key.h"
#include "exit.h"
#include "lcd.h"
#include "spi.h"
#include "esp_rtc.h"
#include "temp.h"
#include "rng.h"
#include "spi_sdcard.h"

void app_main(void)
{
    esp_err_t ret;
    size_t bytes_total, bytes_free;                     /* Total and free space of the SD card */

    ret = nvs_flash_init();                             /* Initialize NVS */

    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    led_init();                                         /* Initialize LED */
    spi2_init();                                        /* Initialize SPI */
    lcd_init();                                         /* Initialize LCD */

    while (sd_spi_init())                               /* SD card not detected */
    {
        lcd_show_string(0, 0, 200, 16, 16, "SD Card Error!", RED);
        vTaskDelay(500);
        lcd_show_string(0, 20, 200, 16, 16, "Please Check!", RED);
        vTaskDelay(500);
    }

    lcd_show_string(0, 0, 200, 16, 16, "SD Card OK!", RED);
    lcd_show_string(0, 20, 200, 16, 16, "Total:       MB", RED);
    lcd_show_string(0, 40, 200, 16, 16, "Free :       MB", RED);
    sd_get_fatfs_usage(&bytes_total, &bytes_free);

    lcd_show_num(60, 20, (int)bytes_total / 1024, 5, 16, BLUE);
    lcd_show_num(60, 40, (int)bytes_free / 1024, 5, 16, BLUE);

    while (1)
    {
        led_toggle();
        vTaskDelay(500);
    }
}

```