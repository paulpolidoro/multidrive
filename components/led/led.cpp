#include "led.h"
#include "driver/gpio.h"
#include "esp_log.h"

Led::Led(int pin) : pin(pin), state(false), blinking(false), blinkTaskHandle(nullptr), previousState(false) {
    gpio_reset_pin((gpio_num_t)pin); // Reseta o pino para o estado padrão
    gpio_set_direction((gpio_num_t)pin, GPIO_MODE_OUTPUT); // Configura como saída
    off(); // Inicializa o LED como desligado
}

void Led::on() {
    if (blinking) {
        blinkStop(); // Para o piscar se estiver ativo
    }
    state = true;
    gpio_set_level((gpio_num_t)pin, 1);
}

void Led::off() {
    if (blinking) {
        blinkStop(); // Para o piscar se estiver ativo
    }
    state = false;
    gpio_set_level((gpio_num_t)pin, 0);
}

void Led::toggle() {
    if (state) {
        off();
    } else {
        on();
    }
}

bool Led::isOn() const {
    return state;
}

bool Led::isOff() const {
    return !state;
}

void Led::blink(int intervalMs, int blinkCount, int blinkDurationMs) {
    if (blinking) {
        blinkStop();
    }

    previousState = state;
    off();
    blinking = true;

    led_blink_params_t* params = new led_blink_params_t{this, intervalMs, blinkCount, blinkDurationMs};

    xTaskCreate(
        blinkTask,
        "LedBlinkTask",
        2048,
        params,
        1,
        &blinkTaskHandle
    );
}

bool Led::isBlink() const {
    return blinking;
}

void Led::blinkStop() {
    if (blinking && blinkTaskHandle != nullptr) {
        vTaskDelete(blinkTaskHandle);
        blinkTaskHandle = nullptr;
        blinking = false;

        if (previousState) {
            on();
        } else {
            off();
        }
    }
}

void Led::blinkTask(void* params) {
    led_blink_params_t* blinkParams = static_cast<led_blink_params_t*>(params);
    Led* led = blinkParams->led;
    int intervalMs = blinkParams->intervalMs;
    int blinkCount = blinkParams->blinkCount;
    int blinkDurationMs = blinkParams->blinkDurationMs;

    int count = 0;
    TickType_t startTime = xTaskGetTickCount();

    while (true) {
        gpio_set_level((gpio_num_t)led->pin, 1);
        vTaskDelay(pdMS_TO_TICKS(intervalMs));

        gpio_set_level((gpio_num_t)led->pin, 0);
        vTaskDelay(pdMS_TO_TICKS(intervalMs));

        if (blinkCount > 0 && ++count >= blinkCount) {
            break;
        }

        if (blinkDurationMs > 0 && (xTaskGetTickCount() - startTime) * portTICK_PERIOD_MS >= blinkDurationMs) {
            break;
        }
    }

    led->blinking = false;
    led->blinkStop();

    delete blinkParams;
    vTaskDelete(nullptr);
}