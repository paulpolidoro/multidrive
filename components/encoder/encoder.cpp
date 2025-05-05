#include "encoder.h"
#include "esp_timer.h"


Encoder::Encoder() {}

void Encoder::begin() {
    // Configuração do botão SW
    gpio_config_t io_conf = {};
    io_conf.pin_bit_mask = (1ULL << swPin);
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio_config(&io_conf);
}

int Encoder::getPosition() {
    int16_t count = 0;
    pcnt_get_counter_value(unit, &count);

    int direction = 0;
    if (count > lastPosition) {
        direction = 1;  // Rotação para a direita
    } else if (count < lastPosition) {
        direction = -1; // Rotação para a esquerda
    }

    lastPosition = count; // Atualiza a posição anterior
    return direction;
}


bool Encoder::onPress() {
    bool buttonState = gpio_get_level(static_cast<gpio_num_t>(swPin)) == 0;

    if (buttonState && !lastButtonState) {
        lastButtonState = true;
        pressStartTime = esp_timer_get_time();
        return true; // Botão foi pressionado
    }

    return false;
}

bool Encoder::onShortPress() {
    bool buttonState = gpio_get_level(static_cast<gpio_num_t>(swPin)) == 0;

    if (!buttonState && lastButtonState) {
        lastButtonState = false;
        int64_t pressDuration = esp_timer_get_time() - pressStartTime;

        if (pressDuration < 2000000) { // < 2 segundos
            return true;
        }
    }

    return false;
}

bool Encoder::onLongPress() {
    bool buttonState = gpio_get_level(static_cast<gpio_num_t>(swPin)) == 0;
    int64_t pressDuration = esp_timer_get_time() - pressStartTime;

    return buttonState && pressDuration >= 2000000; // Pressionado por 2s ou mais
}

bool Encoder::onRelease() {
    bool buttonState = gpio_get_level(static_cast<gpio_num_t>(swPin)) == 0;

    if (!buttonState && lastButtonState) {
        lastButtonState = false;
        return true; // Botão foi solto
    }

    return false;
}