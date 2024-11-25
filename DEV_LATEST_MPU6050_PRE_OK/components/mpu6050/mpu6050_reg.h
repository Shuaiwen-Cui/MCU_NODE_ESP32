#ifndef __MPU6050_REG_H__
#define __MPU6050_REG_H__

// Contains commonly used register addresses for the MPU6050 sensor

#define	MPU6050_SMPLRT_DIV		0x19   // Sample Rate Divider register; lower values result in faster sampling
#define	MPU6050_CONFIG			0x1A   // Configuration register for DLPF (Digital Low Pass Filter) and external sync
#define	MPU6050_GYRO_CONFIG		0x1B   // Gyroscope configuration register; sets gyroscope full-scale range
#define	MPU6050_ACCEL_CONFIG	0x1C   // Accelerometer configuration register; sets accelerometer full-scale range

#define	MPU6050_ACCEL_XOUT_H	0x3B   // Accelerometer X-axis high byte
#define	MPU6050_ACCEL_XOUT_L	0x3C   // Accelerometer X-axis low byte
#define	MPU6050_ACCEL_YOUT_H	0x3D   // Accelerometer Y-axis high byte
#define	MPU6050_ACCEL_YOUT_L	0x3E   // Accelerometer Y-axis low byte
#define	MPU6050_ACCEL_ZOUT_H	0x3F   // Accelerometer Z-axis high byte
#define	MPU6050_ACCEL_ZOUT_L	0x40   // Accelerometer Z-axis low byte

#define	MPU6050_TEMP_OUT_H		0x41   // Temperature high byte
#define	MPU6050_TEMP_OUT_L		0x42   // Temperature low byte

#define	MPU6050_GYRO_XOUT_H		0x43   // Gyroscope X-axis high byte
#define	MPU6050_GYRO_XOUT_L		0x44   // Gyroscope X-axis low byte
#define	MPU6050_GYRO_YOUT_H		0x45   // Gyroscope Y-axis high byte
#define	MPU6050_GYRO_YOUT_L		0x46   // Gyroscope Y-axis low byte
#define	MPU6050_GYRO_ZOUT_H		0x47   // Gyroscope Z-axis high byte
#define	MPU6050_GYRO_ZOUT_L		0x48   // Gyroscope Z-axis low byte

#define	MPU6050_PWR_MGMT_1		0x6B   // Power Management 1 register
#define	MPU6050_PWR_MGMT_2		0x6C   // Power Management 2 register
#define	MPU6050_WHO_AM_I		0x75   // Device ID register

#endif
