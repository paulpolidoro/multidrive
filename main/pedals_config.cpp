#include "pedals_config.h"
#include "fader.h"
#include "driver/ledc.h"

extern std::vector<std::shared_ptr<Pedal>> globalPedals = {
    std::make_shared<Pedal>(Pedal{1, "Morning Glory", {Fader{13, LEDC_CHANNEL_0, "Volume"}, Fader{12, LEDC_CHANNEL_1, "Drive"}, Fader{14, LEDC_CHANNEL_2, "Tone"}}}), 
    //std::make_shared<Pedal>(Pedal{2, "OCD", {Fader{"Volume"}, Fader{"Drive"}, Fader{"Tone"}}}),
    std::make_shared<Pedal>(Pedal{2, "1989", {Fader{27, LEDC_CHANNEL_3, "Drive"}, Fader{26, LEDC_CHANNEL_4, "Cut"}, Fader{33, LEDC_CHANNEL_5, "Volume"}}}),
    //std::make_shared<Pedal>(Pedal{4, "Timmy", {Fader{"Drive"}, Fader{"Gain"}, Fader{"Bass"}, Fader{"Treble"}}}),
};