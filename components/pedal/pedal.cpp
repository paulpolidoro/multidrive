#include "pedal.h"

// Lista global de pedais
std::vector<std::shared_ptr<pedal_t>> pedals = {
    std::make_shared<pedal_t>(pedal_t{1, false, "Morning Glory", {fader_t{"Volume", 50, false}, fader_t{"Drive", 75, false}, fader_t{"Tone", 30, false}, fader_t{"Gain", 20, false}}}), 
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

Pedal::Pedal(int id, const std::string& nome, const std::vector<Fader>& faders) : id(id), name(nome), faders(faders) {};

bool Pedal::isSelected(){
    return selected;
}
bool Pedal::isActived(){
    return actived;
}

void Pedal::select(){
    selected = true;
}

void Pedal::unselect(){
    selected = false;
}

void Pedal::activate(){
    actived = true;

}

void Pedal::deactivate(){
    actived = false;    
}

Fader& Pedal::getFader(int index) {
   return faders[index];
}

void Pedal::addFader(const Fader& fader) {
    faders.push_back(fader);
}

void Pedal::removeFader(int index) {
    faders.erase(faders.begin() + index);
}
