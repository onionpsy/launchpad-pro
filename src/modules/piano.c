#include "piano.h"

void piano_handler(Piano *piano, u8 index, u8 value) {
    u8 size = sizeof piano->pads_intervals / sizeof *piano->pads_intervals;
    u8 midi_note = in_array(index - piano->c, piano->pads_intervals, size);

    // 17 = top right pad
    if (index < piano->c || index > piano->c + 17) {
        return;
    }

    if (value > 0) {
        midi_send(DINMIDI, NOTEON, piano->midi_channel, midi_note + (12 * piano->octave), value);
    } else {
        midi_send(DINMIDI, NOTEOFF, piano->midi_channel, midi_note + (12 * piano->octave), 0);
    }
}

void piano_draw(Piano *piano) {
    u8 n_keys = sizeof piano->pads_intervals / sizeof *piano->pads_intervals;
    for (u8 i = 0; i < n_keys; ++i) {
        display_plot_led(piano->c + piano->pads_intervals[i], piano->keys_color);
    }
}