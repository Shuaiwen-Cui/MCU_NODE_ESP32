/**
 ****************************************************************************************************
 * @file        app_test.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2023-08-01
 * @brief       APP功能测试
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 ESP32-S3 开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 * 
 ****************************************************************************************************
 */

#include "app_test.h"
#include "lcd.h"
#include "led.h"
#include "key.h"
#include "spi_sdcard.h"
#include "tinyusb.h"
#include "tusb_cdc_acm.h"
#include "tusb_tasks.h"


#include "exfuns.h"
#include "piclib.h"

static uint8_t usb_buf[CONFIG_TINYUSB_CDC_RX_BUFSIZE + 1];
__usbdev g_usbdev;      /* USB控制器 */

/**
 * @brief       USB 设备接收回调函数
 * @param       itf     :设置的简要CDC端口
 * @param       event   :CDC事件
 * @retval      无
 */
void tinyusb_cdc_rx_callback(int itf, cdcacm_event_t *event)
{
    size_t rx_size = 0;

    /* 读取串口的数据 */
    tinyusb_cdcacm_read(itf, usb_buf, CONFIG_TINYUSB_CDC_RX_BUFSIZE, &rx_size);

    /* 发送数据 */
    tinyusb_cdcacm_write_queue(itf, usb_buf, rx_size);
    tinyusb_cdcacm_write_flush(itf, 0);
}

/**
 * @brief       USB 串行设备回调函数
 * @param       itf     :设置的简要CDC端口
 * @param       event   :CDC事件
 * @retval      无
 */
void tinyusb_cdc_line_state_changed_callback(int itf, cdcacm_event_t *event)
{
    g_usbdev.status |= 0x01;
}

extern esp_err_t tinyusb_cdc_deinit(int itf);

/**
 * @brief       卸载USART
 * @param       无
 * @retval      无
 */
void tud_usb_detint(void)
{
    tusb_stop_task();
    tinyusb_cdc_deinit(TINYUSB_CDC_ACM_0);
}

/**
 * @brief       USB函数初始化
 * @param       无
 * @retval      无
 */
void tud_usb_usart(void)
{
    const tinyusb_config_t tusb_cfg = {
        .device_descriptor = NULL,
        .string_descriptor = NULL,
        .external_phy = false,
        .configuration_descriptor = NULL,
    };
    /* USB设备登记 */
    ESP_ERROR_CHECK(tinyusb_driver_install(&tusb_cfg));

    tinyusb_config_cdcacm_t acm_cfg = {
        .usb_dev = TINYUSB_USBDEV_0,                /* USB设备 */
        .cdc_port = TINYUSB_CDC_ACM_0,              /* CDC端口 */
        .rx_unread_buf_sz = 64,                     /* 配置RX缓冲区大小 */
        .callback_rx = &tinyusb_cdc_rx_callback,    /* 接收回调函数 */
        .callback_rx_wanted_char = NULL,
        .callback_line_state_changed = NULL,
        .callback_line_coding_changed = NULL
    };
    /* USB CDC初始化 */
    ESP_ERROR_CHECK(tusb_cdc_acm_init(&acm_cfg));
    /* 注册回调函数 */
    ESP_ERROR_CHECK(tinyusb_cdcacm_register_callback(
                        TINYUSB_CDC_ACM_0,
                        CDC_EVENT_LINE_STATE_CHANGED,
                        &tinyusb_cdc_line_state_changed_callback));
}

void usb_test(void)
{
    lcd_clear(WHITE);
    
    lcd_show_string(51, 1, 64, 16, 16, "USB_TEST", RED);
    lcd_show_string(16, 40, 128, 16, 16, "Connect USB_JTAG", RED);
    tud_usb_usart();    /* USB初始化 */

    while (1)
    {
        if ((g_usbdev.status & 0x0f) == 0x01)
        {
            tud_usb_detint();
            lcd_show_string(23,     61, 32, 16, 16, "PASS", BLUE);
            lcd_show_string(3 + 79, 61, 72, 16, 16, "BOOT NEXT", RED);
            break;
        }
    }
}


void sdcard_test(void)
{
    uint8_t key_value = 0;
    FF_DIR picdir;              /* 图片目录 */

    lcd_clear(WHITE);

    lcd_show_string(51, 1, 56, 16, 16, "SD_TEST", RED);

    /* TFCARD检测 */
    while(sd_spi_init())
    {
        lcd_show_string(59, 39, 40, 16, 16, "Error", RED);
        vTaskDelay(500);
        lcd_show_string(59, 39, 40, 16, 16, "     ", RED);
        vTaskDelay(500);
    }

    exfuns_init();                            
    while (f_opendir(&picdir, "0:/PICTURE"))    
    {
        printf("open picture file failed \r\n");
        vTaskDelay(1000);
    }

    piclib_init();  

    lcd_show_string(23,     61, 32, 16, 16, "PASS", BLUE);
    lcd_show_string(3 + 79, 61, 72, 16, 16, "BOOT NEXT", RED);

    piclib_ai_load_picfile("0:/PICTURE/cheer.png", 0, 0, 160, 80);   

    while (1)
    {
        key_value = key_scan(0);
        
        if (key_value)
        {
            lcd_clear(WHITE);
            break;
        }
    }
}

void led_key_test(void)
{
    uint8_t key_value = 0;
    uint8_t key_flag = 0;

    lcd_clear(WHITE);

    /* LED状态 */
    lcd_show_string(3, 1, 72, 16, 16, "LED_STATE", RED);
    lcd_draw_rectangle(29, 39, 49, 59, LGRAY);

    /* KEY状态 */
    lcd_show_string(3 + 79, 1, 72, 16, 16, "KEY_STATE", RED);
    lcd_draw_rectangle(79 + 29, 39, 79 + 49, 59, LGRAY);

    /* 验证操作 */
    while (1)
    {
        key_value = key_scan(0);

        if (key_value && (!key_flag))                   /* 第一次按下按键 */
        {
            LED(0);
            lcd_fill(29, 39, 49, 59, RED);              /* LED图标亮红色*/
            lcd_fill(79 + 29, 39, 79 + 49, 59, RED);    /* KEY图标亮红色 */

            key_flag = 1;   /* 第一次按下标志 */
            key_value = 0;
            lcd_show_string(23,     61, 32, 16, 16, "PASS", BLUE);
            lcd_show_string(3 + 79, 61, 72, 16, 16, "BOOT NEXT", RED);
        }

        if (key_value && (key_flag))
        {
            lcd_clear(WHITE);
            break;
        }
    }
}

void lcd_test(void)
{
    uint8_t key_value = 0;
    uint8_t key_flag = 0;
    uint8_t i = 0;
    uint16_t lcd_color[5] = {RED, GREEN, BLUE, BLACK, WHITE};
    lcd_clear(WHITE);

    while (1)
    {
        key_value = key_scan(0);

        if (key_value && (!key_flag))                  
        {
            lcd_clear(lcd_color[i]);
            i++;
        }
        if (i == 5) break;
    }
}

void func_test(void)
{
    /* LCD测试 */
    lcd_test();

    /* LED&KEY测试 */
    led_key_test();

    /* TFCARD测试 */
    sdcard_test();

    /* USB_JTAG测试 */
    usb_test();
}
