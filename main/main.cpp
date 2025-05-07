#include <stdio.h>
#include <vector>
#include "rotary.h"
#include "pedal.h"
#include "screen.h"
#include "pedals_config.h"
#include "foot.h"

Rotary rotary;
Screen screen;

Foot footButton1(GPIO_NUM_5);


void onRotaryShortPress() {
    if (screen.getCurrentScreen() == SCREEN_PRESET_CHANGE) { 
        deselectAllPedals(pedals);
        screen.nextScreen();
    } 
    else if (screen.getCurrentScreen() == SCREEN_PRESET_EDIT) { 
        selectPedalByIndex(pedals, screen.getCurrentPage());
        screen.nextScreen();
    } 
    else if (screen.getCurrentScreen() == SCREEN_PEDAL_PARAMS) { 
        for (auto& pedal : pedals) {
            if (pedal->isSelected()) {
                if (screen.getCurrentPage() >= 0 && screen.getCurrentPage() < pedal->faders.size()) {
                    pedal->toggleSelectFaderByIndex(screen.getCurrentPage());
                }

                break;
            }
        }

        screen.update();
    }
}

void onRotaryLongPress(){
    deselectAllPedals(pedals);
    screen.previousScreen();
}

void onRotaryTurn(int value){
    if (value != 0){
        if (changeFaderValueIfSelected(pedals, value)) {
            screen.update();
            return;
        }

        if(value > 0) {
            screen.nextPage();
        }

        if (value < 0) {
            screen.previousPage();
        }       
    }
}

extern "C" void app_main() {
    screen.init();
    screen.update();
    
    rotary.begin();

    rotary.onShortPress = onRotaryShortPress;
    rotary.onTurn = onRotaryTurn;
    rotary.onLongPress = onRotaryLongPress;

    footButton1.begin();

    footButton1.onPress = []() {
        printf("Botão 1 pressionado!\n");
    };

    footButton1.onShortPress = []() {
        printf("Botão 1 pressionado curto!\n");
    };

    footButton1.onLongPress = []() {
        printf("Botão 1 pressionado longo!\n");
    };

    footButton1.onRelease = []() {
        printf("Botão 1 liberado!\n");
    };

    while (true) {
        rotary.handleEvents();
        footButton1.handleEvents();
        
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}