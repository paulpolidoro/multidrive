#include <stdio.h>
#include <vector>
#include "rotary.h"
#include "pedals_config.h"
#include "screen.h"
#include "foot.h"
#include "led.h"
#include "prompt.h"
#include "storage.h"
#include "preset.h"
#include <iostream>
#include "esp_partition.h"
#include "esp_log.h"

Rotary rotary;
Storage& storage = Storage::getInstance();
Screen screen(storage);
Prompt prompt;

Foot footPreset(FOOT_PRESET_PIN);
Foot footBypass(FOOT_BYPASS_PIN);
Led ledBypass(LED_BYPASS_PIN);
Led ledPreset(LED_PRESET_PIN);

void onRotaryShortPress() {
    if (prompt.isShowing()){
        prompt.fieldToggle();
        return;
    }
    
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
       if(prompt.isShowing()){
            if(value <0) {
                prompt.previous();
            } else if(value > 0) {
                prompt.next();
            }

            return;
        }

        if (changeFaderValueIfSelected(globalPedals, value)) {
            if(!ledPreset.isBlink()) {
                 ledPreset.blink(300);
            }
           
            screen.update();
            return;
        }

        ledPreset.blinkStop();

        if(value > 0) {
            screen.nextPage();
        }

        else if (value < 0) {
            screen.previousPage();
        }       
    }
}

extern "C" void app_main() {
    rotary.begin();

    rotary.onShortPress = onRotaryShortPress;
    rotary.onTurn = onRotaryTurn;
    rotary.onLongPress = onRotaryLongPress;

    footBypass.begin();
    footPreset.begin();

    footBypass.onShortPress = []() {
        if(prompt.isShowing()) {
            prompt.close();
            screen.update();
            return;
        }

        ledBypass.toggle();
    };

    footPreset.onDoublePress = []() {
        if(prompt.isShowing()) {
            return;
        }

         screen.goToScreenAndPage(SCREEN_PRESET_CHANGE, screen.getPageFromScreen(SCREEN_PRESET_CHANGE) - 1);
    };

    footPreset.onShortPress = []() {
        int index = screen.getPageFromScreen(SCREEN_PRESET_CHANGE);

        if(prompt.isShowing()) {
            std::string presetName = prompt.getText();
            
            storage.saveCurrent(index, presetName);
            ledPreset.blink(150, 3, 0);

            screen.alert("PRESET SAVED", 1000);

            prompt.close();

            screen.update();

            return;
        }

        screen.goToScreenAndPage(SCREEN_PRESET_CHANGE, screen.getPageFromScreen(SCREEN_PRESET_CHANGE) + 1);
        //screen.nextPage();
    };
    
    footPreset.onLongPress = []() {
        int index = screen.getPageFromScreen(SCREEN_PRESET_CHANGE);

        if(prompt.isShowing()) {
            return;
        }

        prompt.show("SAVE PRESET " + presetCode(index), storage.loadPreset(index).getName());
    };

    screen.init();

    while (true) {
        rotary.handleEvents();
        footPreset.handleEvents();
        footBypass.handleEvents();

        if(!prompt.isShowing()){
            screen.handleBackHome();
        }
        
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}