#include "pedal.h"

void deselectAllPedals(std::vector<std::shared_ptr<Pedal>>& pedals) {
    for (auto& pedal : pedals) {
        pedal->unselectAllFaders();
        pedal->unselect();
    }
}

void selectPedalById(std::vector<std::shared_ptr<Pedal>>&  pedals, int id) {
    deselectAllPedals(pedals);
    for (auto& pedal : pedals) {
        if (pedal->id == id) {
            pedal->select();
            break;
        }
    }
}

void selectPedalByIndex(std::vector<std::shared_ptr<Pedal>>&  pedals, int index) {
    deselectAllPedals(pedals);
    if (index >= 0 && index < pedals.size()) {
        pedals[index]->select();
    }
}

bool changeFaderValueIfSelected(std::vector<std::shared_ptr<Pedal>>&  pedals, int value) {
    for (auto& pedal : pedals) {
        if (pedal->isSelected()) {
            if (pedal->hasFaderSelected()) {
                pedal->getSelectedFader()->addValue(value);

                return true;
            }
            
            break;
        }
    }

    return false;
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

Fader* Pedal::getSelectedFader() {
    for (auto& fader : faders) {
        if (fader.isSelected()) {
            return &fader;
        }
    }

    return nullptr;
}

bool Pedal::hasFaderSelected() {
    for (auto& fader : faders) {
        if (fader.isSelected()) {
            return true;
        }
    }
    return false;
}

void Pedal::addFader(const Fader& fader) {
    faders.push_back(fader);
}

void Pedal::removeFader(int index) {
    faders.erase(faders.begin() + index);
}

void Pedal::setSelectedFaderValue(int value) {
    for (auto& fader : faders) {
        if (fader.isSelected()) {
            fader.setValue(value);
            break;
        }
    }
}

void Pedal::upSelectedFader() {
    for (auto& fader : faders) {
        if (fader.isSelected()) {
            fader.up();
            break;
        }
    }
}

void Pedal::downSelectedFader() {
    for (auto& fader : faders) {
        if (fader.isSelected()) {
            fader.down();
            break;
        }
    }
}

void Pedal::selectFaderByIndex(int index) {
    unselectAllFaders();

    if (index >= 0 && index < faders.size()) {
        faders[index].select();
    }
}

void Pedal::unselectAllFaders() {
    for (auto& fader : faders) {
        fader.unselect();
    }
}

void Pedal::toggleSelectFaderByIndex(int index) {
    if (index >= 0 && index < faders.size()) {
        faders[index].toggleSelect();
    }
}