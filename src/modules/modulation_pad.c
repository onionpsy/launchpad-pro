#include "modulation_pad.h"

void modulation_pad_handler(ModulationPad *pad, u8 index, u8 value) {
    if (index != pad->index) {
        return;
    }

    // Reset to default value
    // TODO take value from DT before pressing
    if (value == 0) {
        midi_send(DINMIDI, CC, pad->midi_channel, pad->cc, pad->value_range[0]);
    }
}

u8 modulation_pad_calculate_value(u8 value, u8 range1, u8 range2) { 
    return range1 + (
        value / (1 + (
            127 / (range2 - range1)
        ))
    );
}

void modulation_pad_aftertouch_handler(ModulationPad *pad, u8 index, u8 value) {
    if (index != pad->index) {
        return;
    }

    if (pad->value_range[0] > pad->value_range[1]) {
        value = modulation_pad_calculate_value(
            pad->value_range[0] - value,
            pad->value_range[1],
            pad->value_range[0]
        );
    } else {
        value = modulation_pad_calculate_value(
            value,
            pad->value_range[0],
            pad->value_range[1]
        );
    }

    midi_send(DINMIDI, CC, pad->midi_channel, pad->cc, value);
}

void modulation_pad_draw(ModulationPad *pad) {
    display_plot_led(pad->index, pad->color);
}