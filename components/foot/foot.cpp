#include "foot.h"

Foot::Foot(gpio_num_t pin) : pin(pin) {}

void Foot::begin() {
    gpio_config_t io_conf = {};
    io_conf.pin_bit_mask = (1ULL << pin);
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio_config(&io_conf);
}

bool Foot::pressEvent() {
    bool buttonState = gpio_get_level(pin) == 0;
    
    if (buttonState && !lastButtonState) {
        lastButtonState = true;
        pressStartTime = esp_timer_get_time();

        if (checkDoublePress){
            int64_t doublePressDuration = esp_timer_get_time() - doublePressStartTime;

            if (doublePressDuration < doublePressThreshold) {
                doublePresseHandled = true; 
                checkDoublePress = false;
            }else{
                doublePressStartTime = esp_timer_get_time();
            }
        }else{
            doublePressStartTime = esp_timer_get_time();
            checkDoublePress = true; // Set the flag to check for double press
        }

        return true;
    }

    return false;
}

bool Foot::shortPressEvent() {
    bool buttonState = gpio_get_level(pin) == 0;

    if (!buttonState && lastButtonState) {
        int64_t pressDuration = esp_timer_get_time() - pressStartTime;

        if (pressDuration < longPressThreshold && pressDuration > doublePressThreshold) {
            return true;
        }
    }

    return false;
}

bool Foot::longPressEvent() {
    bool buttonState = gpio_get_level(pin) == 0;
    int64_t pressDuration = esp_timer_get_time() - pressStartTime;

    if (buttonState && pressDuration >= longPressThreshold && !longPressHandled) {
        longPressHandled = true;
        return true;
    }
    if (!buttonState) {
        longPressHandled = false;
    }

    return false;
}

bool Foot::releaseEvent() {
    bool buttonState = gpio_get_level(pin) == 0;

    if (!buttonState && lastButtonState) {
        lastButtonState = false;
        return true;
    }

    if (buttonState) {
        lastButtonState = true;
    }

    return false;
}

void Foot::handleEvents() {
    if (pressEvent()) {
        onPress();
    }

    if (doublePresseHandled){
        doublePresseHandled = false; // Reset the count if the time exceeds the threshold
        onDoublePress();
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