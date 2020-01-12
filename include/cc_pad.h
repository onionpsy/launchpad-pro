#ifndef CC_PAD_H
#define CC_PAD_H

#include "app_defs.h"

typedef struct CcPad {
    u8 index;
    u8 cc;
    u8 value;
    u8 midi_channel;
    int color;
} CcPad;

#endif