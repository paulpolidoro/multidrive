#include "rotary.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


Rotary::Rotary() {}

void Rotary::begin() {
    gpio_config_t io_conf = {};
    io_conf.pin_bit_mask = (1ULL << swPin);
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpio_config(&io_conf);

    pcnt_config_t pcnt_config = {
        .pulse_gpio_num = clkPin,
        .ctrl_gpio_num = dtPin,
        .lctrl_mode = PCNT_MODE_KEEP,
        .hctrl_mode = PCNT_MODE_REVERSE,
        .pos_mode = PCNT_COUNT_INC,
        .neg_mode = PCNT_COUNT_DEC,
        .counter_h_lim = 1000,
        .counter_l_lim = -1000,
        .unit = PCNT_UNIT_0,
        .channel = PCNT_CHANNEL_0,
    };
    
    pcnt_unit_config(&pcnt_config);
    //pcnt_isr_service_install(0); // Instala o serviço ISR   

      // Zera o contador do PCNT
      pcnt_counter_pause(unit);
      pcnt_counter_clear(unit);
      pcnt_counter_resume(unit);
  
      // Sincroniza lastPosition com o valor inicial do contador
      int16_t count = 0;
      pcnt_get_counter_value(unit, &count);
      lastPosition = count;
  
      // Adiciona um pequeno atraso para estabilizar os sinais
      vTaskDelay(pdMS_TO_TICKS(50));
}

int Rotary::getPosition() {
    int16_t count = 0;
    esp_err_t err = pcnt_get_counter_value(unit, &count);

    if (err != ESP_OK) {
        // Trate o erro apropriadamente
        return 0; // Ou outro valor que faça sentido no seu contexto
    }

    int direction = 0;
    if (count > lastPosition) {
        direction = 1;  // Rotação para a direita
    } else if (count < lastPosition) {
        direction = -1; // Rotação para a esquerda
    } else {
        direction = 0;  // Sem rotação
    }

    lastPosition = count; // Atualiza a posição anterior
    return direction;
}

bool Rotary::pressEvent() {
    bool buttonState = gpio_get_level(static_cast<gpio_num_t>(swPin)) == 0;

    if (buttonState && !lastButtonState) {
        lastButtonState = true;
        pressStartTime = esp_timer_get_time();
        return true;
    }

    return false;
}

bool Rotary::shortPressEvent() {
    bool buttonState = gpio_get_level(static_cast<gpio_num_t>(swPin)) == 0;

    if (!buttonState && lastButtonState) {
        int64_t pressDuration = esp_timer_get_time() - pressStartTime;

        if (pressDuration < longPressThreshold) { 
            return true;
        }
    }

    return false;
}

bool Rotary::longPressEvent() {
    bool buttonState = gpio_get_level(static_cast<gpio_num_t>(swPin)) == 0;
    int64_t pressDuration = esp_timer_get_time() - pressStartTime;

    if (buttonState && pressDuration >= longPressThreshold && !longPressHandled) {
        longPressHandled = true; // Marca que o pressionamento longo foi tratado
        return true;
    }
    if (!buttonState) {
        longPressHandled = false; // Reseta o estado quando o botão é solto
    }
    
    return false;
}

bool Rotary::releaseEvent() {
    bool buttonState = gpio_get_level(static_cast<gpio_num_t>(swPin)) == 0;

    if (!buttonState && lastButtonState) {
        lastButtonState = false;
      
        return true; // Botão foi solto
    }

    if (buttonState) {
        lastButtonState = true; // Atualiza o estado do botão quando pressionado
    }

    return false;
}

void Rotary::handleEvents() {
    int value = getPosition();
    if (value != 0) {
        onTurn(value);
    }

    if (pressEvent()) {
        onPress();
    }

    if (shortPressEvent()) {
        onShortPress();
    }

    if (longPressEvent()) {
        onLongPress();
    }

    if (releaseEvent()) {
        onRelease();
    }
}