/**
 ****************************************************************************************************
 * @file        app_test.h
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

#ifndef __APP_TEST_H
#define __APP_TEST_H


#include <inttypes.h>


/* USB控制器 */
typedef struct
{
    uint8_t status;                         /* bit0:0,断开;1,连接 */
}__usbdev;

void func_test(void);

#endif
