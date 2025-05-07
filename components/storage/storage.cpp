#include "storage.h"
#include <sstream> // Para manipulação de strings

Storage::Storage() {
    // Inicialização da memória, se necessário
}

// Salva um preset específico
bool Storage::savePreset(const Preset& preset, int index) {
    if (index < 0 || index >= MAX_PRESETS) {
        return false; // Índice inválido
    }

    // Serializa o preset para uma string
    std::ostringstream serializedData;
    serializedData << preset.getId() << ";" << preset.getName() << ";";

    for (const auto& pedal : preset.getPedals()) {
        for (const auto& value : pedal) {
            if (std::holds_alternative<bool>(value)) {
                serializedData << (std::get<bool>(value) ? "1" : "0"); // Salva bool como 1 ou 0
            } else if (std::holds_alternative<int>(value)) {
                serializedData << std::get<int>(value); // Salva int como está
            }
            serializedData << ",";
        }
        serializedData.seekp(-1, std::ios_base::end); // Remove a última vírgula
        serializedData << "|"; // Separador entre pedais
    }

    // Escreve os dados na memória
    return writeToStorage("preset_" + std::to_string(index), serializedData.str());
}

// Carrega um preset específico
Preset Storage::loadPreset(int index) {
    if (index < 0 || index >= MAX_PRESETS) {
        return Preset(); // Retorna um preset vazio se o índice for inválido
    }

    // Lê os dados da memória
    std::string data = readFromStorage("preset_" + std::to_string(index));
    if (data.empty()) {
        return Preset(); // Retorna um preset vazio se não houver dados
    }

    // Desserializa os dados para criar um objeto Preset
    std::istringstream serializedData(data);
    std::string idStr, name, pedalData;

    std::getline(serializedData, idStr, ';');
    std::getline(serializedData, name, ';');

    int id = std::stoi(idStr);
    std::vector<std::vector<std::variant<bool, int>>> pedals;

    while (std::getline(serializedData, pedalData, '|')) {
        std::istringstream pedalStream(pedalData);
        std::string value;
        std::vector<std::variant<bool, int>> pedal;

        while (std::getline(pedalStream, value, ',')) {
            if (value == "1" || value == "0") {
                pedal.push_back(value == "1"); // Converte para bool
            } else {
                pedal.push_back(std::stoi(value)); // Converte para int
            }
        }

        pedals.push_back(pedal);
    }

    return Preset(id, name, pedals);
}

// Escreve na memória
bool Storage::writeToStorage(const std::string& key, const std::string& data) {
    // Implemente a lógica para salvar na memória da placa (ex.: EEPROM, SPIFFS, etc.)
    //std::cout << "Salvando na memória: " << key << " -> " << data << std::endl;
    return true;
}

// Lê da memória
std::string Storage::readFromStorage(const std::string& key) {
    // Implemente a lógica para ler da memória da placa
   // std::cout << "Lendo da memória: " << key << std::endl;
    return ""; // Retorne os dados lidos
}