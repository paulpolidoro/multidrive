#ifndef DISPLAY_H
#define DISPLAY_H

#include <driver/i2c_master.h>
#include "fader.h"
extern "C" {
    #include <ssd1306.h>
}

#define FADER_HEIGHT 20

class Display {
public:
    Display();
    ~Display();
    void init();
    void clear();
    void printText(const char* text, int x, int y, bool invert = false);
    void update();
    void addFader(int y, bool select, bool setting, const Fader& fader);
    void scrollVertical(int offset);
    
private:
    i2c_master_bus_handle_t i2c_master_bus;
    i2c_ssd1306_handle_t i2c_ssd1306;
};

#endif // DISPLAY_H
