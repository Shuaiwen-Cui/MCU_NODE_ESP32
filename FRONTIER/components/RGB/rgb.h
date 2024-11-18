/**
 * @file rgb.h
 * @author SHUAIWEN CUI (SHUAIWEN001@e.ntu.edu.sg)
 * @brief This driver can be used for external RGB LED modules.
 * @version 1.0
 * @date 2024-11-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __RGB_H__
#define __RGB_H__

/* Dependencies */
#include "driver/gpio.h"

/* GPIO Pin Definition */
#define RGB_R_GPIO_PIN  GPIO_NUM_19  /* GPIO port connected to RGB Red */
#define RGB_G_GPIO_PIN  GPIO_NUM_20  /* GPIO port connected to RGB Green */
#define RGB_B_GPIO_PIN  GPIO_NUM_21  /* GPIO port connected to RGB Blue */

/* GPIO States */
#define RGB_PIN_RESET   0
#define RGB_PIN_SET     1

/**
 * @brief       Initialize the RGB LED
 * @param       None
 * @retval      None
 */
void rgb_init(void);

/**
 * @brief       Control the RGB LED
 * @param       r: 1 for on, 0 for off
 * @param       g: 1 for on, 0 for off
 * @param       b: 1 for on, 0 for off
 * @retval      None
 */
void rgb(int r, int g, int b);

/**
 * @brief       Toggle the RGB LED
 * @param       None
 * @retval      None
 */
void rgb_toggle(void);

#endif /*__RGB_H__*/