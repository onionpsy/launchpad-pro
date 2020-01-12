#include "piano.h"
#include "note.h"

u8 piano_handler(Piano *piano, u8 index, u8 value, u8 arp) {
    // 17 = top right pad
    if (index < piano->c || index > piano->c + 17) {
        return 0;
    }
    
    u8 size = sizeof piano->pads_intervals / sizeof *piano->pads_intervals;
    u8 interval = in_array(index - piano->c, piano->pads_intervals, size);

    // Interval C is 0 but should still be sent
    if (interval == 0 && index - piano->c != 0) {
        return 0;
    }

    return interval + (12 * piano->octave);
}

void piano_send_note(Piano *piano, u8 note, u8 value) {
    if (note == 0) {
        return;
    }

    midi_send(DINMIDI, NOTEOFF, piano->midi_channel, note, value);
}

void piano_stop_note(Piano *piano, u8 note) {
    midi_send(DINMIDI, NOTEOFF, piano->midi_channel, note, 0);
}

void piano_draw(Piano *piano) {
    u8 n_keys = sizeof piano->pads_intervals / sizeof *piano->pads_intervals;
    for (u8 i = 0; i < n_keys; ++i) {
        display_plot_led(piano->c + piano->pads_intervals[i], piano->keys_color);
    }
}