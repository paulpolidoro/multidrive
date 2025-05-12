#ifndef SCREEN_H
#define SCREEN_H

#include "display.h"
#include <string.h>
#include "storage.h"
#include "esp_timer.h"



#define SCREEN_PRESET_CHANGE 0
#define SCREEN_PRESET_EDIT 1
#define SCREEN_PEDAL_PARAMS 2

extern Display display;


class Screen {
public:
    Screen(Storage& storage);
    void init();
    void nextScreen();
    void previousScreen();
    void nextPage();
    void previousPage();
    void setCurrentScreen(int screen);
    void setCurrentPage(int page);
    void goToScreen(int screen);
    void goToPage(int page);
    void goToScreenAndPage(int screen, int page);
    void update();
    void handleBackHome();
    int getCurrentScreen() const;
    int getCurrentPage() const;
    int getPageFromScreen(int screen) const;

    void alert(std::string text, int duration=500);
    
    void presetScreen();
    void presetEditScreen();
    void pedalParamsScreen();
private:
    
    int currentScreen{0};
    int currentPages[4]{0, 0, 0, 0};
    Storage& storage;
    int64_t lastUpdateTime{0};
};

#endif // SCREEN_H
