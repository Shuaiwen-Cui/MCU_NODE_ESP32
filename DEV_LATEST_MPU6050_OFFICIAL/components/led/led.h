/**
 * @file led.h
 * @author SHUAIWEN CUI (SHUAIWEN001@e.ntu.edu.sg)
 * @brief The led here indicates the onboard red led on the Alientek DNESP32S3M minimal development board.
 * @version 1.0
 * @date 2024-11-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __LED_H__
#define __LED_H__

/* DEPENDENCIES */
#include "setup.h"

/* FUNCTIONS */
/**
 * @brief       Initialize the LED
 * @param       None
 * @retval      None
 */
void led_init(void);

/**
 * @brief       Control the LED
 * @param       x: 1 for on, 0 for off
 * @retval      None
 */
void led(int x);

/**
 * @brief       Toggle the LED
 * @param       None
 * @retval      None
 */
void led_toggle(void);

#endif /*__LED_H__*/