#ifndef NOTE_H
#define NOTE_H

#include "app_defs.h"

typedef struct Note {
    u8 note;
    u8 velocity;
    u8 status;
    u8 index;
    u8 midi_channel;
} Note;

#endif