# `components` 文件夹下的 `CMakelists.txt`

!!! note
    注意整个 `components` 文件夹下个component共用一个 `CMakelists.txt` 文件，所以，该文件登记了所有的component的头文件和源文件路径(文件夹名称)，以及依赖项。每次添加新的component时，都需要在该文件中登记。

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
