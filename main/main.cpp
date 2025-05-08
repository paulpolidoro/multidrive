#include <stdio.h>
#include <vector>
#include "rotary.h"
#include "pedals_config.h"
#include "screen.h"
#include "foot.h"
#include "storage.h"
#include <iostream>
#include "esp_partition.h"
#include "esp_log.h"

Rotary rotary;
Storage& storage = Storage::getInstance();
Screen screen(storage);

Foot footButton1(GPIO_NUM_2);

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
        int index = screen.getPageFromScreen(SCREEN_PRESET_CHANGE);
        storage.saveCurrent(index, "Preset_" + std::to_string(index));
        printf("PRESET %d SALVO!\n", index);
        screen.savePreset();
    };

    footButton1.onRelease = []() {
        printf("Botão 1 liberado!\n");
    };

    screen.init();

    while (true) {
        rotary.handleEvents();
        footButton1.handleEvents();
        screen.handleBackHome();
        
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}