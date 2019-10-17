#ifndef MODULATION_PAD_H
#define MODULATION_PAD_H

#include "app_defs.h"

typedef struct ModualationPad {
    u8 index;
    u8 cc;
    u8 midi_channel;
    int color;
    u8 value_range[2];
} ModulationPad;

void modulation_pad_handler(ModulationPad *pad, u8 index, u8 value);

u8 modulation_pad_calculate_value(u8 value, u8 range1, u8 range2);

void modulation_pad_aftertouch_handler(ModulationPad *pad, u8 index, u8 value);

void modulation_pad_draw(ModulationPad *pad);

#endif