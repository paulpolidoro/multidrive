#include "pedal.h"

// Lista global de pedais
std::vector<std::shared_ptr<pedal_t>> pedals = {
    std::make_shared<pedal_t>(pedal_t{1, false, "Morning Glory", {fader_t{"Volume", 50, false}, fader_t{"Drive", 75, false}, fader_t{"Tone", 30, false}}}),
    std::make_shared<pedal_t>(pedal_t{2, false, "OCD", {fader_t{"Volume", 60, false}, fader_t{"Drive", 80, false}, fader_t{"Tone", 40, false}}}),
    std::make_shared<pedal_t>(pedal_t{3, false, "1989", {fader_t{"Drive", 70, false}, fader_t{"Cut", 65, false}, fader_t{"Volume", 50, false}}})
};

void deselectAllPedals(std::vector<std::shared_ptr<pedal_t>>& pedals) {
    for (auto& pedal : pedals) {
        pedal->selected = false;
    }
}

void selectPedalById(std::vector<std::shared_ptr<pedal_t>>&  pedals, int id) {
    deselectAllPedals(pedals);
    for (auto& pedal : pedals) {
        if (pedal->id == id) {
            pedal->selected = true;
            break;
        }
    }
}

void selectPedalByIndex(std::vector<std::shared_ptr<pedal_t>>&  pedals, int index) {
    deselectAllPedals(pedals);
    if (index >= 0 && index < pedals.size()) {
        pedals[index]->selected = true;
    }
}