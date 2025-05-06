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

Fader::Fader(const std::string& title, int value) : title(title), value(value) {};

void Fader::setValue(int value) {
    if (value < minValue) {
        this->value = minValue;
    } else if (value > maxValue) {
        this->value = maxValue;
    } else {
        this->value = value;
    }
}

void Fader::up() {
    setValue(value + 1);
}

void Fader::down() {
    setValue(value - 1);
}

void Fader::select() {
    selected = true;
}

void Fader::unselect() {
    selected = false;
}

bool Fader::isSelected() {
    return selected;
}
