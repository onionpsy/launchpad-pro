#ifndef PIANO_H
#define PIANO_H

#include "app_defs.h"

typedef struct Piano {
    u8 c;
    u8 octave;
    u8 midi_channel;
    u8 pads_intervals[14];
    int octave_color;
    int keys_color;
    u8 pressed_notes[4];
    u8 n_pressed_notes;
} Piano;

#endif