#ifndef ROTARY_H
#define ROTARY_H

#include "driver/pcnt.h"
#include "driver/gpio.h"

class Rotary {
public:
Rotary();
    void begin();
    int getPosition();
    void reset();
    
    bool onPress();      // Detecta quando o botão é pressionado
    bool onShortPress(); // Detecta um pressionamento curto (<2s)
    bool onLongPress();  // Detecta um pressionamento longo (>=2s)
    bool onRelease();

private:
    static const int clkPin = GPIO_NUM_18;  // Pino do CLK
    static const int dtPin = GPIO_NUM_19;   // Pino do DT
    static const int swPin = GPIO_NUM_23;   // Pino do botão SW
    pcnt_unit_t unit = PCNT_UNIT_0;
    int lastPosition = 0;

    bool lastButtonState = false;
    int64_t pressStartTime = 0;
    bool longPressHandled = false; 
    int longPressThreshold = 1000000; // 2 segundos em microssegundos

};

#endif // ROTARY_H