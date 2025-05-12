#ifndef DISPLAY_H
#define DISPLAY_H

#include <driver/i2c_master.h>
#include "fader.h"
#include "font.h"

extern "C" {
    #include <ssd1306.h>
}

#define FADER_HEIGHT 18


class Display {
public:
    Display();
    void init();
    void clear();
    void printText(const char* text, int x, int y, bool invert = false);
    void printRetangle(int x, int y, int w, int h, bool fill = false);
    void update();
    void addFader(int y, bool select, const Fader& fader);
    void addOption(int x, int y, const char* text, bool selected);
    void drawChar(int x, int y, char c, const tFont& font, bool invert=false);
    void drawText(int x, int y, const char* text, const tFont& font, bool invert=false);

private:
    i2c_master_bus_handle_t i2c_master_bus;
    i2c_ssd1306_handle_t i2c_ssd1306;
};

#endif // DISPLAY_H
