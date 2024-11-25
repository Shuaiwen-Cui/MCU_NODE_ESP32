/**
 * @file adxl355.h
 * @author SHUAIWEN CUI (SHUAIWEN001@e.ntu.edu.sg)
 * @brief This file is for driving the adxl355 for acceleration measurement.
 * @version 1.0
 * @date 2024-11-21
 * @ref https://github.com/MoustachedBird/ESP32_seismic_datalogger.git
 * @copyright Copyright (c) 2024
 *
 */

#include "setup.h"

/*Configurates SPI clock and SPI PINS*/
void adxl355_config_spi(void);

/*Configurates the accelerometer's sample rate*/
void adxl355_100hz_rate(void);

/*Configurates and turns on the accelerometer (+-2G range)*/
void adxl355_range_conf(void);

/*Read acceleration values*/
void adxl355_read_accl(uint8_t *data_received, uint8_t size_buffer);

#define READ_FLAG_ADXL355 0x01
#define WRITE_FLAG_ADXL355 0x00

//Range values
#define RANGE_2G  0x01
#define RANGE_4G  0x02
#define RANGE_8G  0x03

//Registers addresses
#define ZDATA3  (0x0E << 1)
#define YDATA3  (0x0B << 1)
#define XDATA3  (0x08 << 1)
