#include <stdio.h>
#include <vector>
#include "rotary.h"
//#include "pedal.h"
#include "pedals_config.h"
#include "screen.h"
#include "foot.h"
#include "storage.h"
#include <iostream>

Rotary rotary;
Screen screen;
Storage storage;

Foot footButton1(GPIO_NUM_5);


void onRotaryShortPress() {
    if (screen.getCurrentScreen() == SCREEN_PRESET_CHANGE) { 
        deselectAllPedals(globalPedals);
        screen.nextScreen();
    } 
    else if (screen.getCurrentScreen() == SCREEN_PRESET_EDIT) { 
        selectPedalByIndex(globalPedals, screen.getCurrentPage());
        screen.nextScreen();
    } 
    else if (screen.getCurrentScreen() == SCREEN_PEDAL_PARAMS) { 
        for (auto& pedal : globalPedals) {
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
    deselectAllPedals(globalPedals);
    screen.previousScreen();
}

void onRotaryTurn(int value){
    if (value != 0){
        if (changeFaderValueIfSelected(globalPedals, value)) {
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

    // Criando um preset
    std::vector<std::vector<std::variant<bool, int>>> pedals = {
        {true, 12, 13, 44}
    };
    
    globalPresets[0] = Preset(1, "Clean Tone", {{true, 0, 20, 30}});
    globalPresets[1] = Preset(2, "Crunch", {{true, 40, 0, 60}});
    globalPresets[2] = Preset(3, "1 Stagio", {{true, 0, 80, 90}});
    globalPresets[3] = Preset(4, "2 Stagio", {{true, 15, 0, 0}});
    globalPresets[4] = Preset(5, "High Gain", {{true, 0, 55, 65}});
    globalPresets[5] = Preset(6, "Fuzz", {{true, 0, 85, 0}});

    while (true) {
        rotary.handleEvents();
        footButton1.handleEvents();
        
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}