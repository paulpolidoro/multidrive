#include "display.h"
#include <esp_log.h>
#include "ssd1306.h"

static const i2c_master_bus_config_t i2c_master_bus_config = {
    .i2c_port = I2C_NUM_0,
    .sda_io_num = GPIO_NUM_21,  // Ordem correta
    .scl_io_num = GPIO_NUM_22,
    .clk_source = I2C_CLK_SRC_DEFAULT,
    .glitch_ignore_cnt = 7,
    .flags = {
        .enable_internal_pullup = true
    }
};

static const i2c_ssd1306_config_t i2c_ssd1306_config = {
    .i2c_device_address = 0x3C,
    .i2c_scl_speed_hz = 400000,
    .width = 128,
    .height = 64,
    .wise = SSD1306_TOP_TO_BOTTOM
};

Display::Display() {}

Display::~Display() {}

void Display::init() {
    ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_master_bus_config, &i2c_master_bus));
    ESP_ERROR_CHECK(i2c_ssd1306_init(i2c_master_bus, i2c_ssd1306_config, &i2c_ssd1306));
}

void Display::clear() {
   ESP_ERROR_CHECK(i2c_ssd1306_buffer_clear(&i2c_ssd1306));
}

void Display::printText(const char* text, int x, int y, bool invert) {
    ESP_ERROR_CHECK(i2c_ssd1306_buffer_text(&i2c_ssd1306, x, y, text, invert));
}

void Display::addFader(int y, bool select, bool setting, const Fader& fader) {
    int x = 2;
    int w = 101;
    int h = 4;
    int font_h = 8;
    int space_title = 8;
    int value = 0;

    if (fader.value > 100) {
        value = 100;
    } else if (fader.value < 0) {
        value = 0;
    } else {
        value = fader.value;
    }

    if (select) {
        ESP_ERROR_CHECK(i2c_ssd1306_buffer_fill_space(&i2c_ssd1306, 0, 127, y-2, y + font_h + h +4, true));
        ESP_ERROR_CHECK(i2c_ssd1306_buffer_fill_space(&i2c_ssd1306, 1, 126, y-1, y + font_h + h +3, false));
    }
    
    ESP_ERROR_CHECK(i2c_ssd1306_buffer_fill_space(&i2c_ssd1306, x, x + w, y + space_title, y + h + space_title +2, true));

    if (value < 100) {
        ESP_ERROR_CHECK(i2c_ssd1306_buffer_fill_space(
            &i2c_ssd1306, 
            (x + 1) + value,
            x + w -1, 
            y + space_title + 1, 
            y + h + space_title + 1, 
            false)
        );
    }

    ESP_ERROR_CHECK(i2c_ssd1306_buffer_int(&i2c_ssd1306, w + x + 1, y+font_h, value, false));

    ESP_ERROR_CHECK(i2c_ssd1306_buffer_text(&i2c_ssd1306, x, y, fader.title.c_str(), false));

   

    if (setting) {
        ESP_ERROR_CHECK(i2c_ssd1306_buffer_fill_space(&i2c_ssd1306, x + w - 2, x + w, y, y + h, true));
    }
  
    ESP_ERROR_CHECK(i2c_ssd1306_buffer_to_ram(&i2c_ssd1306));
}


void Display::update() {
   ESP_ERROR_CHECK(i2c_ssd1306_buffer_to_ram(&i2c_ssd1306));
}

void Display::scrollVertical(int offset) {
    i2c_ssd1306_buffer_clear(&i2c_ssd1306); // Limpa o buffer
    i2c_ssd1306_buffer_text(&i2c_ssd1306, 10, 20 - offset, "Texto rolando", false);
    i2c_ssd1306_buffer_to_ram(&i2c_ssd1306); // Atualiza a tela
}