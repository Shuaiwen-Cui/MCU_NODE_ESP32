/**
 * @file dht11.c
 * @author 
 * SHUAIWEN CUI (SHUAIWEN001@e.ntu.edu.sg)
 * @brief DHT11 sensor driver implementation
 * @version 1.0
 * @date 2024-11-16
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
// #include "nvs_flash.h"
#include <driver/rmt_rx.h>
#include <driver/rmt_tx.h>
#include <soc/rmt_reg.h>
#include "esp_log.h"
#include "driver/gpio.h"
#include "esp_system.h"
#include "esp32s3/rom/ets_sys.h"
#include "dht11.h"

#define TAG "DHT11"

uint8_t DHT11_PIN = -1;

// RMT receive channel handle
static rmt_channel_handle_t rx_chan_handle = NULL;

// Data receive queue
static QueueHandle_t rx_receive_queue = NULL;

// Process the RMT pulse data into temperature and humidity values
static int parse_items(rmt_symbol_word_t *item, int item_num, int *humidity, int *temp_x10);

// Callback function for RMT reception completion
static bool IRAM_ATTR example_rmt_rx_done_callback(rmt_channel_handle_t channel, const rmt_rx_done_event_data_t *edata, void *user_data)
{
    BaseType_t high_task_wakeup = pdFALSE;
    QueueHandle_t rx_receive_queue = (QueueHandle_t)user_data;
    // Send the received RMT symbols to the parser task
    xQueueSendFromISR(rx_receive_queue, edata, &high_task_wakeup);
    return high_task_wakeup == pdTRUE;
}

/** Initialize the DHT11 sensor
 * @param void
 * @return None
 */
void DHT11_Init(void)
{
    DHT11_PIN = DHT11_GPIO_PIN;

    rmt_rx_channel_config_t rx_chan_config = {
        .clk_src = RMT_CLK_SRC_APB,   // Select clock source
        .resolution_hz = 1000 * 1000, // 1 MHz resolution, i.e., 1 tick = 1 µs
        .mem_block_symbols = 64,      // Memory block size, i.e., 64 * 4 = 256 bytes
        .gpio_num = DHT11_PIN,        // GPIO pin number
        .flags.invert_in = false,     // Do not invert the input signal
        .flags.with_dma = false,      // No DMA backend (specific to ESP32S3)
    };
    // Create RMT receive channel
    ESP_ERROR_CHECK(rmt_new_rx_channel(&rx_chan_config, &rx_chan_handle));

    // Create a data receive queue
    rx_receive_queue = xQueueCreate(20, sizeof(rmt_rx_done_event_data_t));
    assert(rx_receive_queue);

    // Register the reception completion callback function
    ESP_LOGI(TAG, "register RX done callback");
    rmt_rx_event_callbacks_t cbs = {
        .on_recv_done = example_rmt_rx_done_callback,
    };
    ESP_ERROR_CHECK(rmt_rx_register_event_callbacks(rx_chan_handle, &cbs, rx_receive_queue));

    // Enable the RMT receive channel
    ESP_ERROR_CHECK(rmt_enable(rx_chan_handle));
}

// Process the RMT pulse data into temperature and humidity values (rmt_symbol_word_t is called an RMT symbol)
static int parse_items(rmt_symbol_word_t *item, int item_num, int *humidity, int *temp_x10)
{
    int i = 0;
    unsigned int rh = 0, temp = 0, checksum = 0;
    if (item_num < 41)
    { // Check if there are enough pulses
        return 0;
    }
    if (item_num > 41)
        item++; // Skip the start signal pulse

    for (i = 0; i < 16; i++, item++) // Extract humidity data
    {
        uint16_t duration = 0;
        if (item->level0)
            duration = item->duration0;
        else
            duration = item->duration1;
        rh = (rh << 1) + (duration < 35 ? 0 : 1);
    }

    for (i = 0; i < 16; i++, item++) // Extract temperature data
    {
        uint16_t duration = 0;
        if (item->level0)
            duration = item->duration0;
        else
            duration = item->duration1;
        temp = (temp << 1) + (duration < 35 ? 0 : 1);
    }

    for (i = 0; i < 8; i++, item++)
    { // Extract checksum data

        uint16_t duration = 0;
        if (item->level0)
            duration = item->duration0;
        else
            duration = item->duration1;
        checksum = (checksum << 1) + (duration < 35 ? 0 : 1);
    }
    // Check the checksum
    if ((((temp >> 8) + temp + (rh >> 8) + rh) & 0xFF) != checksum)
    {
        ESP_LOGI(TAG, "Checksum failure %4X %4X %2X\n", temp, rh, checksum);
        return 0;
    }
    // Return data

    rh = rh >> 8;
    temp = (temp >> 8) * 10 + (temp & 0xFF);

    // Validate the data
    if (rh <= 100)
        *humidity = rh;
    if (temp <= 600)
        *temp_x10 = temp;
    return 1;
}

/** Retrieve data from the DHT11 sensor
 * @param temp_x10 Temperature value multiplied by 10
 * @return int 0 if failed, 1 if successful
 */
int DHT11_StartGet(int *temp_x10, int *humidity)
{
    // Send a 20ms start signal pulse to initiate DHT11 single-bus communication
    gpio_set_direction(DHT11_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(DHT11_PIN, 1);
    ets_delay_us(1000);
    gpio_set_level(DHT11_PIN, 0);
    ets_delay_us(20000);
    // Pull high for 20us
    gpio_set_level(DHT11_PIN, 1);
    ets_delay_us(20);
    // Set the signal line to input to prepare for receiving data
    gpio_set_direction(DHT11_PIN, GPIO_MODE_INPUT);
    gpio_set_pull_mode(DHT11_PIN, GPIO_PULLUP_ONLY);

    // Start the RMT receiver to fetch data
    rmt_receive_config_t receive_config = {
        .signal_range_min_ns = 100,         // Minimum pulse width (0.1us); signals shorter than this are considered noise
        .signal_range_max_ns = 1000 * 1000, // Maximum pulse width (1000us); signals longer than this are considered end signals
    };

    static rmt_symbol_word_t raw_symbols[128]; // Receive buffer
    static rmt_rx_done_event_data_t rx_data;   // Actual received data
    ESP_ERROR_CHECK(rmt_receive(rx_chan_handle, raw_symbols, sizeof(raw_symbols), &receive_config));

    // Wait for RX done signal
    if (xQueueReceive(rx_receive_queue, &rx_data, pdMS_TO_TICKS(1000)) == pdTRUE)
    {
        // Parse the received symbols and return the result
        return parse_items(rx_data.received_symbols, rx_data.num_symbols, humidity, temp_x10);
    }
    return 0;
}
