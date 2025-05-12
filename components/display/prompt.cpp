#include "prompt.h"
#include "font_mono_8.h"
#include <algorithm> 

Prompt::Prompt(){
    // Inicializa o array textValues com -1
    for (int i = 0; i < MAX_CARACTERES; ++i) {
        textValues[i] = -1;
    }

    alphabet_size = sizeof(PROMPT_ALPHABET) / sizeof(PROMPT_ALPHABET[0]);
};

void Prompt::show(std::string title, std::string defaultText) {
    this->title = title;
    char text[MAX_CARACTERES + 1] = {0}; // +1 para o terminador nulo
    int letterW = 8;

    if(!defaultText.empty()){
        setText(defaultText);
    }

    state = true;
    display.clear();
    display.printText(title.c_str(), 0, 0, false);

    // Preenche o array text com os caracteres correspondentes ou '_'
    for (int i = 0; i < MAX_CARACTERES; ++i) { 
        char letter;
        if (textValues[i] > -1) {
            letter = PROMPT_ALPHABET[textValues[i]][0]; // Atualiza o caractere selecionado
        } else {
            letter = '_'; // Preenche com '_'
        }

        display.drawChar(2 + (letterW * i), 22, letter, FontMono8, (selectedField == i));
    }

    text[MAX_CARACTERES] = '\0'; // Garante que a string termine com '\0'

    // Exibe o texto no display
    //display.drawText(2, 22, text, FontMono8); // Exibe o texto
    display.drawText(2 + (letterW * currentField), 34, "*", FontMono8); // Exibe o cursor

    display.printText("CANCEL", 0, 55);
    display.printText("SAVE", 95, 55);

    display.update();
}

std::string Prompt::getText() const{
    char text[MAX_CARACTERES + 1] = {0};

    for (int i = 0; i < MAX_CARACTERES; ++i) { 
        if (textValues[i] > -1) {
            text[i] = PROMPT_ALPHABET[textValues[i]][0]; // Atualiza o caractere selecionado
        }
    }

    text[MAX_CARACTERES] = '\0'; 

    return std::string(text);
}

void Prompt::clear() {
     for (int i = 0; i < MAX_CARACTERES; ++i) {
        textValues[i] = -1;
    }

    currentField = 0;
    selectedField = -1;
}

void Prompt::close(){
    clear();

    state = false;
}

void Prompt::next() {
     if(selectedField > -1) {
        if (textValues[selectedField] == (alphabet_size - 1)) {
            textValues[selectedField] = -1;
        }else{
            textValues[selectedField]++;
        }
    }else{
        if (currentField < MAX_CARACTERES - 1) {
            currentField++;
        } else {
            currentField = MAX_CARACTERES - 1;
        }
    }

    Prompt::update();
}

void Prompt::previous() {
    if(selectedField > -1) {
        if (textValues[selectedField] == -1) {
            textValues[selectedField] = (alphabet_size - 1);
        }else{
            textValues[selectedField]--;
        }
    }else{
        if (currentField > 0) {
            currentField--;
        } else {
            currentField = 0;
        }
    }

    Prompt::update();
}

bool Prompt::isShowing() const {
    return state;
}

void Prompt::update(){
    for (int i = 0; i < MAX_CARACTERES; i++){
        printf("%d, ", textValues[i]);
    }

    printf("\n ");

    show(title);
}

void Prompt::fieldSelect() {
    selectedField = currentField;

    update();
}

void Prompt::fieldUnselect() {
    selectedField = -1;

    update();
}

void Prompt::fieldToggle() {
    if (selectedField > -1) {
        fieldUnselect();
    } else {
        fieldSelect();
    }
}

void Prompt::setText(const std::string text) {
    for (size_t i = 0; i < text.size(); i++) {
        // Converte o caractere para maiúscula, caso seja uma letra minúscula
        char uppercaseC = std::toupper(text[i]);

        // Procura pelo caractere no array PROMPT_ALPHABET
        auto it = std::find_if(std::begin(PROMPT_ALPHABET), std::end(PROMPT_ALPHABET),
                               [uppercaseC](const char* s) { return s[0] == uppercaseC; });

        // Adiciona ao vetor apenas se encontrar um índice válido
        if (it != std::end(PROMPT_ALPHABET)) {
            textValues[i] = std::distance(std::begin(PROMPT_ALPHABET), it);
        }
    }
}
