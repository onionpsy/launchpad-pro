#include "modulation_pad.h"

void modulation_pad_handler(ModulationPad *pad, u8 index, u8 velocity) {
    if (index != pad->index) {
        return;
    }
    
    midi_send(DINMIDI, CC, pad->midi_channel, pad->cc, velocity);
}

void modulation_pad_draw(ModulationPad *pad) {
    display_plot_led(pad->index, pad->color);
}