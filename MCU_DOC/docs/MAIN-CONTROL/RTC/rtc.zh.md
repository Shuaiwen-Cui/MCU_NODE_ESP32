# 实时时钟 (RTC)

!!! note
    本章介绍 ESP32-S3 实时时钟（RTC）的使用，实时时钟能为系统提供一个准确的时间，即时系统复位或主电源断电，RTC 依然能够运行，因此 RTC 也经常用于各种低功耗场景。

!!! note "实时时钟"
    RTC（实时时钟）是指安装在电子设备或实现其功能的 IC（集成电路）上的时钟。
    
    当您在数字电路中称其为“时钟”时，您可能会想到周期信号，但在英语中，clock 也意味着“时钟”。那为什么我们需要一个单独的 RTC?
    
    原因是 CPU 的定时器时钟功能只在“启动”即“通电时”运行，断电时停止。当然，如果时钟不能连续跟踪时间，则必须手动设置时间。
    
    通常，RTC 配备一个单独分离的电源，如纽扣电池（备用电池），即使 DNESP32S3M 最小系统板电源关闭，它也能保持运作，随时可以实时显示时间。然后，当 DNESP32S3M 最小系统板再次打开时，计算机内置的定时器时钟从 RTC 读取当前时间，并在此基础上供电的同时，时间在其自身机制下显示。顺便说一句，由于纽扣电池相对便宜且使用寿命长，因此 RTC 可以以极低的成本运行。基于此这个作用，它也可以用作内存。

!!! note
    在 ESP32-S3 中，并没有像 STM32 芯片一样，具有 RTC 外设，但是存在一个系统时间，利用系统时间，也可以实现实时时钟的功能效果。
    ESP32-S3 使用两种硬件时钟源建立和保持系统时间。根据应用目的及对系统时间的精度要求，既可以仅使用其中一种时钟源，也可以同时使用两种时钟源。这两种硬件时钟源为 **RTC 定时器** 和 **高分辨率定时器** 。默认情况下，是使用这两种定时器。下面我们将逐一介绍。

## 用例

1. 通过 LCD 实时显示 RTC 时间
2. LED 闪烁，指示程序正在运行

## 涉及资源

1. LED
LED0 - IO1
2. 0.96 寸 LCD
3. RTC

## 依赖

newlib

## 代码

### esp_rtc.h

```c
/**
 * @file esp_rtc.h
 * ! Do not name as rtc.h, as it will conflict with the built-in rtc.h
 * @author 
 * @brief Header file for the RTC driver
 * @version 1.0
 * @date 2024-11-18
 * @ref Alienteck RTC Driver
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __ESP_RTC_H__
#define __ESP_RTC_H__

#include "driver/spi_master.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <sys/time.h>

/* Time structure, including year, month, day, week, hour, minute, and second */
typedef struct
{
    uint8_t hour;       /* Hour */
    uint8_t min;        /* Minute */
    uint8_t sec;        /* Second */
    /* Gregorian year, month, day, and week */
    uint16_t year;      /* Year */
    uint8_t  month;     /* Month */
    uint8_t  date;      /* Day */
    uint8_t  week;      /* Weekday */
} _calendar_obj;

extern _calendar_obj calendar;      /* Time structure */

/* Function declarations */
/**
 * @brief       Set the RTC time
 * @param       year    : Year
 * @param       mon     : Month
 * @param       mday    : Day
 * @param       hour    : Hour
 * @param       min     : Minute
 * @param       sec     : Second
 * @retval      None
 */
void rtc_set_time(int year, int mon, int mday, int hour, int min, int sec);  /* Set time */

/**
 * @brief       Get the current time
 * @param       None
 * @retval      None
 */
void rtc_get_time(void);                                                     /* Get time */

/**
 * @brief       Convert year, month, and day to the day of the week
 * @note        Calculates the weekday based on the Gregorian calendar.
 *              Utilizes the Kim Larson formula for calculation.
 *              For more details, refer to:
 *              https://www.cnblogs.com/fengbohello/p/3264300.html
 * @param       year : Year
 * @param       month: Month
 * @param       day  : Day
 * @retval      0: Sunday; 1 ~ 6: Monday ~ Saturday
 */
uint8_t rtc_get_week(uint16_t year, uint8_t month, uint8_t day);             /* Get the weekday */

#endif /* __RTC_H__ */


```

### esp_rtc.c

```c
/**
 * @file esp_rtc.c
 * ! Do not name as rtc.c, as it will conflict with the built-in rtc.c
 * @author 
 * @brief This file contains the implementation of the RTC driver
 * @version 1.0
 * @date 2024-11-18
 * @ref Alienteck RTC Driver
 * 
 */

#include "esp_rtc.h"

_calendar_obj calendar;         /* Time structure */

/**
 * @brief       Set the RTC time
 * @param       year    : Year
 * @param       mon     : Month
 * @param       mday    : Day
 * @param       hour    : Hour
 * @param       min     : Minute
 * @param       sec     : Second
 * @retval      None
 */
void rtc_set_time(int year, int mon, int mday, int hour, int min, int sec)
{
    struct tm datetime;
    /* Set time */
    datetime.tm_year = year - 1900;
    datetime.tm_mon = mon - 1;
    datetime.tm_mday = mday;
    datetime.tm_hour = hour;
    datetime.tm_min = min;
    datetime.tm_sec = sec;
    datetime.tm_isdst = -1;
    /* Get total seconds since 1970-01-01 */
    time_t second = mktime(&datetime);
    struct timeval val = { .tv_sec = second, .tv_usec = 0 };
    /* Set current time */
    settimeofday(&val, NULL);
}

/**
 * @brief       Get the current time
 * @param       None
 * @retval      None
 */
void rtc_get_time(void)
{
    struct tm *datetime;
    time_t second;
    /* Get the time elapsed since (1970-01-01 00:00:00 UTC) in seconds */
    time(&second);
    datetime = localtime(&second);

    calendar.hour = datetime->tm_hour;          /* Hour */
    calendar.min = datetime->tm_min;            /* Minute */
    calendar.sec = datetime->tm_sec;            /* Second */
    /* Gregorian year, month, day, and week */
    calendar.year = datetime->tm_year + 1900;   /* Year */
    calendar.month = datetime->tm_mon + 1;      /* Month */
    calendar.date = datetime->tm_mday;          /* Day */
    /* Weekday */
    calendar.week = rtc_get_week(calendar.year, calendar.month, calendar.date);
}

/**
 * @brief       Convert year, month, and day to the day of the week
 * @note        Calculates the weekday based on the Gregorian calendar.
 *              Utilizes the Kim Larson formula for calculation.
 *              For more details, refer to:
 *              https://www.cnblogs.com/fengbohello/p/3264300.html
 * @param       year : Year
 * @param       month: Month
 * @param       day  : Day
 * @retval      0: Sunday; 1 ~ 6: Monday ~ Saturday
 */
uint8_t rtc_get_week(uint16_t year, uint8_t month, uint8_t day)
{
    uint8_t week = 0;

    if (month < 3)
    {
        month += 12;
        --year;
    }

    week = (day + 1 + 2 * month + 3 * (month + 1) / 5 + year + (year >> 2) - year / 100 + year / 400) % 7;
    return week;
}
```

!!! tip
    CMakelists.txt 中添加 rtc.h, rtc.c所在路径，分别添加到头文件和源文件对应位置。此外，在依赖中添加 newlib。

### main.c

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
#include "key.h"
#include "exit.h"
#include "lcd.h"
#include "spi.h"
#include "esp_rtc.h"

/* Global variables */
char* weekdays[]={"Sunday","Monday","Tuesday","Wednesday",
                  "Thursday","Friday","Saterday"};

/**
 * @brief Entry point of the program
 * @param None
 * @retval None
 */
void app_main(void)
{
    esp_err_t ret;
    uint8_t tbuf[40];
    uint8_t t = 0;
    

    ret = nvs_flash_init();             

    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    led_init();                         
    spi2_init();                        
    lcd_init();                         
    rtc_set_time(2024,10,18,00,00,00);   

    while (1)
    {
        t++;

        if ((t % 10) == 0)              
        {
            rtc_get_time();
            sprintf((char *)tbuf, "Time:%02d:%02d:%02d", calendar.hour, calendar.min, calendar.sec);
            printf("Time:%02d:%02d:%02d\r\n", calendar.hour, calendar.min, calendar.sec);
            lcd_show_string(0, 0, 210, 16, 16, (char *)tbuf,BLUE);
            sprintf((char *)tbuf, "Date:%04d-%02d-%02d", calendar.year, calendar.month, calendar.date);
            printf("Date:%02d-%02d-%02d\r\n",  calendar.year,  calendar.month,  calendar.date);
            lcd_show_string(0, 30, 210, 16, 16, (char *)tbuf,BLUE);
            sprintf((char *)tbuf, "Week:%s", weekdays[calendar.week - 1]);
            lcd_show_string(0, 60, 210, 16, 16, (char *)tbuf,BLUE);
        }

        if ((t % 20) == 0)
        {
            led_toggle();               
        }

        vTaskDelay(10);
    }
}
```

