set(src_dirs
            LED
            RGB
            KEY
            EXIT
            TIM
            LCD
            SPI
            SDIO
            )

set(include_dirs
            LED
            RGB
            KEY
            EXIT
            TIM
            LCD
            SPI
            SDIO
            )

set(requires
            driver
            fatfs
            esp_timer
            )

idf_component_register(SRC_DIRS ${src_dirs} INCLUDE_DIRS ${include_dirs} REQUIRES ${requires})

component_compile_options(-ffast-math -O3 -Wno-error=format=-Wno-format)