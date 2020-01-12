#include "cc_pad.h"

void cc_pad_handler(CcPad *pad, u8 index, u8 value) {
    if (index != pad->index) {
        return;
    }

    if (value > 0) {
        midi_send(DINMIDI, CC, pad->midi_channel, pad->cc, pad->value);
    }
}

void cc_pad_draw(CcPad *pad) {
    display_plot_led(pad->index, pad->color);
}