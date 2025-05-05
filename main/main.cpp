#include <stdio.h>
#include "display.h"
#include "encoder.h"

extern "C" void app_main() {
    Display display;
    display.init();
    
    display.clear();
    display.printText("M.Glory 1/2", 0, 0);

    Fader fader1 = {"Volume", 23};
    display.addFader(12, false, false, fader1);

    fader1.title = "Tone";
    fader1.value = 67;
    display.addFader(12 + FADER_HEIGHT, true, false, fader1);

    display.update();

    Encoder encoder;
    encoder.begin();


    while (true) {
        //int encoderValue = encoder.getPosition();
        //if (encoderValue != 0)
        //{
        //    printf("Posição do Encoder: %d\n", encoderValue);

        //}
        

        //if (encoder.isPressed()) {
        //    printf("Botão pressionado!\n");
        //}

        if (encoder.onPress()) {
            printf("Botão pressionado!\n");
        }

        if (encoder.onShortPress()) {
            printf("Pressionamento curto!\n");
        }

        if (encoder.onLongPress()) {
            printf("Pressionamento longo!\n");
        }

        if (encoder.onRelease()) {
            printf("Botão liberado!\n");
        }


        vTaskDelay(pdMS_TO_TICKS(100));
    }

    

}