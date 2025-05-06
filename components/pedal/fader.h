#ifndef FADER_H
#define FADER_H

#include <vector>
#include <string>

struct fader_t {
    std::string title; // Título do fader
    int value;  
    bool selected;       // Valor do fader
};

class Fader{
    public:
    std::string title; // Título do fader

    Fader(const std::string& title, int value);

    void setValue(int value);
    void up();
    void down();
    void select();
    void unselect();
    bool isSelected();

    private:
    int value{0};
    int minValue{0}; // Valor mínimo do fader
    int maxValue{100}; // Valor máximo do fader
    bool selected{false}; // Indica se o fader está selecionado
};




void deselectAllFaders(std::vector<fader_t>& faders);

void selectFaderByIndex(std::vector<fader_t>& faders, int index);

#endif // FADER_H