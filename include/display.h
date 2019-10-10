#ifndef DISPLAY_H
#define DISPLAY_H

#include "app.h"
#include "fader_page.h"

u8 display_change_page(u8 index, FaderPage *pages);

void display_draw_pad(u8 index, u16 color);

void display_fill_all(u16 color);

void display_fill_pads(u16 color);

void display_fill_buttons(u16 color);

void display_draw_faders(
    u8 index,
    u8 *values,
    u16 color,
    u16 background_color
);
void display_draw_piano(
    u8 index
);

#endif