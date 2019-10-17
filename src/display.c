#include "display.h"
#include "app_defs.h"

void display_plot_led(u8 index, int color) {
    hal_plot_led(
        TYPEPAD,
        index,
        ((color >> 16) & 0xFF),
        ((color >> 8) & 0xFF),
        (color & 0xFF)
    );
}

void display_fill_all(int color) {
    for (u8 i = 0; i < 99; ++i) {
        display_plot_led(i, color);
    }    
}
void display_fill_pads(int color) {
    for (u8 i = 1; i < 9; ++i) {
        for (u8 j = 1; j < 9; ++j) {
            display_plot_led(j * 10 + i, color);
        }
    }
};
void display_fill_buttons(int color) {}

void display_draw_faders(u8 index, u8 *values, int color, int background_color) {
    for (u8 i = 1; i < 9; ++i) {
        for (u8 j = 2; j < 9; ++j) {
            if (j <= values[i]) {
                display_plot_led(
                    j * 10 + i,
                    color
                );
            } else {
                display_plot_led(
                    j * 10 + i,
                    background_color
                );
            }
        }
    }
}

u8 display_change_page(u8 index, FaderPage *pages) {

    // Clear pages buttons
    /*for (u8 i = 1; i < 9; ++i) {
        display_plot_led(i * 10 + 9, 0x00009);
    }

    for (u8 i = 0; i < sizeof(pages) / sizeof(*pages); ++i) {
        display_plot_led(11 + i, 0xFFFFFF);
        if (pages[i].index == index) {
            display_plot_led(index, 0x9998877);
            return i;
        }
    }*/

    return 0;
}

void display_draw_mutes(u8 index, u8 *mutes, int muted_color, int unmuted_color) {
    for (u8 i = 1; i < 9; ++i) {
        display_plot_led(
            i + 10,
            mutes[i]? muted_color : unmuted_color
        );
    }
}