/**
 ****************************************************************************************************
 * @file        main.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2023-08-26
 * @brief       ESP32-S3板载外设测试实验(0.96寸TFTLCD)
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 ESP32-S3 最小系统板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "led.h"
#include "key.h"
#include "lcd.h"
#include "app_test.h"
#include "logo.h"

#include "esp_partition.h"
#include "spi_flash_mmap.h"

const   esp_partition_t   *storage_partition;
#define TEST_FLAG_ADDR    0x3FFFFF
#define TEST_FINISH_FLAG  0xAA

void lcd_show_pic(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t *pic);

/**
 * @brief       程序入口
 * @param       无
 * @retval      无
 */
void app_main(void)
{
    esp_err_t ret;
    uint8_t test_flag = 0;
    uint8_t finish_flag = 0xAA;
    uint8_t key_value = 0;

    ret = nvs_flash_init();             /* 初始化NVS */
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    /* 从FLASH中找到子分区storage(用storage最后一个字节存放) */
    storage_partition = esp_partition_find_first(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_ANY, "storage");    
    if (storage_partition == NULL)
    {
        printf("Flash partition not found");
    }

    led_init();                         /* 初始化LED */
    key_init();                         /* 初始化KEY */
    spi2_init();                        /* 初始化SPI2 */
    lcd_init();                         /* 初始化LCD */

    esp_partition_read(storage_partition, TEST_FLAG_ADDR, (uint8_t *)&test_flag, 1);
    // printf("test_flag:%#x \r\n", test_flag);
    if (test_flag != TEST_FINISH_FLAG)  /* 如果是第一次测试,则需要测试LED/KEY/USB/LCD */
    {
        /* 出厂测试程序 */
        func_test();
        // esp_partition_erase_range(storage_partition, TEST_FLAG_ADDR, 1); /* 擦除标记 */
        esp_partition_write(storage_partition, TEST_FLAG_ADDR, (uint8_t *)&finish_flag, 1);     /* 写入已经测试好的标记 */
    }

    /* 测试完毕 显示正点原子LOGO 以及 资料中心二维码 */
    lcd_show_pic(0, 0, 80, 80, gImage_logo);
    lcd_show_pic(80, 0, 80, 80, gImage_source);

    while (1)
    {
        key_value = key_scan(1);    /* 可通过长按BOOT按键进行到强制测试模式 */

        if (key_value)
        {   
            func_test();

            lcd_clear(WHITE);
            lcd_show_string(20, 1,  120, 16, 16, "DNESP32S3M TEST", RED);
            lcd_show_string(24, 40, 112, 16, 16, "Pass all tests", RED);
            lcd_show_string(32, 60, 96,  16, 16, "Please reset", RED);
        }

        LED_TOGGLE();
        vTaskDelay(500);
    }
}

/**
 * @brief       LCD图片显示
 * @note        图片取模方式: 水平扫描、RGB565、高位在前
 * @param       x     : 待显示图片的X坐标
 *              y     : 待显示图片的Y坐标
 *              width : 待显示图片的宽度
 *              height: 待显示图片的高度
 *              pic   : 待显示图片数组首地址
 * @retval      无
 */
void lcd_show_pic(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t *pic)
{
    if ((x + width > lcd_self.width) || (y + height > lcd_self.height))
    {
        return;
    }

    lcd_set_window(x, y, x + width - 1, y + height - 1);
    lcd_write_data(pic, width * height * sizeof(uint16_t));

    lcd_set_window(0, 0, lcd_self.width - 1, lcd_self.height - 1);
}
