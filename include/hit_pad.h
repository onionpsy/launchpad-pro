#ifndef HIT_PAD_H
#define HIT_PAD_H

#include "app_defs.h"

typedef struct HitPad {
    u8 index;
    u8 cc;
    u8 midi_channel;
    int color;
} HitPad;

#endif