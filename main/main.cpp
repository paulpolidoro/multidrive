#include <stdio.h>
#include "display.h"
#include "rotary.h"
#include "pedal.h"
#include "render.h"
#include <vector>

Display display;

extern std::vector<std::shared_ptr<pedal_t>> pedals;

extern std::vector<std::shared_ptr<Pedal>> pedais = {
    std::make_shared<Pedal>(Pedal{1, "Morning Glory", {Fader{"Volume", 50}, Fader{"Drive", 75}, Fader{"Tone", 30}, Fader{"Gain", 20}}}), 
    std::make_shared<Pedal>(Pedal{2, "OCD", {Fader{"Volume", 60}, Fader{"Drive", 80}, Fader{"Tone", 40}}}),
    std::make_shared<Pedal>(Pedal{3, "1989", {Fader{"Drive", 70}, Fader{"Cut", 65}, Fader{"Volume", 50}}})
};

bool changeFaderValue(int rotaryValue) {
    for (auto& pedal : pedals) {
        if (pedal->selected) {
            // Verifica se o fader na página atual já está selecionado
            if (display.getCurrentPage() >= 0 && display.getCurrentPage() < pedal->faders.size()) {
                auto& fader = pedal->faders[display.getCurrentPage()];
                if (fader.selected) {
                    fader.value += rotaryValue;
                    return true;
                }
            }
        }
    }

    return false;
}

extern "C" void app_main() {
    
    display.init();

    display.update();

    Rotary rotary;
    rotary.begin();


    while (true) {
        int rotaryValue = rotary.getPosition();

        if (rotaryValue != 0){
            
           if (changeFaderValue(rotaryValue)) {
                // Se o valor do fader foi alterado, atualiza o display
                display.update();
            } else {
                if(rotaryValue > 0) {
                    display.nextPage();
                }
    
                if (rotaryValue < 0) {
                    display.previousPage();
                }       
            }

        }
        
        if (rotary.onPress()) {
            
        }

        if (rotary.onShortPress()) {
            if (display.getCurrentScreen() == SCREEN_PRESET_CHANGE) { 
                // Desmarca todos os pedais e muda para a próxima tela
                deselectAllPedals(pedals);
                display.nextScreen();
            } 
            else if (display.getCurrentScreen() == SCREEN_PRESET_EDIT) { 
                // Seleciona o pedal com base na página atual e muda para a próxima tela
                selectPedalByIndex(pedals, display.getCurrentPage());
                display.nextScreen();
            } 
            else if (display.getCurrentScreen() == SCREEN_PEDAL_PARAMS) { 
                // Itera pelos pedais para encontrar o pedal selecionado
                for (auto& pedal : pedals) {
                    if (pedal->selected) {
                       // Verifica se o fader na página atual já está selecionado
                        if (display.getCurrentPage() >= 0 && display.getCurrentPage() < pedal->faders.size()) {
                            auto& fader = pedal->faders[display.getCurrentPage()];
                            if (fader.selected) {
                                // Se já estiver selecionado, desmarca
                                fader.selected = false;
                                printf("Fader '%s' desmarcado.\n", fader.title.c_str());
                            } else {
                                // Se não estiver selecionado, marca
                                selectFaderByIndex(pedal->faders, display.getCurrentPage());
                                printf("Fader '%s' selecionado.\n", fader.title.c_str());
                            }
                        }
                        break;
                    }
                }
        
                // Atualiza o display para refletir as mudanças
                display.update();
            }
        }

        if (rotary.onLongPress()) {
            //printf("Pressionamento longo!\n");
            display.previousScreen();
        }

        if (rotary.onRelease()) {
           
        }


        vTaskDelay(pdMS_TO_TICKS(100));
    }

    

}