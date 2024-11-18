/**
 * @file lcd.c
 * @author
 * @brief LCD driver source file
 * @version 1.0
 * @date 2024-11-18
 * @ref Alinetek LCD driver
 */

#include "lcd.h"
#include "lcdfont.h"

spi_device_handle_t MY_LCD_Handle;
uint8_t lcd_buf[LCD_TOTAL_BUF_SIZE];
lcd_obj_t lcd_self;

/* LCD initialization commands/parameters structure */
typedef struct
{
    uint8_t cmd;
    uint8_t data[16];
    uint8_t databytes; /* Number of data bytes; bit 7 = delay after command; 0xFF = end of commands */
} lcd_init_cmd_t;

/**
 * @brief       Sends a command to the LCD using polling mode (blocking).
 *              Polling mode is used for efficiency due to small data transfers.
 * @param       cmd 8-bit command data to send
 * @retval      None
 */
void lcd_write_cmd(const uint8_t cmd)
{
    LCD_WR(0);
    spi2_write_cmd(MY_LCD_Handle, cmd);
}

/**
 * @brief       Sends data to the LCD using polling mode (blocking).
 *              Polling mode is used for efficiency due to small data transfers.
 * @param       data Pointer to the data to be sent
 * @param       len Length of the data to send
 * @retval      None
 */
void lcd_write_data(const uint8_t *data, int len)
{
    LCD_WR(1);
    spi2_write_data(MY_LCD_Handle, data, len);
}

/**
 * @brief       Sends 16-bit data to the LCD using polling mode (blocking).
 * @param       data 16-bit data to send
 * @retval      None
 */
void lcd_write_data16(uint16_t data)
{
    uint8_t dataBuf[2] = {0, 0};
    dataBuf[0] = data >> 8;
    dataBuf[1] = data & 0xFF;
    LCD_WR(1);
    spi2_write_data(MY_LCD_Handle, dataBuf, 2);
}

/**
 * @brief       Sets the display window size
 * @param       xstar X-coordinate of the top-left corner
 * @param       ystar Y-coordinate of the top-left corner
 * @param       xend X-coordinate of the bottom-right corner
 * @param       yend Y-coordinate of the bottom-right corner
 * @retval      None
 */
void lcd_set_window(uint16_t xstar, uint16_t ystar, uint16_t xend, uint16_t yend)
{
    uint8_t databuf[4] = {0, 0, 0, 0};

    if (lcd_self.dir == 1) /* Horizontal orientation */
    {
        databuf[0] = (xstar + 1) >> 8;
        databuf[1] = 0xFF & (xstar + 1);
        databuf[2] = (xend + 1) >> 8;
        databuf[3] = 0xFF & (xend + 1);
        lcd_write_cmd(lcd_self.setxcmd);
        lcd_write_data(databuf, 4);

        databuf[0] = (ystar + 26) >> 8;
        databuf[1] = 0xFF & (ystar + 26);
        databuf[2] = (yend + 26) >> 8;
        databuf[3] = 0xFF & (yend + 26);
        lcd_write_cmd(lcd_self.setycmd);
        lcd_write_data(databuf, 4);
    }
    else /* Vertical orientation */
    {
        databuf[0] = (xstar + 26) >> 8;
        databuf[1] = 0xFF & (xstar + 26);
        databuf[2] = (xend + 26) >> 8;
        databuf[3] = 0xFF & (xend + 26);
        lcd_write_cmd(lcd_self.setxcmd);
        lcd_write_data(databuf, 4);

        databuf[0] = (ystar + 1) >> 8;
        databuf[1] = 0xFF & (ystar + 1);
        databuf[2] = (yend + 26) >> 8;
        databuf[3] = 0xFF & (yend + 26);
        lcd_write_cmd(lcd_self.setycmd);
        lcd_write_data(databuf, 4);
    }

    lcd_write_cmd(lcd_self.wramcmd); /* Start writing to GRAM */
}

/**
 * @brief       Clears the LCD screen with a specified color
 * @param       color Fill color for the screen
 * @retval      None
 */
void lcd_clear(uint16_t color)
{
    uint16_t i, j;
    uint8_t data[2] = {0};

    data[0] = color >> 8;
    data[1] = color;

    lcd_set_window(0, 0, lcd_self.width - 1, lcd_self.height - 1);

    for (j = 0; j < LCD_BUF_SIZE / 2; j++)
    {
        lcd_buf[j * 2] = data[0];
        lcd_buf[j * 2 + 1] = data[1];
    }

    for (i = 0; i < (LCD_TOTAL_BUF_SIZE / LCD_BUF_SIZE); i++)
    {
        lcd_write_data(lcd_buf, LCD_BUF_SIZE);
    }
}

/**
 * @brief       Fills a specified rectangular area with a single color
 * @param       sx, sy Starting coordinates of the rectangle
 * @param       ex, ey Ending coordinates of the rectangle
 * @param       color Fill color
 * @retval      None
 */
void lcd_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t color)
{
    uint16_t i, j;
    uint16_t width, height;

    width = ex - sx + 1;
    height = ey - sy + 1;
    lcd_set_window(sx, sy, ex, ey);

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            lcd_write_data16(color);
        }
    }
    lcd_set_window(sx, sy, ex, ey);
}

/**
 * @brief       Sets the cursor position
 * @param       xpos X-coordinate
 * @param       ypos Y-coordinate
 * @retval      None
 */
void lcd_set_cursor(uint16_t xpos, uint16_t ypos)
{
    lcd_set_window(xpos, ypos, xpos, ypos);
}

/**
 * @brief       Sets the LCD's automatic scanning direction (not applicable to RGB screens)
 * @param       dir Direction value (0~7) representing 8 possible orientations (definitions in lcd.h)
 * @retval      None
 */
void lcd_scan_dir(uint8_t dir)
{
    uint8_t regval = 0;
    uint8_t dirreg = 0;
    uint16_t temp;

    /* Adjust direction based on screen orientation (horizontal or vertical) */
    if (lcd_self.dir == 1) /* Horizontal orientation */
    {
        dir = 1;
    }
    else /* Vertical orientation */
    {
        dir = 0;
    }

    switch (dir)
    {
    case 0: /* Vertical: Top-right corner as (0, 0) */
        regval |= 0x08;
        break;

    case 1: /* Horizontal: Top-left corner as (0, 0) */
        regval |= 0xA8;
        break;

    case 2: /* Vertical: Bottom-left corner as (0, 0) */
        regval |= 0xC8;
        break;

    case 3: /* Horizontal: Bottom-right corner as (0, 0) */
        regval |= 0x78;
        break;
    }

    dirreg = 0x36; /* For most driver ICs, the direction is controlled by register 0x36 */

    uint8_t data_send[1] = {regval};

    lcd_write_cmd(dirreg);
    lcd_write_data(data_send, 1);

    if (regval & 0x20)
    {
        if (lcd_self.width < lcd_self.height) /* Swap X and Y dimensions */
        {
            temp = lcd_self.width;
            lcd_self.width = lcd_self.height;
            lcd_self.height = temp;
        }
    }
    else
    {
        if (lcd_self.width > lcd_self.height) /* Swap X and Y dimensions */
        {
            temp = lcd_self.width;
            lcd_self.width = lcd_self.height;
            lcd_self.height = temp;
        }
    }

    lcd_set_window(0, 0, lcd_self.width, lcd_self.height);
}

/**
 * @brief       Sets the LCD display orientation
 * @param       dir 0 for vertical; 1 for horizontal orientation
 * @retval      None
 */
void lcd_display_dir(uint8_t dir)
{
    lcd_self.dir = dir;

    if (lcd_self.dir == 0) /* Vertical orientation */
    {
        lcd_self.width = 80;
        lcd_self.height = 160;
        lcd_self.wramcmd = 0X2C;
        lcd_self.setxcmd = 0X2A;
        lcd_self.setycmd = 0X2B;
    }
    else /* Horizontal orientation */
    {
        lcd_self.width = 160;
        lcd_self.height = 80;
        lcd_self.wramcmd = 0X2C;
        lcd_self.setxcmd = 0X2A;
        lcd_self.setycmd = 0X2B;
    }

    lcd_scan_dir(lcd_self.dir); /* Default scanning direction */
}

/**
 * @brief       Performs a hardware reset on the LCD
 * @retval      None
 */
void lcd_hard_reset(void)
{
    LCD_RST(0);
    vTaskDelay(200); /* Delay in milliseconds */
    LCD_RST(1);
    vTaskDelay(200);
}

/**
 * @brief       Draws a pixel at a specified position
 * @param       x X-coordinate
 * @param       y Y-coordinate
 * @param       color Color value for the pixel
 * @retval      None
 */
void lcd_draw_pixel(uint16_t x, uint16_t y, uint16_t color)
{
    lcd_set_cursor(x, y);
    lcd_write_data16(color);
}

/**
 * @brief       Draws a line (horizontal, vertical, or diagonal)
 * @param       x1, y1 Starting coordinates
 * @param       x2, y2 Ending coordinates
 * @param       color Line color
 * @retval      None
 */
void lcd_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
    uint16_t t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;

    int incx, incy, urow, ucol;

    delta_x = x2 - x1; /* Calculate coordinate increments */
    delta_y = y2 - y1;
    urow = x1;
    ucol = y1;

    if (delta_x > 0)
        incx = 1; /* Set single-step direction */
    else if (delta_x == 0)
        incx = 0; /* Vertical line */
    else
    {
        incx = -1;
        delta_x = -delta_x;
    }
    if (delta_y > 0)
        incy = 1;
    else if (delta_y == 0)
        incy = 0; /* Horizontal line */
    else
    {
        incy = -1;
        delta_y = -delta_y;
    }

    if (delta_x > delta_y)
        distance = delta_x; /* Choose the main axis */
    else
        distance = delta_y;

    for (t = 0; t <= distance + 1; t++) /* Draw the line */
    {
        lcd_draw_pixel(urow, ucol, color); /* Draw the pixel */
        xerr += delta_x;
        yerr += delta_y;

        if (xerr > distance)
        {
            xerr -= distance;
            urow += incx;
        }

        if (yerr > distance)
        {
            yerr -= distance;
            ucol += incy;
        }
    }
}

/**
 * @brief       Draw a horizontal line
 * @param       x: Starting x-coordinate
 * @param       y: Starting y-coordinate
 * @param       len: Length of the line
 * @param       color: Color of the line
 * @retval      None
 */
void lcd_draw_hline(uint16_t x, uint16_t y, uint16_t len, uint16_t color)
{
    if ((len == 0) || (x > lcd_self.width) || (y > lcd_self.height))
        return;

    lcd_fill(x, y, x + len - 1, y, color);
}

/**
 * @brief       Draws a rectangle
 * @param       x0, y0 Starting coordinates
 * @param       x1, y1 Ending coordinates
 * @param       color Rectangle color
 * @retval      None
 */
void lcd_draw_rectangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{
    lcd_draw_line(x0, y0, x1, y0, color);
    lcd_draw_line(x0, y0, x0, y1, color);
    lcd_draw_line(x0, y1, x1, y1, color);
    lcd_draw_line(x1, y0, x1, y1, color);
}

/**
 * @brief       Draw a circle
 * @param       x0, y0: Coordinates of the circle's center
 * @param       r: Radius of the circle
 * @param       color: Fill color of the circle
 * @retval      None
 */
void lcd_draw_circle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t color)
{
    int a, b;
    int di;
    a = 0;
    b = r;
    di = 3 - (r << 1);

    while (a <= b)
    {
        lcd_draw_pixel(x0 - b, y0 - a, color);
        lcd_draw_pixel(x0 + b, y0 - a, color);
        lcd_draw_pixel(x0 - a, y0 + b, color);
        lcd_draw_pixel(x0 - b, y0 - a, color);
        lcd_draw_pixel(x0 - a, y0 - b, color);
        lcd_draw_pixel(x0 + b, y0 + a, color);
        lcd_draw_pixel(x0 + a, y0 - b, color);
        lcd_draw_pixel(x0 + a, y0 + b, color);
        lcd_draw_pixel(x0 - b, y0 + a, color);
        a++;

        if (di < 0)
        {
            di += 4 * a + 6;
        }
        else
        {
            di += 10 + 4 * (a - b);
            b--;
        }

        lcd_draw_pixel(x0 + a, y0 + b, color);
    }
}

/**
 * @brief       Display a character at the specified position
 * @param       x, y: Coordinates where the character will be displayed
 * @param       chr: Character to display (" " to "~")
 * @param       size: Font size (12/16/24/32)
 * @param       mode: Overlay mode (1) or non-overlay mode (0)
 * @param       color: Color of the character
 * @retval      None
 */
void lcd_show_char(uint16_t x, uint16_t y, uint8_t chr, uint8_t size, uint8_t mode, uint16_t color)
{
    uint8_t temp = 0, t1 = 0, t = 0;
    uint8_t *pfont = 0;
    uint8_t csize = 0; /* Number of bytes representing a character in the font */
    uint16_t colortemp = 0;
    uint8_t sta = 0;

    csize = (size / 8 + ((size % 8) ? 1 : 0)) * (size / 2); /* Calculate the bytes required for a character */
    chr = chr - ' ';                                        /* Get the font array index (ASCII offset for the space character) */

    if ((x > (lcd_self.width - size / 2)) || (y > (lcd_self.height - size)))
    {
        return;
    }

    lcd_set_window(x, y, x + size / 2 - 1, y + size - 1); /* Set the window for the character */

    switch (size)
    {
    case 12:
        pfont = (uint8_t *)asc2_1206[chr]; /* Use 12x6 font */
        break;

    case 16:
        pfont = (uint8_t *)asc2_1608[chr]; /* Use 16x8 font */
        break;

    case 24:
        pfont = (uint8_t *)asc2_2412[chr]; /* Use 24x12 font */
        break;

    case 32:
        pfont = (uint8_t *)asc2_3216[chr]; /* Use 32x16 font */
        break;

    default:
        return;
    }

    if (size != 24)
    {
        csize = (size / 8 + ((size % 8) ? 1 : 0)) * (size / 2);

        for (t = 0; t < csize; t++)
        {
            temp = pfont[t]; /* Get font pixel data */

            for (t1 = 0; t1 < 8; t1++)
            {
                if (temp & 0x80)
                {
                    colortemp = color;
                }
                else if (mode == 0) /* Skip invalid points if in non-overlay mode */
                {
                    colortemp = 0xFFFF;
                }

                lcd_write_data16(colortemp);
                temp <<= 1;
            }
        }
    }
    else
    {
        csize = (size * 16) / 8;

        for (t = 0; t < csize; t++)
        {
            temp = asc2_2412[chr][t];

            if (t % 2 == 0)
            {
                sta = 8;
            }
            else
            {
                sta = 4;
            }

            for (t1 = 0; t1 < sta; t1++)
            {
                if (temp & 0x80)
                {
                    colortemp = color;
                }
                else if (mode == 0) /* Skip invalid points if in non-overlay mode */
                {
                    colortemp = 0xFFFF;
                }

                lcd_write_data16(colortemp);
                temp <<= 1;
            }
        }
    }
}

/**
 * @brief       Function to compute m^n
 * @param       m, n: Input parameters
 * @retval      Result of m raised to the power n
 */
uint32_t lcd_pow(uint8_t m, uint8_t n)
{
    uint32_t result = 1;

    while (n--)
        result *= m;

    return result;
}

/**
 * @brief       Display a number with len digits
 * @param       x, y: Starting coordinates
 * @param       num: Number to display (0 ~ 2^32)
 * @param       len: Number of digits to display
 * @param       size: Font size (12/16/24/32)
 * @retval      None
 */
void lcd_show_num(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint8_t size, uint16_t color)
{
    uint8_t t, temp;
    uint8_t enshow = 0;

    for (t = 0; t < len; t++) /* Iterate through total digits */
    {
        temp = (num / lcd_pow(10, len - t - 1)) % 10; /* Extract each digit */

        if (enshow == 0 && t < (len - 1)) /* Skip leading zeros */
        {
            if (temp == 0)
            {
                lcd_show_char(x + (size / 2) * t, y, ' ', size, 0, color); /* Display a blank space */
                continue;
            }
            else
            {
                enshow = 1; /* Enable display */
            }
        }

        lcd_show_char(x + (size / 2) * t, y, temp + '0', size, 0, color); /* Display the digit */
    }
}

/**
 * @brief       Display a number with leading zeros if specified
 * @param       x, y: Starting coordinates
 * @param       num: Number to display (0 ~ 2^32)
 * @param       len: Number of digits to display
 * @param       size: Font size (12/16/24/32)
 * @param       mode: Display mode
 *              [7]: 0, No padding; 1, Pad with zeros.
 *              [6:1]: Reserved.
 *              [0]: 0, Non-overlay display; 1, Overlay display.
 * @param       color: Number color
 * @retval      None
 */
void lcd_show_xnum(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint8_t size, uint8_t mode, uint16_t color)
{
    uint8_t t, temp;
    uint8_t enshow = 0;

    for (t = 0; t < len; t++) /* Iterate through total digits */
    {
        temp = (num / lcd_pow(10, len - t - 1)) % 10; /* Extract each digit */

        if (enshow == 0 && t < (len - 1)) /* Skip leading zeros unless padding */
        {
            if (temp == 0)
            {
                if (mode & 0X80) /* Pad with zeros if specified */
                {
                    lcd_show_char(x + (size / 2) * t, y, '0', size, mode & 0X01, color);
                }
                else
                {
                    lcd_show_char(x + (size / 2) * t, y, ' ', size, mode & 0X01, color);
                }
                continue;
            }
            else
            {
                enshow = 1; /* Enable display */
            }
        }
        lcd_show_char(x + (size / 2) * t, y, temp + '0', size, mode & 0X01, color);
    }
}

/**
 * @brief       Display a string within a specified area
 * @param       x, y: Starting coordinates
 * @param       width, height: Area dimensions
 * @param       size: Font size (12/16/24/32)
 * @param       p: Pointer to the string
 * @param       color: String color
 * @retval      None
 */
void lcd_show_string(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t size, char *p, uint16_t color)
{
    uint8_t x0 = x;
    width += x;
    height += y;

    while ((*p <= '~') && (*p >= ' ')) /* Validate character */
    {
        if (x >= width)
        {
            x = x0;
            y += size;
        }

        if (y >= height)
            break; /* Exit if out of bounds */

        lcd_show_char(x, y, *p, size, 0, color);
        x += size / 2;
        p++;
    }
}

/**
 * @brief       Turn on the LCD
 * @retval      None
 */
void lcd_on(void)
{
    LCD_PWR(1);
    vTaskDelay(10);
}

/**
 * @brief       Turn off the LCD
 * @retval      None
 */
void lcd_off(void)
{
    LCD_PWR(0);
    vTaskDelay(10);
}

/**
 * @brief       Initializes the LCD
 * @retval      None
 */
void lcd_init(void)
{
    int cmd = 0;
    esp_err_t ret = 0;

    lcd_self.dir = 0;
    lcd_self.wr = LCD_NUM_WR;   /* Configure WR pin */
    lcd_self.cs = LCD_NUM_CS;   /* Configure CS pin */
    lcd_self.bl = LCD_NUM_BL;   /* Configure BL pin */
    lcd_self.rst = LCD_NUM_RST; /* Configure RST pin */

    /* SPI driver interface configuration */
    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = 60 * 1000 * 1000, /* SPI clock speed */
        .mode = 0,                          /* SPI mode 0 */
        .spics_io_num = lcd_self.cs,        /* SPI device pin */
        .queue_size = 7,                    /* Transaction queue size */
    };

    ret = spi_bus_add_device(SPI2_HOST, &devcfg, &MY_LCD_Handle); /* Add SPI device to the bus */
    ESP_ERROR_CHECK(ret);

    lcd_off();
    lcd_hard_reset(); /* Perform hardware reset */

    /* LCD initialization sequence */
    lcd_init_cmd_t ili_init_cmds[] =
        {
            {0x11, {0}, 0x80},
            {0x21, {0}, 0x80},
            {0xB1, {0x05, 0x3A, 0x3A}, 3},
            {0xB2, {0x05, 0x3A, 0x3A}, 3},
            {0xB3, {0x05, 0x3A, 0x3A, 0x05, 0x3A, 0x3A}, 6},
            {0xB4, {0x03}, 1},
            {0xC0, {0x62, 0x02, 0x04}, 3},
            {0xC1, {0xC0}, 1},
            {0xC2, {0x0D, 0x00}, 2},
            {0xC3, {0x8D, 0x6A}, 2},
            {0xC4, {0x8D, 0xEE}, 2},
            {0xC5, {0x0E}, 1},
            {0xE0, {0x10, 0x0E, 0x02, 0x03, 0x0E, 0x07, 0x02, 0x07, 0x0A, 0x12, 0x27, 0x37, 0x00, 0x0D, 0x0E, 0x10}, 16},
            {0xE1, {0x10, 0x0E, 0x03, 0x03, 0x0F, 0x06, 0x02, 0x08, 0x0A, 0x13, 0x26, 0x36, 0x00, 0x0D, 0x0E, 0x10}, 16},
            {0x3A, {0x05}, 1},
            {0x36, {0xA8}, 1},
            {0x29, {0}, 0x80},
            {0, {0}, 0xFF},
        };

    while (ili_init_cmds[cmd].databytes != 0xFF)
    {
        lcd_write_cmd(ili_init_cmds[cmd].cmd);
        lcd_write_data(ili_init_cmds[cmd].data, ili_init_cmds[cmd].databytes & 0x1F);

        if (ili_init_cmds[cmd].databytes & 0x80)
        {
            vTaskDelay(120);
        }

        cmd++;
    }

    lcd_display_dir(1); /* Set default display direction */
    lcd_clear(WHITE);   /* Clear the screen */
    lcd_on();           /* Turn on the LCD */
}
