/*
 * @Author: i want to 舞动乾坤
 * @Date: 2024-07-26 08:52:56
 * @LastEditors: i want to 舞动乾坤
 * @LastEditTime: 2024-07-26 16:42:29
 * @FilePath: \i2c_hardware_driver_mpu6050\main\MPU6050.c
 * @Description: 
 * 
 * Copyright (c) 2024 by i want to 舞动乾坤, All Rights Reserved. 
 */

#include "mpu6050.h"

#define MPU6050_Address 0x68 // MPU6050 的 7 位地址
#define MPU6050_SCL_Pin GPIO_NUM_1
#define MPU6050_SDA_Pin GPIO_NUM_2
#define i2c_port I2C_NUM_0

static const char* TAG = "MPU6050";

/**
 * @description: MPU6050写寄存器
 * @param {uint8_t} RegAddress 寄存器地址，范围：参考MPU6050手册的寄存器描述
 * @param {uint8_t} Data 要写入寄存器的数据，范围：0x00~0xFF
 * @tip:设备地址通常是一个 7 位地址。当在软件中使用该地址时，通常需要将其左移一位（即乘以 2）以适应 I2C 总线传输格式。具体来说：
		I2C 总线上的设备地址总共是 8 位：
		前 7 位是设备的地址。
		第 8 位（最低位）是读/写位（R/W），用于指示这次操作是读还是写。
		0 表示写操作（I2C_MASTER_WRITE）。
		1 表示读操作（I2C_MASTER_READ）。
		所以，当你指定设备地址时，需要将其左移一位，并将读/写位添加到最低位。例如，对于一个 7 位设备地址 0x68：
		写操作：地址为 0x68 << 1 | I2C_MASTER_WRITE，即 0xD0。
		读操作：地址为 0x68 << 1 | I2C_MASTER_READ，即 0xD1。
		这是为什么需要左移一位的原因。
 * @return {*}无
 */
void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data)
{
    uint8_t res;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create(); // 创建链接，装载容器
    i2c_master_start(cmd); // 产生起始信号
    i2c_master_write_byte(cmd, (MPU6050_Address << 1) | I2C_MASTER_WRITE, true); // 发送从机地址，并产生应答
    i2c_master_write_byte(cmd, RegAddress, true); // 发送从机数据寄存器的地址，并产生应答
    i2c_master_write_byte(cmd, Data, true); // 写入数据 并产生应答
    i2c_master_stop(cmd); // 产生停止信号
    res = i2c_master_cmd_begin(i2c_port, cmd, 100 / portTICK_PERIOD_MS); // 启动容器，开始工作
    i2c_cmd_link_delete(cmd); // 删除链接容器，避免占用资源

    if (res == ESP_OK) {
        ESP_LOGI(TAG, "MPU6050_WriteReg success - RegAddress: 0x%02X, Data: 0x%02X", RegAddress, Data);
    } else {
        ESP_LOGE(TAG, "MPU6050_WriteReg failed with error: %d - RegAddress: 0x%02X, Data: 0x%02X", res, RegAddress, Data);
    }
}

/**
 * @description: 读寄存器的数据
 * 
 * @param {uint8_t} RegAddress  寄存器地址，范围：参考MPU6050手册的寄存器描述
 * @return {*}读取寄存器的数据，范围：0x00~0xFF
 */
uint8_t MPU6050_ReadReg(uint8_t RegAddress)
{
    uint8_t Data = 0;
    uint8_t res;



	i2c_cmd_handle_t cmd = i2c_cmd_link_create(); // 创建链接，装载容器
	i2c_master_start(cmd); // 产生起始信号
	i2c_master_write_byte(cmd, (MPU6050_Address << 1) | I2C_MASTER_WRITE, true); // 发送从机地址，并产生应答
	i2c_master_write_byte(cmd, RegAddress, true); // 发送从机数据寄存器的地址，并产生应答

	// 开始在该寄存器下读数据
	i2c_master_start(cmd); // 产生起始信号
	i2c_master_write_byte(cmd, (MPU6050_Address << 1) | I2C_MASTER_READ, true); // 发送从机地址，读写位为1，表示即将读取，并产生应答
	i2c_master_read_byte(cmd, &Data, I2C_MASTER_LAST_NACK); // 读一个字节的数据至Data内，并且非应答
	i2c_master_stop(cmd); // 发送停止信号
	res = i2c_master_cmd_begin(i2c_port, cmd, 100 / portTICK_PERIOD_MS); // 启动容器，开始工作
	i2c_cmd_link_delete(cmd); // 删除链接，保证资源不会被一直占用

	if (res == ESP_OK) {
		ESP_LOGI(TAG, "MPU6050_ReadReg success - RegAddress: 0x%02X, Data: 0x%02X", RegAddress, Data);
	
	} else {
		ESP_LOGE(TAG, "MPU6050_ReadReg failed with error: %d - RegAddress: 0x%02X, retrying...", res, RegAddress);
		vTaskDelay(10 / portTICK_PERIOD_MS); // 延迟10ms后重试
	}
    

    return Data;
}

/**
 * @description: MPU5050初始化
 * @return {*}无
 */
void MPU6050_Init(void)
{
    uint8_t res;
    i2c_config_t i2c_config_InitStructure;
    i2c_config_InitStructure.clk_flags = 0; // 采用默认时钟
    i2c_config_InitStructure.master.clk_speed = 50000; // 通信速度 分为标准速度100kbps和快速400kbps，这里用标准速度即可
    i2c_config_InitStructure.mode = I2C_MODE_MASTER; // 主机模式
    i2c_config_InitStructure.scl_io_num = MPU6050_SCL_Pin; // 通信引脚，scl
    i2c_config_InitStructure.scl_pullup_en = GPIO_PULLUP_ENABLE; // scl 上拉使能
    i2c_config_InitStructure.sda_io_num = MPU6050_SDA_Pin; // sda引脚
    i2c_config_InitStructure.sda_pullup_en = GPIO_PULLUP_ENABLE; // sda 上拉使能

    res = i2c_param_config(i2c_port, &i2c_config_InitStructure);//配置参数
    if (res == ESP_OK) {
        ESP_LOGI(TAG, "i2c_param_config success");
    } else {
        ESP_LOGE(TAG, "i2c_param_config failed with error: %d", res);
    }

    res = i2c_driver_install(i2c_port, I2C_MODE_MASTER, 0, 0, 0); // 安装驱动
    if (res == ESP_OK) {
        ESP_LOGI(TAG, "i2c_driver_install success");
    } else {
        ESP_LOGE(TAG, "i2c_driver_install failed with error: %d", res);
    }

    MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01); // 唤醒mpu6050
    MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00);
    MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09); // 10分频
    MPU6050_WriteReg(MPU6050_CONFIG, 0x06); // 数字低通滤波器
    MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18); // 陀螺仪寄存器
    MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18); // 加速度寄存器 最大量程
}



/**
  * 函    数：MPU6050获取ID号
  * 参    数：无
  * 返 回 值：MPU6050的ID号
  */
uint8_t MPU6050_GetID(void)
{
	return MPU6050_ReadReg(MPU6050_WHO_AM_I);

}



/**
  * 函    数：MPU6050获取数据
  * 参    数：AccX AccY AccZ 加速度计X、Y、Z轴的数据，使用输出参数的形式返回，范围：-32768~32767
  * 参    数：GyroX GyroY GyroZ 陀螺仪X、Y、Z轴的数据，使用输出参数的形式返回，范围：-32768~32767
  * 返 回 值：无
  * 具体选择转的角速度是多少 是通过比例公式计算出来的  读取的数据/32768  =  x /满量程  求x
  */
void MPU6050_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ, 
						int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ)
{
	uint8_t DataH,DataL;
	//读取加速度x轴寄存器的高八位
	DataH=MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);
	//读取加速度x轴寄存器的低八位
	DataL=MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
	*AccX=(DataH<<8) | DataL;//读取
	
	//读取加速度y轴寄存器的高八位
	DataH=MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
	//读取加速度y轴寄存器的低八位
	DataL=MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
	*AccY=(DataH<<8) | DataL;  //返回出去
	
	
	//读取加速度z轴寄存器的高八位
	DataH=MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
	//读取加速度z轴寄存器的低八位       
	DataL=MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
	*AccZ=(DataH<<8) | DataL;  //返回出去
	
	
		
	//读取加速度z轴寄存器的高八位
	DataH=MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
	//读取加速度z轴寄存器的低八位       
	DataL=MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
	*AccZ=(DataH<<8) | DataL;  //返回出去
	
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);		//读取陀螺仪X轴的高8位数据
	DataL = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);		//读取陀螺仪X轴的低8位数据
	*GyroX = (DataH << 8) | DataL;						//数据拼接，通过输出参数返回
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);		//读取陀螺仪Y轴的高8位数据
	DataL = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);		//读取陀螺仪Y轴的低8位数据
	*GyroY = (DataH << 8) | DataL;						//数据拼接，通过输出参数返回
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);		//读取陀螺仪Z轴的高8位数据
	DataL = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);		//读取陀螺仪Z轴的低8位数据
	*GyroZ = (DataH << 8) | DataL;						//数据拼接，通过输出参数返回
}
