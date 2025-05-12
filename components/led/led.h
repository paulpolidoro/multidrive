#ifndef LED_H
#define LED_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LED_BYPASS_PIN 32
#define LED_PRESET_PIN 33

class Led;

struct led_blink_params_t {
    Led* led;          // Ponteiro para o objeto Led
    int intervalMs;     // Tempo entre piscadas
    int blinkCount;     // Número de piscadas
    int blinkDurationMs; // Duração total do piscar
};

class Led {
public:
    // Construtor
    explicit Led(int pin);

    // Métodos para controle do LED
    void on();
    void off();
    void toggle();
    bool isOn() const;
    bool isOff() const;

    // Métodos para piscar o LED
    void blink(int intervalMs = 500, int blinkCount = 0, int blinkDurationMs = 0);
    bool isBlink() const;
    void blinkStop();

private:
    int pin; // Pino do LED
    bool state; // Estado atual do LED (true = ligado, false = desligado)
    bool blinking; // Indica se o LED está piscando
    TaskHandle_t blinkTaskHandle; // Handle para a tarefa de piscar o LED
    bool previousState; // Estado anterior ao piscar (true = ligado, false = desligado)

    // Função estática para a tarefa de piscar
    static void blinkTask(void* params);
};

#endif // LED_H