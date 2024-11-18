/**
 * @file spi.c
 * @author 
 * @brief 
 * @version 1.0
 * @date 2024-11-18
 * @ref Alientek SPI driver
 * 
 */

#include "spi.h"

/**
 * @brief       Initialize SPI
 * @param       None
 * @retval      None
 */
void spi2_init(void)
{
    esp_err_t ret = 0;
    spi_bus_config_t spi_bus_conf = {0};

    /* SPI bus configuration */
    spi_bus_conf.miso_io_num = SPI_MISO_GPIO_PIN;                               /* SPI_MISO pin */
    spi_bus_conf.mosi_io_num = SPI_MOSI_GPIO_PIN;                               /* SPI_MOSI pin */
    spi_bus_conf.sclk_io_num = SPI_CLK_GPIO_PIN;                                /* SPI_SCLK pin */
    spi_bus_conf.quadwp_io_num = -1;                                            /* SPI write protection signal pin, not enabled */
    spi_bus_conf.quadhd_io_num = -1;                                            /* SPI hold signal pin, not enabled */
    spi_bus_conf.max_transfer_sz = 160 * 80 * 2;                                /* Configure maximum transfer size in bytes */
    
    /* Initialize SPI bus */
    ret = spi_bus_initialize(SPI2_HOST, &spi_bus_conf, SPI_DMA_CH_AUTO);        /* SPI bus initialization */
    ESP_ERROR_CHECK(ret);                                                       /* Check parameter values */
}

/**
 * @brief       Send command via SPI
 * @param       handle : SPI handle
 * @param       cmd    : Command to send
 * @retval      None
 */
void spi2_write_cmd(spi_device_handle_t handle, uint8_t cmd)
{
    esp_err_t ret;
    spi_transaction_t t = {0};

    t.length = 8;                                       /* Number of bits to transmit (1 byte = 8 bits) */
    t.tx_buffer = &cmd;                                 /* Fill the command */
    ret = spi_device_polling_transmit(handle, &t);      /* Start transmission */
    ESP_ERROR_CHECK(ret);                               /* Usually no issues */
}

/**
 * @brief       Send data via SPI
 * @param       handle : SPI handle
 * @param       data   : Data to send
 * @param       len    : Length of data to send
 * @retval      None
 */
void spi2_write_data(spi_device_handle_t handle, const uint8_t *data, int len)
{
    esp_err_t ret;
    spi_transaction_t t = {0};

    if (len == 0)
    {
        return;                                     /* No data to transmit if length is 0 */
    }

    t.length = len * 8;                             /* Number of bits to transmit (1 byte = 8 bits) */
    t.tx_buffer = data;                             /* Fill the data */
    ret = spi_device_polling_transmit(handle, &t);  /* Start transmission */
    ESP_ERROR_CHECK(ret);                           /* Usually no issues */
}

/**
 * @brief       Process data via SPI
 * @param       handle       : SPI handle
 * @param       data         : Data to send
 * @retval      t.rx_data[0] : Received data
 */
uint8_t spi2_transfer_byte(spi_device_handle_t handle, uint8_t data)
{
    spi_transaction_t t;

    memset(&t, 0, sizeof(t));

    t.flags = SPI_TRANS_USE_TXDATA | SPI_TRANS_USE_RXDATA;
    t.length = 8;
    t.tx_data[0] = data;
    spi_device_transmit(handle, &t);

    return t.rx_data[0];
}
