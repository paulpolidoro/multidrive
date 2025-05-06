#ifndef PEDAL_H
#define PEDAL_H

#include <memory>
#include <string>
#include <vector>
#include "fader.h"

struct pedal_t {
    int id; // Identificador único do pedal
    bool selected; // Indica se o pedal está selecionado
    std::string name; // Nome do pedal
    std::vector<fader_t> faders; // Vetor dinâmico de faders
};

class Pedal {
    public:
    int id;
    std::string name;
    std::vector<Fader> faders;

    Pedal(int id, const std::string& name, const std::vector<Fader>& faders); 

    bool isSelected();
    bool isActived();
    void select();
    void unselect();
    void activate();
    void deactivate();
    Fader& getFader(int index);
    void addFader(const Fader& fader);
    void removeFader(int index);

    private:
    bool selected {false};
    bool actived {false};
};

extern std::vector<std::shared_ptr<Pedal>> pedals;

void deselectAllPedals(std::vector<std::shared_ptr<pedal_t>>& pedals);

void selectPedalById(std::vector<std::shared_ptr<pedal_t>>& pedals, int id);

void selectPedalByIndex(std::vector<std::shared_ptr<pedal_t>>& pedals, int index);

#endif // PEDAL_H