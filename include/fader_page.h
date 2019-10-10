#ifndef FADER_PAGE_H
#define FADER_PAGE_H

#include "app_defs.h"

typedef struct FaderPage {
    u8 values[10]; // TODO could be -1 if fader_value is between 0 and 8
    u8 mutes[10]; // TODO
    u8 index;
    u8 cc;
    u8 max_value;

    int backgroud_color;
    int color;

    int muted_color;
    int unmuted_color;
} FaderPage;

#endif