set(src_dirs
            LCD
            LED
            RGB
            KEY
            SPI
            SDIO
            DHT11
            )

set(include_dirs
            LCD
            LED
            RGB
            KEY
            SPI
            SDIO
            DHT11
            )

set(requires
            driver
            fatfs
            )

idf_component_register(SRC_DIRS ${src_dirs} INCLUDE_DIRS ${include_dirs} REQUIRES ${requires})

component_compile_options(-ffast-math -O3 -Wno-error=format=-Wno-format)