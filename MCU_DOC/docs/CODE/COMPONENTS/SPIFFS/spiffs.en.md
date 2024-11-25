# `spiffs.h` & `spiffs.c`

!!! info 
    `spiffs.h` & `spiffs.c` provide driver functions to initialize and interact with the SPIFFS file system. The functions are used to initialize the SPIFFS file system, read and write files, and retrieve information about the SPIFFS partition.

!!! info 
    SPIFFS is a lightweight file system designed for embedded devices. It is characterized by its low memory footprint, making it suitable for resource-constrained embedded systems. The usage of SPIFFS is similar to a standard file system, allowing access to files via filenames or file handles. In this project, SPIFFS is used to target the onboard FLASH for storing configuration files and data files. Note the distinction between SPIFFS and SD cards with FATFS. SD cards and FATFS are external storage devices accessed via the SPI interface, whereas SPIFFS directly accesses the onboard FLASH.

## SPIFFS.H

```c
/**
 * @file fs.h
 * @author SHUAIWEN CUI (SHUAIWEN001@e.ntu.edu.sg)
 * @brief This file offers functions for file system operation on flash memory using SPIFFS.
 * @version 1.0
 * @date 2024-11-19
 * @ref Alientek SPIFFS Driver
 * @copyright Copyright (c) 2024
 * 
 */

/* DEPENDENCIES */
#include "setup.h"

#include "led.h"
#include "spi.h"
#include "lcd.h"

/* FUNCTIONS */
/**
 * @brief       SPIFFS initialization
 * @param       partition_label: The name of the partition in the partition table
 * @param       mount_point: The path prefix associated with the file system
 * @param       max_files: Maximum number of files that can be opened simultaneously
 * @retval      None
 */
esp_err_t spiffs_init(char *partition_label, char *mount_point, size_t max_files);

/**
 * @brief       Deinitialize SPIFFS
 * @param       partition_label: Partition label
 * @retval      None
 */
esp_err_t spiffs_deinit(char *partition_label);

/**
 * @brief       Test SPIFFS functionality
 * @param       None
 * @retval      None
 */
void spiffs_test(void);
```

## SPIFFS.C

```c
/**
 * @file fs.c
 * @author SHUAIWEN CUI (SHUAIWEN001@e.ntu.edu.sg)
 * @brief This file offers functions for file system operation on flash memory using SPIFFS.
 * @version 1.0
 * @date 2024-11-19
 * @ref Alientek SPIFFS Driver
 * @copyright Copyright (c) 2024
 */

#include "spiffs.h"

/* Variables */
const char               *TAG = "spiffs";

/**
 * @brief       Initialize SPIFFS
 * @param       partition_label: Partition label in the partition table
 * @param       mount_point: Prefix path associated with the file system
 * @param       max_files: Maximum number of files that can be opened simultaneously
 * @retval      None
 */
esp_err_t spiffs_init(char *partition_label, char *mount_point, size_t max_files)
{
    /* Configure parameters for the SPIFFS file system */
    esp_vfs_spiffs_conf_t conf = {
        .base_path = mount_point,
        .partition_label = partition_label,
        .max_files = max_files,
        .format_if_mount_failed = true,
    };

    /* Initialize and mount the SPIFFS file system using the above configuration */
    esp_err_t ret_val = esp_vfs_spiffs_register(&conf);

    /* Check if SPIFFS mount and initialization were successful */
    if (ret_val != ESP_OK)
    {
        if (ret_val == ESP_FAIL)
        {
            printf("Failed to mount or format filesystem\n");
        }
        else if (ret_val == ESP_ERR_NOT_FOUND)
        {
            printf("Failed to find SPIFFS partition\n");
        }
        else
        {
            printf("Failed to initialize SPIFFS (%s)\n", esp_err_to_name(ret_val));
        }

        return ESP_FAIL;
    }

    /* Print SPIFFS storage information */
    size_t total = 0, used = 0;
    ret_val = esp_spiffs_info(conf.partition_label, &total, &used);

    if (ret_val != ESP_OK)
    {
        ESP_LOGI(TAG, "Failed to get SPIFFS partition information (%s)", esp_err_to_name(ret_val));
    }
    else
    {
        ESP_LOGI(TAG, "Partition size: total: %d, used: %d", total, used);
    }

    return ret_val;
}

/**
 * @brief       Unregister SPIFFS
 * @param       partition_label: Partition label in the partition table
 * @retval      None
 */
esp_err_t spiffs_deinit(char *partition_label)
{
    return esp_vfs_spiffs_unregister(partition_label);
}

/**
 * @brief       Test SPIFFS
 * @param       None
 * @retval      None
 */
void spiffs_test(void)
{

    ESP_LOGI(TAG, "Opening file");
    /* Create a write-only file named /spiffs/hello.txt */
    FILE* f = fopen("/spiffs/hello.txt", "w");

    if (f == NULL)
    {
        ESP_LOGE(TAG, "Failed to open file for writing");
        return;
    }

    /* Write data to the file */
    fprintf(f, WRITE_DATA);

    fclose(f);
    ESP_LOGI(TAG, "File written");
 
    /* Check if the target file exists before renaming */
    struct stat st;

    if (stat("/spiffs/foo.txt", &st) == 0) /* Get file information, returns 0 on success */
    {
        /* Remove a file name from the file system. 
           If the name is the last link to a file and no other processes have it open,
           the file is deleted. */
        unlink("/spiffs/foo.txt");
    }
 
    /* Rename the created file */
    ESP_LOGI(TAG, "Renaming file");

    if (rename("/spiffs/hello.txt", "/spiffs/foo.txt") != 0)
    {
        ESP_LOGE(TAG, "Rename failed");
        return;
    }
 
    /* Open the renamed file and read it */
    ESP_LOGI(TAG, "Reading file");
    f = fopen("/spiffs/foo.txt", "r");

    if (f == NULL)
    {
        ESP_LOGE(TAG, "Failed to open file for reading");
        return;
    }

    char line[64];
    fgets(line, sizeof(line), f);
    fclose(f);
    
    char* pos = strchr(line, '\n'); /* Pointer pos points to the first occurrence of '\n' */

    if (pos)
    {
        *pos = '\0';                /* Replace '\n' with '\0' */
    }

    ESP_LOGI(TAG, "Read from file: %s", line);

    lcd_show_string(90, 20, 200, 16, 16, line, RED);
}

```