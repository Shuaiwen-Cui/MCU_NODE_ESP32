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