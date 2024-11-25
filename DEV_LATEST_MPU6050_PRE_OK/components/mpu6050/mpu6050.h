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
#include "esp_i2c.h"
#include "mpu6050_reg.h"

void MPU6050_Init(void);
uint8_t MPU6050_ReadReg(uint8_t RegAddress);
void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data);
void MPU6050_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ,
                     int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ);
uint8_t MPU6050_GetID(void);

#endif
