/**
 * @file i2c.h
 * @author SHUAIWEN CUI (SHUAIWEN001@e.ntu.edu.sg)
 * @brief This is the header file for the I2C driver.
 * @version 1.0
 * @date 2024-11-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */

/* DEPENDENCIES */
#include "setup.h"

/* DEFINITIONS */
#define I2C_MASTER_SCL_IO GPIO_NUM_0     /*!< gpio number for I2C master clock */
#define I2C_MASTER_SDA_IO GPIO_NUM_1       /*!< gpio number for I2C master data  */
#define I2C_MASTER_NUM I2C_NUM_0  /*!< I2C port number for master dev */
#define I2C_MASTER_FREQ_HZ 100000 /*!< I2C master clock frequency */

/* FUNCTION DECLARATIONS */
/**
 * @description: I2C_BUS0 Initialization
 * @param None
 * @return esp_err_t
 */
esp_err_t i2c_bus0_init(void);