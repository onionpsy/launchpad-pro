#ifndef MODULATION_PAD_H
#define MODULATION_PAD_H

#include "app_defs.h"

typedef struct ModualationPad {
    u8 index;
    u8 cc;
    u8 midi_channel;
    u8 start;
    u8 end;
    int color;
} ModulationPad;

#endif