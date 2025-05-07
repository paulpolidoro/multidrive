#ifndef SCREEN_H
#define SCREEN_H

#include "display.h"
#include <string.h>

#define SCREEN_PRESET_CHANGE 0
#define SCREEN_PRESET_EDIT 1
#define SCREEN_PEDAL_PARAMS 2

class Screen {
public:
    Screen();

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
    int getCurrentScreen() const;
    int getCurrentPage() const;
    
    void presetScreen();
    void presetEditScreen();
    void pedalParamsScreen();

private:
    Display display;
    int currentScreen{0};
    int currentPages[3]{0, 0, 0};
};

#endif // SCREEN_H
