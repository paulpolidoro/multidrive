#include <memory>
#include "render.h"
#include "pedal.h"
#include <stdio.h>
#include <math.h>

//extern std::vector<std::shared_ptr<Pedal>> pedals;

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

int renderPresetEdit(Display& display, int page, int beforeScreen, int beforePage) {
    int baseIndex = (page / 3) * 3;
    int maxPedals = baseIndex + 3;

    printf("PAGINA: %d\n", page);

    page = fmin(page, pedals.size() - 1);

    for (size_t i = baseIndex; i < fmin(pedals.size(), maxPedals); ++i) {
        if(page == i){
            display.printRetangle(0, 0 + (18 * i), 127, 18, false);
        }

        display.printText(pedals[i]->name.c_str(), 4, 5 + (18 * i), false);
    }

    return page;
}

int renderPedalParams(Display& display, int page, int beforeScreen, int beforePage) {

    // Encontra o pedal selecionado
    for (const auto& pedal : pedals) {
        if (pedal->selected) {

            printf("PAGINA: %d\n", page);

            page = fmin(page, pedal->faders.size() - 1); // Limita a página ao número de faders disponíveis

            display.printText(pedal->name.c_str(), 0, 0, false);

            // Define a faixa dinâmica para os faders
            int baseIndex = (page / 3) * 3; // Define o início do grupo (0, 3, 6, ...)
            int maxFaders = baseIndex + 3;  // Define o fim do grupo (3, 6, 9, ...)

            for (size_t i = baseIndex; i < fmin(pedal->faders.size(), maxFaders); ++i) {
                display.addFader(10 + (i - baseIndex) * FADER_HEIGHT, (page == i), pedal->faders[i]);
            }

            return page; // Sai da função após encontrar o pedal selecionado
        }
    }

    // Caso nenhum pedal esteja selecionado
    display.printText("Nenhum pedal selecionado", 0, 0, false);
    return 0; // Retorna 0 se nenhum pedal estiver selecionado
}