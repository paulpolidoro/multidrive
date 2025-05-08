#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include "preset.h"
#include "esp_littlefs.h"

class Storage {
public:
    static Storage& getInstance(); // Método para obter a única instância

    // Métodos para presets
    bool savePreset(const Preset& preset, int index);
    bool saveCurrent(int index, const std::string& name); // Atualizado para incluir o nome do preset
    Preset loadPreset(int index);

private:
    Storage(); // Construtor privado
    ~Storage(); // Destrutor privado
    Storage(const Storage&) = delete; // Proíbe cópia
    Storage& operator=(const Storage&) = delete; // Proíbe atribuição

    // Métodos auxiliares
    bool writeToStorage(const std::string& key, const std::string& data);
    std::string readFromStorage(const std::string& key);
};

#endif // STORAGE_H