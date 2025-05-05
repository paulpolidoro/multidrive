#ifndef DISPLAY_H
#define DISPLAY_H

#include <driver/i2c_master.h>
#include "fader.h"
extern "C" {
    #include <ssd1306.h>
}

#define FADER_HEIGHT 18


class Display {
public:
    Display();
    ~Display();
    void init();
    void clear();
    void printText(const char* text, int x, int y, bool invert = false);
    void printRetangle(int x, int y, int w, int h, bool fill = false);
    void update();
    void addFader(int y, bool select, const fader_t& fader);

    // Métodos para navegação
    void nextScreen();
    void previousScreen();
    void nextPage();
    void previousPage();

    // Métodos para obter a Screen e Page atuais
    int getCurrentScreen() const;
    int getCurrentPage() const;

private:
    i2c_master_bus_handle_t i2c_master_bus;
    i2c_ssd1306_handle_t i2c_ssd1306;

    // Atributos para rastrear Screen e Page
    int currentScreen; // Índice da Screen atual
    int currentPage;   // Índice da Page atual dentro da Screen
    int totalScreens;  // Total de Screens
    int totalPages;    // Total de Pages na Screen atual
    int beforeScreen; // Índice da Screen anterior
    int beforePage;   // Índice da Page anterior dentro da Screen
};

#endif // DISPLAY_H
