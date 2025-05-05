#include <stdio.h>
#include "display.h"
#include "rotary.h"

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

    Rotary rotary;
    rotary.begin();


    while (true) {
        int rotaryValue = rotary.getPosition();
        
        if (rotaryValue != 0){
           printf("Posição do Encoder: %d\n", rotaryValue);
        }
        

        //if (encoder.isPressed()) {
        //    printf("Botão pressionado!\n");
        //}

        if (rotary.onPress()) {
            printf("Botão pressionado!\n");
        }

        if (rotary.onShortPress()) {
            printf("Pressionamento curto!\n");
        }

        if (rotary.onLongPress()) {
            printf("Pressionamento longo!\n");
        }

        if (rotary.onRelease()) {
            printf("Botão liberado!\n");
        }


        vTaskDelay(pdMS_TO_TICKS(100));
    }

    

}