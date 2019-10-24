#include "hit_pad.h"

void hit_pad_handler(HitPad *pad, u8 index, u8 value) {
    if (index != pad->index) {
        return;
    }

    if (value > 0) {
        midi_send(DINMIDI, NOTEON, pad->midi_channel, 36, value);
    } else {
        midi_send(DINMIDI, NOTEOFF, pad->midi_channel, 36, value);
    }
}

void hit_pad_draw(HitPad *pad) {
    display_plot_led(pad->index, pad->color);
}