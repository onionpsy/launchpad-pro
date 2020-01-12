#ifndef FADER_SECTION_H
#define FADER_SECTION_H

#include "app_defs.h"
#include "display.h"
#include "fader_page.h"

typedef struct FaderSection {
    u8 enabled[8];
    FaderPage pages[9]; // Subpage for each param
    FaderPage *current_page;
} FaderSection;

void fader_section_change_page(u8 index);

void fader_section_faders_controller(u8 col, u8 fader_value);

void fader_section_mutes_controller(u8 col);

void fader_section_handler(u8 index, u8 value);

void fader_section_add_page(
    u8 index,
    u8 cc,
    u8 max_value,
    int color,
    int backgroud_color,
    int muted_color,
    int unmuted_color
);

void fader_section_init();

void fader_section_draw();

#endif