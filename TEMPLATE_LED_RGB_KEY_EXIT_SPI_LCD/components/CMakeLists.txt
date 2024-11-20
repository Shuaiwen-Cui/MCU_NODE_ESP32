set(src_dirs
    setup
    led
    rgb
    key
    exit
    spi
    lcd
)

set(include_dirs
    setup
    led
    rgb
    key
    exit
    spi
    lcd
)

set(requires
    # esp_system
    # nvs_flash
    # esp_hw_support
    # esp_psram
    # esp_flash
    # log
    driver
)

idf_component_register(SRC_DIRS ${src_dirs} INCLUDE_DIRS ${include_dirs} REQUIRES ${requires})

component_compile_options(-ffast-math -O3 -Wno-error=format=-Wno-format)
