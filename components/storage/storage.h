#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <vector>
#include "preset.h"

class Storage {
public:
    Storage(); // Construtor

    // Métodos para presets
    bool savePreset(const Preset& preset, int index); // Salva um preset específico
    Preset loadPreset(int index); // Carrega um preset específico

private:
    // Métodos auxiliares
    bool writeToStorage(const std::string& key, const std::string& data); // Escreve na memória
    std::string readFromStorage(const std::string& key); // Lê da memória
};

#endif // STORAGE_H