#include <memory>
#include "render.h"
#include "pedal.h"

void renderPresetChange(Display& display, int page, int beforeScreen, int beforePage) {
    display.printText("Preset Change", 0, 0, false);

    switch (page) {
        case 0:
            display.printText("Page 1: Selecione um preset", 0, 10, false);
            break;
        case 1:
            display.printText("Page 2: Detalhes do preset", 0, 10, false);
            break;
        case 2:
            display.printText("Page 3: Confirmar", 0, 10, false);
            break;
        default:
            display.printText("Page desconhecida", 0, 10, false);
            break;
    }
}

void renderPresetEdit(Display& display, int page, int beforeScreen, int beforePage) {
    // Lista de pedais (pode ser global ou passada como argumento)
    extern std::vector<std::shared_ptr<pedal_t>> pedals;

     // Renderiza os faders do pedal
    for (size_t i = 0; i < pedals.size(); ++i) {
        if(page == i){
            display.printRetangle(0, 0 + (18 * i), 127, 18, false);
        }

        display.printText(pedals[i]->name.c_str(), 4, 5 + (18 * i), false);
    }
}

void renderPedalParams(Display& display, int page, int beforeScreen, int beforePage) {
    // Encontra o pedal selecionado
    for (const auto& pedal : pedals) {
        if (pedal->selected) {

            display.printText(pedal->name.c_str(), 0, 0, false);

            for (size_t i = 0; i < pedal->faders.size(); ++i) {
                display.addFader(10 + i * FADER_HEIGHT, (page == i), pedal->faders[i]);
            }
            return; // Sai da função após encontrar o pedal selecionado
        }
    }

    // Caso nenhum pedal esteja selecionado
    display.printText("Nenhum pedal selecionado", 0, 0, false);
}