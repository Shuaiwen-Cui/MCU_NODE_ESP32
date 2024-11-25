/**
 * @file mpu6050.h
 * @author SHUAIWEN CUI (SHUAIWEN001@e.ntu.edu.sg)
 * @brief
 * @version 1.0
 * @date 2024-11-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef __MPU6050_H__
#define __MPU6050_H__

/* DEPENDENCIES */
#include "setup.h"
#include "mpu6050_reg.h"

/* FUNCTIONS */
/**
 * @description: Initialize the MPU6050
 * @note: Call this after initializing the I2C bus
 * @details:
 * - Wakes up the MPU6050 from sleep mode.
 * - Enables all sensors (accelerometer and gyroscope).
 * - Sets the sampling rate to 1000 Hz (no divider).
 * - Disables the digital low-pass filter to achieve maximum signal bandwidth (~260 Hz).
 * - Configures the gyroscope full-scale range to ±2000°/s.
 * - Configures the accelerometer full-scale range to ±2g.
 * @register values:
 * - Sampling rate divider (MPU6050_SMPLRT_DIV):
 *   - 0x00: 1000 Hz (default for accelerometer)
 *   - 0x07: 125 Hz
 *   - 0x09: 100 Hz
 *   - 0x13: 50 Hz
 * - Digital low-pass filter configuration (MPU6050_CONFIG):
 *   - 0x00: ~260 Hz (default bandwidth, no filtering)
 *   - 0x01: ~184 Hz
 *   - 0x02: ~94 Hz
 *   - 0x03: ~44 Hz
 *   - 0x04: ~21 Hz
 *   - 0x05: ~10 Hz
 * - Gyroscope full-scale range (MPU6050_GYRO_CONFIG):
 *   - 0x00: ±250°/s
 *   - 0x08: ±500°/s
 *   - 0x10: ±1000°/s
 *   - 0x18: ±2000°/s
 * - Accelerometer full-scale range (MPU6050_ACCEL_CONFIG):
 *   - 0x00: ±2g
 *   - 0x08: ±4g
 *   - 0x10: ±8g
 *   - 0x18: ±16g
 * @return None
 */
void MPU6050_Init(void);
uint8_t MPU6050_ReadReg(uint8_t RegAddress);
void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data);
void MPU6050_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ,
                     int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ);
uint8_t MPU6050_GetID(void);

#endif
