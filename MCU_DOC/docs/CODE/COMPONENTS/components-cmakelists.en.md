# CMakelists.txt UNDER THE `components` FOLDER

!!! note
    Note that all components under the `components` folder share a `CMakelists.txt` file, so this file records the paths of all component header files and source files (folder' name), as well as dependencies. Each time a new component is added, it needs to be registered in this file.

```cmake
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
)

set(requires
    driver
    esp_timer
    newlib
    fatfs
    spiffs
)

idf_component_register(SRC_DIRS ${src_dirs} INCLUDE_DIRS ${include_dirs} REQUIRES ${requires})

component_compile_options(-ffast-math -O3 -Wno-error=format=-Wno-format)


```