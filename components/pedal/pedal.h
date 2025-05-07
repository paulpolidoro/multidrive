#ifndef PEDAL_H
#define PEDAL_H

#include <memory>
#include <string>
#include <vector>
#include "fader.h"

class Pedal {
    public:
    int id;
    std::string name;
    std::vector<Fader> faders;

    Pedal(int id, const std::string& name, const std::vector<Fader>& faders); 

    //Metodos de estados do pedal
    bool isSelected();
    bool isActived();
    void select();
    void unselect();
    void activate();
    void deactivate();
    void setActive(bool active);


    Fader& getFader(int index);
    Fader* getSelectedFader();
    void addFader(const Fader& fader);
    void removeFader(int index);

    void setSelectedFaderValue(int value);
    void upSelectedFader();
    void downSelectedFader();
    bool hasFaderSelected();
    void selectFaderByIndex(int index);
    void unselectAllFaders();
    void toggleSelectFaderByIndex(int index);


    private:
    bool selected {false};
    bool actived {false};
};

extern std::vector<std::shared_ptr<Pedal>> globalPedals;

void deselectAllPedals(std::vector<std::shared_ptr<Pedal>>& pedals);

void selectPedalById(std::vector<std::shared_ptr<Pedal>>& pedals, int id);

void selectPedalByIndex(std::vector<std::shared_ptr<Pedal>>& pedals, int index);

bool changeFaderValueIfSelected(std::vector<std::shared_ptr<Pedal>>& pedals, int value);

#endif // PEDAL_H