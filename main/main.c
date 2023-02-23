#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "esp_log.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/spi_master.h"

#define CLK_PIN 18
#define MOSI_PIN 23
#define CS_PIN 5

spi_device_handle_t spi3;

// static const char *TAG = "BG_CHANGER";

static void spi_init()
{
    esp_err_t ret;
    spi_bus_config_t buscfg = {
        .miso_io_num = -1,
        .mosi_io_num = MOSI_PIN,
        .sclk_io_num = CLK_PIN,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 32,
    };
    ret = spi_bus_initialize(SPI3_HOST, &buscfg, SPI_DMA_CH_AUTO);
    ESP_ERROR_CHECK(ret);
    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = 80000000, // 80 MHz
        .mode = 0,                  // SPI mode 0
        .spics_io_num = CS_PIN,
        .queue_size = 1,
        .flags = SPI_DEVICE_HALFDUPLEX,
        .pre_cb = NULL,
        .post_cb = NULL,
    };
    ESP_ERROR_CHECK(spi_bus_add_device(SPI3_HOST, &devcfg, &spi3));
};

static void set_bg(uint16_t value)
{
    uint8_t tx_data[6] = {
        0, 0, 0, 0,
        value >> 8,
        value & 0xFF};
    spi_transaction_t t = {
        .tx_buffer = tx_data,
        .length = 6 * 8};
    ESP_ERROR_CHECK(spi_device_polling_transmit(spi3, &t));
}

static void set_bg_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
    uint16_t current_color = 0x0000 | (red << 8) | (green << 4) | blue;
    set_bg(current_color);
}

void app_main(void) {
    spi_init();
    while (1) {
        int h, s, v;
        float r = 0;
        float g = 0;
        float b = 0;

        for (h = 0; h < 360; h++) {
            s = 100;
            v = 100;
            // Convert HSV to RGB
            float hue = h / 60.0f;
            float saturation = s / 100.0f;
            float value = v / 100.0f;
            int hi = (int)floor(hue) % 6;
            float f = hue - (int)floor(hue);
            float p = value * (1 - saturation);
            float q = value * (1 - f * saturation);
            float t = value * (1 - (1 - f) * saturation);

            switch (hi)
            {
            case 0:
                r = value;
                g = t;
                b = p;
                break;
            case 1:
                r = q;
                g = value;
                b = p;
                break;
            case 2:
                r = p;
                g = value;
                b = t;
                break;
            case 3:
                r = p;
                g = q;
                b = value;
                break;
            case 4:
                r = t;
                g = p;
                b = value;
                break;
            case 5:
                r = value;
                g = p;
                b = q;
                break;
            }

            // Convert RGB to 4-bit values and display the color
            uint8_t red = (uint8_t)(r * 15);
            uint8_t green  = (uint8_t)(g * 15);
            uint8_t blue  = (uint8_t)(b * 15);
            
            vTaskDelay(17 / portTICK_PERIOD_MS);
            set_bg_rgb(red, green, blue);
        }
    }
}
