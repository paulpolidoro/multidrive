#ifndef FOOT_H
#define FOOT_H

#include "driver/gpio.h"
#include "esp_timer.h"
#include <functional>

class Foot {
public:
    Foot(gpio_num_t pin);

    void begin();
    void handleEvents();

    // Callbacks
    std::function<void()> onPress = []() {};
    std::function<void()> onShortPress = []() {};
    std::function<void()> onLongPress = []() {};
    std::function<void()> onRelease = []() {};

private:
    gpio_num_t pin;
    bool lastButtonState = false;
    bool longPressHandled = false;
    int64_t pressStartTime = 0;
    const int64_t longPressThreshold = 1000000; // 1 segundo (em microssegundos)

    bool pressEvent();
    bool shortPressEvent();
    bool longPressEvent();
    bool releaseEvent();
};

#endif // FOOT_H