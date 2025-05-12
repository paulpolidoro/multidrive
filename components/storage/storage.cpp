#include "storage.h"
#include "esp_log.h"
#include "esp_littlefs.h"
#include "cJSON.h"
#include "pedal.h"
#include "string.h"

static const char *TAG = "Storage";

bool presetNameIsEmpty(const std::string& str) {
    return str.empty() || str.find_first_not_of(' ') == std::string::npos;
}

Storage& Storage::getInstance() {
    static Storage instance; // Instância única
    return instance;
}

Storage::Storage() {
    // Configuração do LittleFS
    esp_vfs_littlefs_conf_t conf = {
        .base_path = "/littlefs",
        .partition_label = "vfs",
        .format_if_mount_failed = true,
        .dont_mount = false,
    };

    // Monta o sistema de arquivos
    esp_err_t ret = esp_vfs_littlefs_register(&conf);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Erro ao montar o LittleFS (%s)", esp_err_to_name(ret));
    } else {
        ESP_LOGI(TAG, "LittleFS montado com sucesso");
    }
}

Storage::~Storage() {
    esp_vfs_littlefs_unregister("vfs");
}

bool Storage::savePreset(const Preset& preset, int index) {
    // Serializa o preset para JSON
    cJSON *root = cJSON_CreateObject();
    if (!root) {
        ESP_LOGE(TAG, "Erro ao criar objeto JSON");
        return false;
    }

    cJSON_AddNumberToObject(root, "id", preset.getId());
    cJSON_AddStringToObject(root, "name", preset.getName().c_str());

    cJSON *pedalsArray = cJSON_CreateArray();
    for (const auto& row : preset.getPedals()) {
        cJSON *rowArray = cJSON_CreateArray();
        for (const auto& value : row) {
            if (std::holds_alternative<bool>(value)) {
                cJSON_AddItemToArray(rowArray, cJSON_CreateBool(std::get<bool>(value)));
            } else if (std::holds_alternative<int>(value)) {
                cJSON_AddItemToArray(rowArray, cJSON_CreateNumber(std::get<int>(value)));
            }
        }
        cJSON_AddItemToArray(pedalsArray, rowArray);
    }
    cJSON_AddItemToObject(root, "pedals", pedalsArray);

    char *jsonString = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);

    if (!jsonString) {
        ESP_LOGE(TAG, "Erro ao serializar JSON");
        return false;
    }

    std::string key = "/littlefs/preset_" + std::to_string(index) + ".json";

    bool result = writeToStorage(key, jsonString);

    free(jsonString);
    return result;
}

bool Storage::saveCurrent(int index, std::string& name) {
    if(presetNameIsEmpty(name)) {
        name = "PRESET " + std::to_string(index);
    }

    Preset currentPreset;
    currentPreset.setId(index + 1);
    currentPreset.setName(name);

    std::vector<std::vector<std::variant<bool, int>>> pedals;
    for (const auto& pedal : globalPedals) {
        std::vector<std::variant<bool, int>> rowValues;

        rowValues.push_back(pedal->isActived());

        for (const auto& fader : pedal->faders) {
            rowValues.push_back(fader.getValue());
        }

        pedals.push_back(rowValues);
    }
    currentPreset.setPedals(pedals);

    return savePreset(currentPreset, index);
}

Preset Storage::loadPreset(int index) {
    std::string key = "/littlefs/preset_" + std::to_string(index) + ".json";

    std::string data = readFromStorage(key);
    if (data.empty()) {
        ESP_LOGW(TAG, "Preset não encontrado: %s", key.c_str());
        return Preset(); // Retorna um preset vazio
    }

    // Desserializa o JSON
    cJSON *root = cJSON_Parse(data.c_str());
    if (!root) {
        ESP_LOGE(TAG, "Erro ao desserializar JSON");
        return Preset();
    }

    Preset preset;
    cJSON *id = cJSON_GetObjectItem(root, "id");
    cJSON *name = cJSON_GetObjectItem(root, "name");
    cJSON *pedalsArray = cJSON_GetObjectItem(root, "pedals");

    if (cJSON_IsNumber(id)) {
        preset.setId(id->valueint);
    }

    if (cJSON_IsString(name)) {
        preset.setName(name->valuestring);
    }

    if (cJSON_IsArray(pedalsArray)) {
        std::vector<std::vector<std::variant<bool, int>>> pedals;

        cJSON *row;
        cJSON_ArrayForEach(row, pedalsArray) {
            if (cJSON_IsArray(row)) {
                std::vector<std::variant<bool, int>> rowValues;
                cJSON *value;
                cJSON_ArrayForEach(value, row) {
                    if (cJSON_IsBool(value)) {
                        rowValues.push_back(static_cast<bool>(cJSON_IsTrue(value)));
                    } else if (cJSON_IsNumber(value)) {
                        rowValues.push_back(value->valueint);
                    }
                }
                pedals.push_back(rowValues);
            }
        }

        preset.setPedals(pedals);
    }

    cJSON_Delete(root);

    return preset;
}

bool Storage::writeToStorage(const std::string& key, const std::string& data) {
    FILE *file = fopen(key.c_str(), "w");
    if (!file) {
        ESP_LOGE(TAG, "Erro ao abrir o arquivo para escrita: %s", key.c_str());
        return false;
    }

    size_t written = fwrite(data.c_str(), 1, data.size(), file);
    fclose(file);

    if (written != data.size()) {
        ESP_LOGE(TAG, "Erro ao escrever no arquivo: %s", key.c_str());
        return false;
    }

    return true;
}

std::string Storage::readFromStorage(const std::string& key) {
    FILE *file = fopen(key.c_str(), "r");
    if (!file) {
        ESP_LOGE(TAG, "Erro ao abrir o arquivo para leitura: %s", key.c_str());
        return "";
    }

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    rewind(file);

    std::string data(size, '\0');
    fread(&data[0], 1, size, file);
    fclose(file);

    return data;
}