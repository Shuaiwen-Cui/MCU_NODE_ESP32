# Development Roadmap and Progress

## Hardware

>**Main Control**

- [x] Main control ATK-DNESP32S3M
    - ATK-MWS3S
        - ROM: 384 KB
        - SRAM: 512 KB
        - PSRAM: 8 MB
        - Flash: 16 MB
    - Power indicator x 1
    - Status indicator x 1
    - Reset button x 1
    - Function button x 1
    - USB to serial (Type-C) x 1
    - USB slave interface (JTAG) x 1
    - TF card interface x 1
    - 5V power input/output x 1 set
    - 3.3V power input/output x 1 set
    - Exposed IO ports x 36

>**Sensing**

- [ ] MPU6050
- [ ] Temperature and humidity sensor (DHT11)
- [ ] Low-precision accelerometer (ADXL362)
- [ ] High-precision accelerometer (ADXL355)
- [ ] Camera module
- [ ] Audio

>**Communication**

- [x] Main control board - Bluetooth module
- [x] Main control board - WiFi module
- [ ] 4G (purchased, pending connection)
- [ ] 5G module (to be purchased)
- [ ] LoRa module (to be purchased)

>**Interaction**

- [x] Main control board - LED
- [x] RGB LED

## Drivers

>**Main Control**

- [x] Timer
- [x] RTC (Real Time Clock)
- [x] SPI (SPI2 - LCD control/SD card)
- [x] RNG Random Number Generator
- [x] TF CARD - SPI
- [ ] I2C
- [ ] UART

>**Sensing**

- [x] ESP built-in thermometer (onboard)
- [ ] MPU6050
- [ ] Temperature and humidity sensor (DHT11)
- [ ] Low-precision accelerometer (ADXL362)
- [ ] High-precision accelerometer (ADXL355)
- [ ] Camera module
- [ ] Audio

>**Communication**

- [ ] WiFi
- [ ] Bluetooth
- [ ] MQTT

>**Interaction**

- [x] LED
- [x] RGB LED
- [x] Button (onboard) (supports external interrupts)
- [x] LCD screen

## Middleware - ESP & Third Party

>**File System**
- [x] VFS
  - [x] FATFS
  - [x] SPIFFS

>**Network**

>**Protocol**

>**Storage**

>**UI**

>**Computation**

>**AI**

ESP-AI / ESP-DL

## Middleware - TTNYSHM




