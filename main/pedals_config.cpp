#include "pedals_config.h"
#include "fader.h"
#include "driver/ledc.h"

extern std::vector<std::shared_ptr<Pedal>> pedals = {
    std::make_shared<Pedal>(Pedal{1, "Morning Glory", {Fader{12, LEDC_CHANNEL_0, "Volume"}, Fader{14, LEDC_CHANNEL_1, "Drive", 50}, Fader{27, LEDC_CHANNEL_2, "Tone", 100}}}), 
    //std::make_shared<Pedal>(Pedal{2, "OCD", {Fader{"Volume"}, Fader{"Drive"}, Fader{"Tone"}}}),
    //std::make_shared<Pedal>(Pedal{3, "1989", {Fader{"Drive"}, Fader{"Cut"}, Fader{"Volume"}}}),
    //std::make_shared<Pedal>(Pedal{4, "Timmy", {Fader{"Drive"}, Fader{"Gain"}, Fader{"Bass"}, Fader{"Treble"}}}),
};