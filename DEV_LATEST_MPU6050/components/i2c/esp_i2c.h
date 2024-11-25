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
#define I2C_NUM0_SCL_PIN GPIO_NUM_1
#define I2C_NUM0_SDA_PIN GPIO_NUM_2


/* FUNCTION DECLARATIONS */
/**
 * @description: I2C_NUM_0 Initialization
 * @param None
 * @return esp_err_t
 */
esp_err_t i2c_num0_init(void);