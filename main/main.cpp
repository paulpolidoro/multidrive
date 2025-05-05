#include <stdio.h>
#include "display.h"
#include "rotary.h"
#include "pedal.h"
#include "render.h"
#include <vector>

extern std::vector<std::shared_ptr<pedal_t>> pedals;

extern "C" void app_main() {
    Display display;
    display.init();

    display.update();

    Rotary rotary;
    rotary.begin();


    while (true) {
        int rotaryValue = rotary.getPosition();

        if (rotaryValue != 0){
            if(rotaryValue > 0) {
                display.nextPage();

                printf("Current Screen: %d, Current Page: %d\n", display.getCurrentScreen(), display.getCurrentPage());
            }

            if (rotaryValue < 0) {
                display.previousPage();
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