#include "fader.h"
#include "driver/ledc.h"
#include "esp_err.h"

Fader::Fader(int pin, const std::string& title, int value) : title(title), pin(pin), value(value) {};

void Fader::setValue(int value) {
    if (value < minValue) {
        this->value = minValue;
    } else if (value > maxValue) {
        this->value = maxValue;
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
    // Configuração do canal LEDC
    ledc_channel_config_t ledc_channel = {
        .gpio_num = pin,                  // Número do GPIO
        .speed_mode = LEDC_LOW_SPEED_MODE, // Modo de velocidade
        .channel = LEDC_CHANNEL_0,        // Canal LEDC
        .intr_type = LEDC_INTR_DISABLE,   // Interrupção desabilitada
        .timer_sel = LEDC_TIMER_0,        // Timer selecionado
        .duty = 0,                        // Duty inicial
        .hpoint = 0,                      // Hpoint inicial
        .sleep_mode = LEDC_SLEEP_MODE_NO_ALIVE_NO_PD, // Modo de sleep
        .flags = { .output_invert = 0 }   // Sem inversão de saída
    };

    // Configura o canal LEDC
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));

    // Configuração do timer LEDC
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_LOW_SPEED_MODE,
        .duty_resolution  = LEDC_TIMER_13_BIT, // Resolução de 13 bits
        .timer_num        = LEDC_TIMER_0,
        .freq_hz          = 5000,              // Frequência de 5 kHz
        .clk_cfg          = LEDC_AUTO_CLK
    };

    // Configura o timer LEDC
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    // Define o duty cycle
    int maxDuty = (1 << LEDC_TIMER_13_BIT) - 1; // Valor máximo para 13 bits
    int duty = (dutyCycle * maxDuty) / 100;     // Converte dutyCycle (0-100%) para o valor do timer
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty));

    // Atualiza o duty cycle
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0));
}