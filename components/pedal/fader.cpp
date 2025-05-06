#include "fader.h"

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

int Fader::getValue() const {
    return value;
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

void Fader::toggleSelect() {
    selected = !selected;
}

bool Fader::isSelected() const {
    return selected;
}

void Fader::addValue(int value) {
    setValue(this->value + value);
}