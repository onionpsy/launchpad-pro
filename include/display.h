#ifndef DISPLAY_H
#define DISPLAY_H

#include "app.h"
#include "fader_page.h"

void display_plot_led(u8 index, int color);

void display_fill_all(int color);

void display_fill_pads(int color);

void display_fill_buttons(int color);

void display_draw_faders(
    u8 index,
    u8 *values,
    int color,
    int background_color
);

void display_draw_mutes(
    u8 index,
    u8 *mutes,
    int muted_color,
    int color
);

void display_draw_piano(u8 index);

#endif