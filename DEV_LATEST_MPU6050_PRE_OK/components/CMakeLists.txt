set(src_dirs
    setup
    led
    rgb
    key
    exit
    spi
    lcd
    tim
    rtc
    rng
    spiffs
    sdio
    i2c
    mpu6050
)

set(include_dirs
    setup
    led
    rgb
    key
    exit
    spi
    lcd
    tim
    rtc
    rng
    spiffs
    sdio
    i2c
    mpu6050
)

set(requires
    esp_system     # Provides system-level support, including startup and memory management (recommended)
    nvs_flash      # Enables non-volatile storage (if required)
    esp_hw_support # Low-level hardware support, such as RTC and RNG (if needed)
    # esp_flash      # Support for external flash memory, such as PSRAM or SD card controllers
    log            # Logging module for debugging purposes (recommended)
    driver         # Peripheral drivers, including I2C, SPI, GPIO, etc. (mandatory for most peripherals)
    esp_timer      # High-precision timer support (recommended)
    fatfs          # FAT file system support (if required for SD card)
    spiffs         # SPIFFS file system support (if required for storage)
)


idf_component_register(SRC_DIRS ${src_dirs} INCLUDE_DIRS ${include_dirs} REQUIRES ${requires})

component_compile_options(-ffast-math -O3 -Wno-error=format=-Wno-format)
