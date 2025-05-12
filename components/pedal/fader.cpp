#include "fader.h"
#include "esp_err.h"

Fader::Fader(int pin, ledc_channel_t channel, const std::string& title, int value) : 
title(title), pin(pin), channel(channel), value(value) {
    // Configuração do timer LEDC
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_LOW_SPEED_MODE,
        .duty_resolution  = LEDC_TIMER_13_BIT, // Resolução de 13 bits
        .timer_num        = LEDC_TIMER_0,      // Use um timer válido
        .freq_hz          = 5000,              // Frequência de 5 kHz
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    // Configuração do canal LEDC
    ledc_channel_config_t ledc_channel = {
        .gpio_num = pin,                  // Número do GPIO
        .speed_mode = LEDC_LOW_SPEED_MODE, // Modo de velocidade
        .channel = channel,               // Canal LEDC
        .intr_type = LEDC_INTR_DISABLE,   // Interrupção desabilitada
        .timer_sel = LEDC_TIMER_0,        // Associa o canal ao timer válido
        .duty = 0,                        // Duty inicial
        .hpoint = 0,                      // Hpoint inicial
        .flags = { .output_invert = 0 }   // Sem inversão de saída
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));

};

void Fader::setValue(int value) {
    if (value < minValue) {
        this->value = maxValue;
    } else if (value > maxValue) {
        this->value = minValue;
    } else {
        this->value = value;
    }

    Fader::setPwm(this->value);
}

int Fader::getValue() const {
    return value;
}

void Fader::up() {
    setValue(value + 1);
}

void Fader::down() {
    setValue(value - 1);
}

void Fader::select() {
    selected = true;
}

void Fader::unselect() {
    selected = false;
}

void Fader::toggleSelect() {
    selected = !selected;
}

bool Fader::isSelected() const {
    return selected;
}

void Fader::addValue(int value) {
    setValue(this->value + value);
}

void Fader::setPwm(int dutyCycle) {
    // Define o duty cycle
    int maxDuty = (1 << LEDC_TIMER_13_BIT) - 1; // Valor máximo para 13 bits
    int duty = (dutyCycle * maxDuty) / 100;     // Converte dutyCycle (0-100%) para o valor do timer
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE, channel, duty));

    // Atualiza o duty cycle
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_LOW_SPEED_MODE, channel));
}