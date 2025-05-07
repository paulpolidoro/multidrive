#include "screen.h"
#include <math.h>
#include <memory>
#include "pedal.h"
#include "preset.h"
#include "font_display.h"
#include "font_mono_8.h"
#include "font_mono_5.h"

Screen::Screen() {}

void Screen::init() {
    display.init();
}

void Screen::presetScreen() {
    if(getCurrentPage() > MAX_PRESETS - 1) {
        setCurrentPage(MAX_PRESETS - 1);
    }else{
        globalPresets[getCurrentPage()].applyToPedals();
    }

    display.printText(globalPresets[getCurrentPage()].getName().c_str(), 0, 0, false);

    std::string presetCodeStr = presetCode(getCurrentPage());

    int x = (128 - (32 * 2)) / 2;

    if(getCurrentPage() < 4) {
        x = (128 - (24 + 32)) / 2;
    }

    display.drawText(x, 10, presetCodeStr.c_str(), FontDisplay);
    display.update();
}

void Screen::presetEditScreen() {
    setCurrentPage(fmin(getCurrentPage(), globalPedals.size() - 1));  

    int baseIndex = (getCurrentPage() / 3) * 3;
    int maxPedalsPage = baseIndex + 3;

    for (size_t i = baseIndex; i < fmin(globalPedals.size(), maxPedalsPage); ++i) {
        display.addOption(0, 0 + (18 * (i - baseIndex)), globalPedals[i]->name.c_str(), (getCurrentPage() == i));
    }
}

void Screen::pedalParamsScreen() {
    for (const auto& pedal : globalPedals) {
        if (pedal->isSelected()) {
            setCurrentPage(fmin(getCurrentPage(), pedal->faders.size() - 1));

            display.printText(pedal->name.c_str(), 0, 0, false);

            int baseIndex = (getCurrentPage() / 3) * 3;
            int maxFadersPage = baseIndex + 3;

            for (size_t i = baseIndex; i < fmin(pedal->faders.size(), maxFadersPage); ++i) {
                display.addFader(10 + (i - baseIndex) * FADER_HEIGHT, (getCurrentPage() == i), pedal->getFader(i));
            }
        }
    }
}

void Screen::nextScreen() {
    currentScreen++;
    currentPages[currentScreen] = 0;

    update();
}

void Screen::previousScreen() {
    if (currentScreen > 0) {
        currentScreen--; 
    }

    update();
}

void Screen::nextPage() {
    currentPages[currentScreen]++;
    update();
}

void Screen::previousPage() {
    if (currentPages[currentScreen] > 0) {
        currentPages[currentScreen]--;
    }

    update();
}

void Screen::goToScreen(int screen) {
    setCurrentScreen(screen);
    setCurrentPage(0);
    update();
}

void Screen::goToPage(int page) {
    setCurrentPage(page);
    update();
}

void Screen::goToScreenAndPage(int screen, int page) {
    setCurrentScreen(screen);
    setCurrentPage(page);
    update();
}

void Screen::setCurrentScreen(int screen) {
    currentScreen = screen;
}

void Screen::setCurrentPage(int page) {
    currentPages[currentScreen] = page;
}

int Screen::getCurrentScreen() const {
    return currentScreen;
}

int Screen::getCurrentPage() const {
    return currentPages[currentScreen];
}

void Screen::update() {
    display.clear(); 

    switch (currentScreen)
    {
    case 0:
        presetScreen();
        break;
    case 1:
        presetEditScreen();
        break;
    case 2:
        pedalParamsScreen();
        break;
    default:
        break;
    }

    display.update();
}
