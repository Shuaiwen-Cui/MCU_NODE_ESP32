# 按键-中断方式

## 介绍

!!! note
    在本节中，我们将讨论DNESP32S3M开发板上的板载按键。区别于先前的开发方式，本节中按键的读取方式采用中断方式。

!!! tip
    注意本页内容实质上对非中断方式的key是替代关系，因此在实际应用中，只需选择一种方式即可。

![KEY](KEY.png){ width=800px }

## 概览

在项目中，我们在components目录下新建了一个KEY目录，用于存放按键驱动代码，包括key.h和key.c文件。

## 引脚配置

根据图纸，板载LED灯连接到GPIO0。

![KEY_CIRCUIT](KEY_CIRCUIT.png){ width=800px }

## 代码

### EXIT.h
    
```c
/**
 * @file exit.h
 * @author 
 * @brief This file is for the external interrupt initialization and configuration.
 * @version 1.0
 * @date 2024-11-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __EXIT_H__
#define __EXIT_H__

#include "esp_err.h"
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp_system.h" 
#include "esp_log.h"
#include "sdkconfig.h"
#include "led.h"

/* Pin definition */
#define BOOT_INT_GPIO_PIN   GPIO_NUM_0

/* IO operation */
#define BOOT_EXIT                gpio_get_level(BOOT_INT_GPIO_PIN)

/* Function declarations */
/**
 * @brief       External interrupt initialization function
 * @param       None
 * @retval      None
 */
void exit_init(void);   /* External interrupt initialization function */

#endif


```

### EXIT.h

```c

/**
 * @file exit.c
 * @author 
 * @brief This file is for the external interrupt initialization and configuration.
 * @version 1.0
 * @date 2024-11-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "exit.h"

/**
 * @brief       External interrupt service routine
 * @param       arg: Interrupt pin number
 * @note        IRAM_ATTR: The IRAM_ATTR attribute is used to store the interrupt handler in internal RAM to reduce latency
 * @retval      None
 */
static void IRAM_ATTR exit_gpio_isr_handler(void *arg)
{
    uint32_t gpio_num = (uint32_t) arg;
    
    if (gpio_num == BOOT_INT_GPIO_PIN)
    {
        led_toggle();
    }
}

/**
 * @brief       External interrupt initialization function
 * @param       None
 * @retval      None
 */
void exit_init(void)
{
    gpio_config_t gpio_init_struct;

    /* Configure BOOT pin and external interrupt */
    gpio_init_struct.mode = GPIO_MODE_INPUT;                    /* Set as input mode */
    gpio_init_struct.pull_up_en = GPIO_PULLUP_ENABLE;           /* Enable pull-up */
    gpio_init_struct.pull_down_en = GPIO_PULLDOWN_DISABLE;      /* Disable pull-down */
    gpio_init_struct.intr_type = GPIO_INTR_NEGEDGE;             /* Trigger on falling edge */
    gpio_init_struct.pin_bit_mask = 1ull << BOOT_INT_GPIO_PIN;  /* Configure BOOT key pin */
    gpio_config(&gpio_init_struct);                             /* Apply configuration */
    
    /* Register interrupt service */
    gpio_install_isr_service(0);
    
    /* Set GPIO interrupt callback function */
    gpio_isr_handler_add(BOOT_INT_GPIO_PIN, exit_gpio_isr_handler, (void*) BOOT_INT_GPIO_PIN);

    /* Enable GPIO interrupt */
    gpio_intr_enable(BOOT_INT_GPIO_PIN);
}

```

## 测试程序

将main.c文件中的代码替换为以下代码：

```c
/**
 * @file main.c
 * @author SHUAIWEN CUI (SHUAIWEN001@e.ntu.edu.sg)
 * @brief 
 * @version 1.0
 * @date 2024-11-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */

/* Dependencies */
// Basic
#include "esp_system.h"
#include "esp_chip_info.h"
#include "esp_psram.h"
#include "esp_flash.h"
#include "nvs_flash.h"
#include "esp_log.h"

// RTOS
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// BSP
#include "led.h"
#include "rgb.h"
#include "exit.h"

/**
 * @brief Entry point of the program
 * @param None
 * @retval None
 */
void app_main(void)
{
    esp_err_t ret;
    uint32_t flash_size;
    esp_chip_info_t chip_info;

    // Initialize NVS
    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase()); // Erase if needed
        ret = nvs_flash_init();
    }

    // Get FLASH size
    esp_flash_get_size(NULL, &flash_size);
    esp_chip_info(&chip_info);

    // Display CPU core count
    printf("CPU Cores: %d\n", chip_info.cores);

    // Display FLASH size
    printf("Flash size: %ld MB flash\n", flash_size / (1024 * 1024));

    // Display PSRAM size
    printf("PSRAM size: %d bytes\n", esp_psram_get_size());

    // BSP
    led_init();
    rgb_init();
    // key_init();
    exit_init();

    while (1)
    {
        vTaskDelay(10);

    }

}
```

