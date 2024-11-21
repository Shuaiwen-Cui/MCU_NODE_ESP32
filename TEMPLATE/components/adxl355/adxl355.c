/**
 * @file adxl355.c
 * @author SHUAIWEN CUI (SHUAIWEN001@e.ntu.edu.sg)
 * @brief This file is for driving the adxl355 for acceleration measurement.
 * @version 1.0
 * @date 2024-11-21
 * @ref https://github.com/MoustachedBird/ESP32_seismic_datalogger.git
 * @copyright Copyright (c) 2024
 *
 */

#include "adxl355.h"

// SPI communication handler
spi_device_handle_t adxl355_handler;

/* Configures SPI clock and SPI pins */
void adxl355_config_spi(void)
{
    esp_err_t ret;

    // SPI device configurations
    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = 1 * 1000 * 1000, // Clock output at 10 MHz, overclock = 26 MHz
        .mode = 0,                         // SPI mode 0
        .spics_io_num = CS_ADXL355,        // CS pin
        .queue_size = 7,                   // Queue up to 7 transactions at a time
        .address_bits = 8,                 // Device memory address length
        //.pre_cb=lcd_spi_pre_transfer_callback,  // Specify pre-transfer callback to handle D/C line
    };

    // Add the SPI device
    ret = spi_bus_add_device(SPI3_HOST, &devcfg, &adxl355_handler);
    ESP_ERROR_CHECK(ret);

    printf("ADXL355: Device successfully added\n");
}

/* Configures the accelerometer's sample rate */
void adxl355_100hz_rate(void)
{
    // Error variable
    esp_err_t ret;

    // Declare the transaction variable
    spi_transaction_t transaccion;

    // Declare data to send (8 bits)
    uint8_t datos_enviar = 0;

    // =====================================================================
    // =========== [For sending information over the SPI bus] ==============
    // =====================================================================

    //-=-=-=-=-=-=-=-=-=[ Change the sampling frequency ]-=-=-=-=-=-=-=-=-=-=-=-=

    /* The sampling frequency includes a low-pass filter.
    The cutoff frequency of the filter is:

    cutoff_frequency = sampling_frequency / 4

    Register: 0x28

    Data      Sampling Frequency  Low-pass Filter (Hz)
    0x00            4000                 1000
    0x01            2000                 500
    0x02            1000                 250
    0x03            500                  125
    0x04            250                  62.5
    0x05            125                  31.25
    0x06            62.5                 15.625
    0x07            31.25                7.813
    0x08            15.625               3.906
    0x09            7.813                1.953
    0x0A            3.906                0.977
    */

    memset(&transaccion, 0, sizeof(transaccion)); // Clear the variable with 0 to avoid errors
    datos_enviar = 0x05;                          // Sampling frequency of 100 Hz

    // Write data 1 to address 0x28, the filter register
    transaccion.length = 8;                              // Total data 8 bits.
    transaccion.tx_buffer = &datos_enviar;               // Pointer to data to send
    transaccion.addr = (0x28 << 1) | WRITE_FLAG_ADXL355; // Register to activate measurement mode

    ret = spi_device_transmit(adxl355_handler, &transaccion); // Transmit data
    assert(ret == ESP_OK);                                    // Should have had no issues.
    printf("ADXL355: Sampling frequency set to 100 Hz\n");
}

/* Configures and turns on the accelerometer (+-2G range) */
void adxl355_range_conf(void)
{
    // Error variable
    esp_err_t ret;

    // Declare the transaction variable
    spi_transaction_t transaccion;

    // Declare data to send (8 bits)
    uint8_t datos_enviar[2];

    //-=-=-=-=-=-=-=-=-=[ Change the measurement range ]-=-=-=-=-=-=-=-=-=-=-=-=
    datos_enviar[0] = RANGE_2G; // According to the datasheet, set bits b0 and b1 to "01"
    // to set the range to ±2g in register 0x2C.

    //-=-=-=-=-=-=-=-=-=[ Switch to measurement mode ]-=-=-=-=-=-=-=-=-=-=-=-=
    datos_enviar[1] = 0x06; // Only accelerometers enabled, disable the temperature sensor
    // Switch to measurement mode, exit standby mode.

    // =====================================================================
    // =========== [For sending information over the SPI bus] ==============
    // =====================================================================
    // Reset the transaction handler
    memset(&transaccion, 0, sizeof(transaccion)); // Clear the variable with 0 to avoid errors

    transaccion.length = 8 * sizeof(datos_enviar); // Length of the data in bits.
    transaccion.tx_buffer = &datos_enviar;         // Pointer to data to send

    transaccion.addr = (0x2C << 1) | WRITE_FLAG_ADXL355; /* Address to which the data will be sent. The length
          of the address is set in spi_device_interface_config_t using the address_bits parameter.
          */
    // Transmit the data
    ret = spi_device_transmit(adxl355_handler, &transaccion);
    assert(ret == ESP_OK); // Check for no errors

    printf("ADXL355: Range set to ±2G and sensor in measurement mode\n");
}

/* Read acceleration values, parameters: pointer of buffer where data will be saved */
void adxl355_read_accl(uint8_t *data_received, uint8_t size_buffer)
{
    esp_err_t ret;

    // Declare the transaction variable
    spi_transaction_t transaccion;

    // =====================================================================
    // =========== [For receiving information over the SPI bus] ============
    // =====================================================================

    // Reset the transaction handler
    memset(&transaccion, 0, sizeof(transaccion));
    // Clear the variable with 0 to avoid errors

    transaccion.length = 8 * size_buffer;          // Transaction size in bits
    transaccion.rx_buffer = data_received;         // Pointer to the buffer for receiving data
    transaccion.addr = XDATA3 | READ_FLAG_ADXL355; // Read the register for the X-axis most significant byte (XDATA3)

    ret = spi_device_transmit(adxl355_handler, &transaccion); // Transmit
    assert(ret == ESP_OK);                                    // Should have had no issues.
}
