/**
 * @file mpu6050.c
 * @author
 * @brief This is the source file for the MPU6050 driver.
 * @version 1.0
 * @date 2024-11-25
 * @ref https://blog.csdn.net/weixin_52924633/article/details/140718490
 * @copyright Copyright (c) 2024
 *
 */

#include "mpu6050.h"

#define MPU6050_Address 0x68 // 7-bit address of MPU6050
#define MPU6050_SCL_Pin GPIO_NUM_1
#define MPU6050_SDA_Pin GPIO_NUM_2
#define i2c_port I2C_NUM_0

static const char *TAG = "MPU6050";

/**
 * @description: Write to a MPU6050 register
 * @param {uint8_t} RegAddress The register address, range: Refer to the MPU6050 datasheet
 * @param {uint8_t} Data The data to be written to the register, range: 0x00~0xFF
 * @tip: The device address is usually a 7-bit address. In software, it typically needs to be shifted left by one bit (i.e., multiplied by 2) to match the I2C bus transfer format. Specifically:
 *      - The I2C device address is 8 bits total:
 *        - The first 7 bits are the device's address.
 *        - The 8th bit (least significant bit) is the read/write bit (R/W), indicating whether the operation is a read or a write.
 *        - 0 indicates a write operation (I2C_MASTER_WRITE).
 *        - 1 indicates a read operation (I2C_MASTER_READ).
 *      - For example, with a 7-bit device address of 0x68:
 *        - Write operation: Address is 0x68 << 1 | I2C_MASTER_WRITE, which equals 0xD0.
 *        - Read operation: Address is 0x68 << 1 | I2C_MASTER_READ, which equals 0xD1.
 *      - This explains why the address needs to be shifted left by one bit.
 * @return None
 */
void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data)
{
	uint8_t res;
	i2c_cmd_handle_t cmd = i2c_cmd_link_create();								 // Create a link for loading commands
	i2c_master_start(cmd);														 // Generate a start signal
	i2c_master_write_byte(cmd, (MPU6050_Address << 1) | I2C_MASTER_WRITE, true); // Send the slave address with write indication
	i2c_master_write_byte(cmd, RegAddress, true);								 // Send the target register address
	i2c_master_write_byte(cmd, Data, true);										 // Write the data to the register
	i2c_master_stop(cmd);														 // Generate a stop signal
	res = i2c_master_cmd_begin(i2c_port, cmd, 100 / portTICK_PERIOD_MS);		 // Execute the I2C command
	i2c_cmd_link_delete(cmd);													 // Delete the link to free resources

	if (res == ESP_OK)
	{
		ESP_LOGI(TAG, "MPU6050_WriteReg success - RegAddress: 0x%02X, Data: 0x%02X", RegAddress, Data);
	}
	else
	{
		ESP_LOGE(TAG, "MPU6050_WriteReg failed with error: %d - RegAddress: 0x%02X, Data: 0x%02X", res, RegAddress, Data);
	}
}

/**
 * @description: Read data from a MPU6050 register
 * @param {uint8_t} RegAddress The register address, range: Refer to the MPU6050 datasheet
 * @return The data read from the register, range: 0x00~0xFF
 */
uint8_t MPU6050_ReadReg(uint8_t RegAddress)
{
	uint8_t Data = 0;
	uint8_t res;

	i2c_cmd_handle_t cmd = i2c_cmd_link_create();								 // Create a link for loading commands
	i2c_master_start(cmd);														 // Generate a start signal
	i2c_master_write_byte(cmd, (MPU6050_Address << 1) | I2C_MASTER_WRITE, true); // Send the slave address with write indication
	i2c_master_write_byte(cmd, RegAddress, true);								 // Send the target register address

	// Start reading data from the specified register
	i2c_master_start(cmd);														// Generate a repeated start signal
	i2c_master_write_byte(cmd, (MPU6050_Address << 1) | I2C_MASTER_READ, true); // Send the slave address with read indication
	i2c_master_read_byte(cmd, &Data, I2C_MASTER_LAST_NACK);						// Read one byte of data into Data without acknowledgment
	i2c_master_stop(cmd);														// Generate a stop signal
	res = i2c_master_cmd_begin(i2c_port, cmd, 100 / portTICK_PERIOD_MS);		// Execute the I2C command
	i2c_cmd_link_delete(cmd);													// Delete the link to free resources

	if (res == ESP_OK)
	{
		ESP_LOGI(TAG, "MPU6050_ReadReg success - RegAddress: 0x%02X, Data: 0x%02X", RegAddress, Data);
	}
	else
	{
		ESP_LOGE(TAG, "MPU6050_ReadReg failed with error: %d - RegAddress: 0x%02X, retrying...", res, RegAddress);
		vTaskDelay(10 / portTICK_PERIOD_MS); // Retry after a 10ms delay
	}

	return Data;
}

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
void MPU6050_Init(void)
{
    MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01); // Wake up the MPU6050
    MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00); // Enable all sensors
    MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x00); // Set sample rate to 1000 Hz
    MPU6050_WriteReg(MPU6050_CONFIG, 0x00);     // Disable digital low-pass filter (~260 Hz bandwidth)
    MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18); // Set gyroscope full-scale range to ±2000°/s
    MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x00); // Set accelerometer full-scale range to ±2g
}


/**
 * @description: Get the MPU6050 ID
 * @return The ID of the MPU6050
 */
uint8_t MPU6050_GetID(void)
{
	return MPU6050_ReadReg(MPU6050_WHO_AM_I);
}

/**
 * @description: Get data from the MPU6050
 * @param {int16_t*} AccX, AccY, AccZ Accelerometer data for the X, Y, Z axes. Returned as output parameters, range: -32768~32767
 * @param {int16_t*} GyroX, GyroY, GyroZ Gyroscope data for the X, Y, Z axes. Returned as output parameters, range: -32768~32767
 * @return None
 * @note: Convert raw data to angular velocity using the scale formula: (Read data / 32768) = (x / full-scale range). Solve for x.
 */
void MPU6050_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ,
					 int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ)
{
	uint8_t DataH, DataL;

	// Read accelerometer X-axis high and low bytes
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
	*AccX = (DataH << 8) | DataL;

	// Read accelerometer Y-axis high and low bytes
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
	*AccY = (DataH << 8) | DataL;

	// Read accelerometer Z-axis high and low bytes
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
	*AccZ = (DataH << 8) | DataL;

	// Read gyroscope X-axis high and low bytes
	DataH = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
	*GyroX = (DataH << 8) | DataL;

	// Read gyroscope Y-axis high and low bytes
	DataH = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
	*GyroY = (DataH << 8) | DataL;

	// Read gyroscope Z-axis high and low bytes
	DataH = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
	*GyroZ = (DataH << 8) | DataL;
}
