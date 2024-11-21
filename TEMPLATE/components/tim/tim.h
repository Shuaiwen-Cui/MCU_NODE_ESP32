/**
 * @file tim.h
 * @author SHUAIWEN CUI (SHUAIWEN001@e.ntu.edu.sg)
 * @brief This file contains the function prototypes for the TIM component.
 * ! This module requires 'eso_timer', do remember to incorporate this in the CMakeLists.txt
 * @version 1.0
 * @date 2024-11-18
 * @ref Alientek Timer Driver
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __TIM_H__
#define __TIM_H__

/* DEPENDENCIES */
#include "setup.h"
#include "led.h"
#include "rgb.h"


/* FUNCTION PROTOTYPES */
/**
 * @brief       Initialize a high-precision timer (ESP_TIMER)
 * @param       tps: Timer period in microseconds (μs). For example, to execute the timer interrupt once every second, 
 *                   set tps = 1s = 1000000μs.
 * @retval      None
 */
void esptim_int_init(uint64_t tps);

/**
 * @brief       Timer callback function
 * @param       arg: No arguments passed
 * @retval      None
 */
void esptim_callback(void *arg); 

#endif /*__TIM_H__*/