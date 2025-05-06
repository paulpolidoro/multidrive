#ifndef ROTARY_H
#define ROTARY_H

#include "driver/pcnt.h"
#include "driver/gpio.h"
#include <functional> 

class Rotary {
public:
Rotary();
    void begin();
    void handleEvents();
    
    std::function<void()> onPress = []() {};
    std::function<void()> onShortPress = []() {};
    std::function<void()> onLongPress = []() {};
    std::function<void(int)> onTurn = [](int) {};
    std::function<void()> onRelease = []() {};

private:
    static const int clkPin = GPIO_NUM_18;  // Pino do CLK
    static const int dtPin = GPIO_NUM_19;   // Pino do DT
    static const int swPin = GPIO_NUM_23; 

    int getPosition();
    void reset();
    
    bool pressEvent();
    bool shortPressEvent();
    bool longPressEvent();
    bool releaseEvent();
    
    pcnt_unit_t unit = PCNT_UNIT_0;
    int lastPosition = 0;

    bool lastButtonState = false;
    int64_t pressStartTime = 0;
    bool longPressHandled = false; 
    int longPressThreshold = 1000000;

};

#endif // ROTARY_H