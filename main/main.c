#include <stdio.h>
#include "esp_log.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/spi_master.h"

#define CLK_PIN     18
#define MOSI_PIN    23
#define CS_PIN      5

spi_device_handle_t spi3;

static const char *TAG = "BG_CHANGER";
static const uint16_t colors [8] = {
    0b0000000000000000,
    0b0000101000000000,
    0b0000101010100000,
    0b0000000010100000,
    0b0000000010101010,
    0b0000000000001010,
    0b0000101000001010,
    0b0000101010101010,
};
static char *color_names [8] = {
    "Transparent",
    "Red",
    "Yellow",
    "Green",
    "Cyan",
    "Blue",
    "Magenta",
    "White",
};

static void spi_init() {
    esp_err_t ret;
    spi_bus_config_t buscfg={
        .miso_io_num = -1,
        .mosi_io_num = MOSI_PIN,
        .sclk_io_num = CLK_PIN,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 32,
    };
    ret = spi_bus_initialize(SPI3_HOST, &buscfg, SPI_DMA_CH_AUTO);
    ESP_ERROR_CHECK(ret);
    spi_device_interface_config_t devcfg={
        .clock_speed_hz = 80000000,  // 80 MHz
        .mode = 0,                  //SPI mode 0
        .spics_io_num = CS_PIN,     
        .queue_size = 1,
        .flags = SPI_DEVICE_HALFDUPLEX,
        .pre_cb = NULL,
        .post_cb = NULL,
    };
    ESP_ERROR_CHECK(spi_bus_add_device(SPI3_HOST, &devcfg, &spi3));
};

static void set_bg(uint16_t value) {
    uint8_t tx_data[6] = { 
        0,0,0,1, 
        value >> 8,
        value & 0xFF
    };
    spi_transaction_t t = {
        .tx_buffer = tx_data,
        .length = 6 * 8
    };
    ESP_ERROR_CHECK(spi_device_polling_transmit(spi3, &t));
}

void app_main(void)
{  
    spi_init();
    uint8_t current_color = 0;
    while(1){
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        ESP_LOGI(TAG, "COLOR: %s", color_names[current_color]);
        set_bg(colors[current_color]);
        if(current_color == 7){
            current_color = 0;
        }else{
            current_color = current_color + 1;
        }
    }
}
