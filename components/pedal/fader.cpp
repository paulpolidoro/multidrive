#include "fader.h"

void deselectAllFaders(std::vector<fader_t>& faders) {
    for (auto& fader : faders) {
        fader.selected = false;
    }
}

void selectFaderByIndex(std::vector<fader_t>& faders, int index) {
    deselectAllFaders(faders);
    if (index >= 0 && index < faders.size()) {
        faders[index].selected = true;
    }
}