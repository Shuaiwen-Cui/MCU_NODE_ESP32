/**
 * @file spi_sdcard.h
 * @author SHUAIWEN CUI (SHUAIWEN001@e.ntu.edu.sg)
 * @brief This file is for SD card initialization and related functions
 * @version 1.0
 * @date 2024-11-19
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __SPI_SDCARD_H__
#define __SPI_SDCARD_H__

/* DEPENDENCIES */
#include "setup.h"

/* VARIABLES */
extern sdmmc_card_t *card;

/* FUNCTIONS */

/**
 * @brief Initialize the SD card
 * @param None
 * @retval esp_err_t
 */
esp_err_t sd_card_init(void);

/**
 * @brief Test file operations on the SD card
 * @param None
 * @retval esp_err_t
 */
esp_err_t sd_card_test_filesystem(void);

/**
 * @brief Unmount the File System and SPI Bus
 * @param None
 * @retval esp_err_t
 */
esp_err_t sd_card_unmount(void);
#endif