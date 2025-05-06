#include <stdio.h>
//#include "display.h"
#include "rotary.h"
#include "pedal.h"
#include "screen.h"
#include <vector>

// Display display2;

Rotary rotary;
Screen screen;

extern std::vector<std::shared_ptr<Pedal>> pedals = {
    std::make_shared<Pedal>(Pedal{1, "Morning Glory", {Fader{"Volume"}, Fader{"Drive"}, Fader{"Tone"}, Fader{"Gain"}}}), 
    std::make_shared<Pedal>(Pedal{2, "OCD", {Fader{"Volume"}, Fader{"Drive"}, Fader{"Tone"}}}),
    std::make_shared<Pedal>(Pedal{3, "1989", {Fader{"Drive"}, Fader{"Cut"}, Fader{"Volume"}}}),
    std::make_shared<Pedal>(Pedal{4, "Timmy", {Fader{"Drive"}, Fader{"Gain"}, Fader{"Bass"}, Fader{"Treble"}}}),
};

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
    

    //display.update();
    
    rotary.begin();

    rotary.onShortPress = onRotaryShortPress;
    rotary.onTurn = onRotaryTurn;
    rotary.onLongPress = onRotaryLongPress;

    while (true) {
        rotary.handleEvents();
        
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}