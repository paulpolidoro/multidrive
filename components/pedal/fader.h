#ifndef FADER_H
#define FADER_H

#include <vector>
#include <string>

struct fader_t {
    std::string title; // Título do fader
    int value;  
    bool selected;       // Valor do fader
};

void deselectAllFaders(std::vector<fader_t>& faders);

void selectFaderByIndex(std::vector<fader_t>& faders, int index);

#endif // FADER_H