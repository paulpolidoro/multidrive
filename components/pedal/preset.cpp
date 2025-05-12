#include "preset.h"
#include "pedal.h"
#include "esp_log.h"

static const char *TAG = "PRESET";

std::vector<Preset> globalPresets(MAX_PRESETS);

std::string presetCode(int presetIndex) {
    if (presetIndex < 0 || presetIndex > MAX_PRESETS) {
        return ""; // Retorna uma string vazia se o índice estiver fora do intervalo
    }

    int group = presetIndex / 4 + 1; // Calcula o grupo (1, 2, etc.)
    char letter = 'A' + (presetIndex % 4); // Calcula a letra (A, B, C, D)

    return std::to_string(group) + letter; // Concatena o grupo e a letra
}

// Construtor padrão
Preset::Preset() : id(0), name(""), pedals({}) {}

// Construtor com ID, nome e pedais
Preset::Preset(int id, const std::string& name, const std::vector<std::vector<std::variant<bool, int>>>& pedals)
    : id(id), name(name), pedals(pedals) {}

// Getters e Setters
int Preset::getId() const { 
    return id; 
}

void Preset::setId(int id) { 
    this->id = id; 
}

std::string Preset::getName() const { 
    return name; 
}

void Preset::setName(const std::string& name) { 
    this->name = name; 
}

std::vector<std::vector<std::variant<bool, int>>> Preset::getPedals() const { 
    return pedals; 
}

void Preset::setPedals(const std::vector<std::vector<std::variant<bool, int>>>& pedals) { 
    this->pedals = pedals; 
}

void Preset::applyToPedals() const {
    if(id == 0) {
        for(size_t i = 0; i < globalPedals.size(); ++i) {
            globalPedals[i]->setActive(false);

            for (size_t j = 0; j < globalPedals[i]->faders.size(); ++j) {
                globalPedals[i]->faders[j].setValue(0);
            }
        }

        return;        
    }

    for (size_t i = 0; i < pedals.size(); ++i) {
        const auto& pedal = pedals[i];
        if (!pedal.empty()) {
            globalPedals[i]->setActive(std::get<bool>(pedal[0]));
          
            for (size_t j = 1; j < pedal.size(); ++j) {
                globalPedals[i]->faders[j - 1].setValue(std::get<int>(pedal[j]));
            }
        }
    }
}