#ifndef PRESET_H
#define PRESET_H

#include <string>
#include <vector>
#include <variant> // Necessário para std::variant

#define MAX_PRESETS 8 // Número máximo de presets

// Classe para representar um preset
class Preset {
    public:
        Preset(); // Construtor padrão
        Preset(int id, const std::string& name, const std::vector<std::vector<std::variant<bool, int>>>& pedals);
    
        // Métodos públicos
        int getId() const;
        void setId(int id);
    
        std::string getName() const;
        void setName(const std::string& name);
    
        std::vector<std::vector<std::variant<bool, int>>> getPedals() const;
        void setPedals(const std::vector<std::vector<std::variant<bool, int>>>& pedals);
        void applyToPedals() const;
    
    private:
        int id; // Identificador do preset
        std::string name; // Nome do preset
        std::vector<std::vector<std::variant<bool, int>>> pedals; // Array de arrays com bool e int
    };

// Funções auxiliares relacionadas a presets
std::vector<Preset> loadPresets(); // Carrega presets
void savePresets(const std::vector<Preset>& presets); // Salva presets
std::string presetCode(int index);

extern std::vector<Preset> globalPresets;

#endif // PRESET_H