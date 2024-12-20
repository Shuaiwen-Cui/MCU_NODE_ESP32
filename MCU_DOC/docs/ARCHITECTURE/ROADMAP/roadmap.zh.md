# 开发路线图与进度

## 硬件

>**主控**

- [x] 主控 ATK-DNESP32S3M
    - ATK-MWS3S
        - ROM: 384 KB
        - SRAM: 512 KB
        - PSRAM: 8 MB
        - Flash: 16 MB
    - 电源指示灯 x 1
    - 状态指示灯 x 1
    - 复位按键 x 1
    - 功能按键 x 1
    - USB转串口 （Type-C）x 1
    - USB从机接口（JTAG）x 1
    - TF卡接口 x 1
    - 5V 电源输入/输出 x 1组
    - 3.3V 电源输入/输出 x 1组
    - 引出IO口 x 36

>**感知**

- [ ] MPU6050
- [ ] 温湿度传感器(DHT11)
- [ ] 低精度加速度传感器(ADXL362)
- [ ] 高精度加速度传感器(ADXL355)
- [ ] 摄像头模块
- [ ] 音频

>**通讯**

- [x] 主控板-蓝牙模块
- [x] 主控板-WIFI模块
- [ ] 4G（已购，待连接）
- [ ] 5G模块 (待选购)
- [ ] LoRa模块 (待选购)

>**交互**

- [x] 主控板-LED
- [x] RGB LED

## 驱动

>**主控**

- [x] 定时器
- [x] RTC (实时时钟)
- [x] SPI (SPI2 - LCD控制/SD卡)
- [x] RNG 随机数生成器
- [x] TF CARD - SPI
- [ ] I2C
- [ ] UART

>**感知**

- [x] ESP内置温度计（板上）
- [ ] MPU6050
- [ ] 温湿度传感器(DHT11)
- [ ] 低精度加速度传感器(ADXL362)
- [ ] 高精度加速度传感器(ADXL355)
- [ ] 摄像头模块
- [ ] 音频

>**通讯**

- [ ] WIFI
- [ ] 蓝牙
- [ ] MQTT

>**交互**

- [x] LED
- [x] RGB LED
- [x] 按钮(板上)(支持外部中断)
- [x] 液晶显示屏


## 中间件-ESP&三方

>**文件系统**

- [x] VFS
  - [x] FATFS
  - [x] SPIFFS

>**网络**

>**协议**

>**存储**

>**UI**

>**计算**

>**AI**

ESP-AI / ESP-DL

## 中间件-TTNYSHM

