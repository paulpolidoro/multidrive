#ifndef PROMPT_H
#define PROMPT_H

#include "screen.h"
#include <string.h>
#include "esp_timer.h"

#define MAX_CARACTERES 10

constexpr const char* PROMPT_ALPHABET[] {" ", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", \
                                "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", \
                                "X", "Y", "Z", "0", "1", "2", "3", "4", "5", \
                                "6", "7", "8", "9"};

class Prompt {
public:
    Prompt();

    void show(std::string title="", std::string defaultText="");
    void fieldSelect();
    void fieldUnselect();
    void fieldToggle();
    void goToField(int field);
    void next();
    void previous();
    void update();
    void clear();

    bool isShowing() const;

    void close();

    int getCurrentField() const;
    std::string getText() const;
    void setText(const std::string text);

private:
    std::string title;
    int currentField{0};
    int selectedField{0};
    bool state{false};
    int textValues[MAX_CARACTERES] = {-1};
    size_t alphabet_size;
};

#endif // PROMPT_H
