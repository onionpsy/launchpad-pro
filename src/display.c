#include "display.h"
#include "app_defs.h"

void display_plot_led(u8 index, u16 color) {
    hal_plot_led(
        TYPEPAD,
        index,
        ((color >> 16) & 0xFF),
        ((color >> 8) & 0xFF),
        (color & 0xFF)
    );
}

void display_fill_all(u16 color) {
    for (u8 i = 0; i < 99; ++i) {
        display_plot_led(i, color);
    }    
}
void display_fill_pads(u16 color) {
    for (u8 i = 1; i < 9; ++i) {
        for (u8 j = 1; j < 9; ++j) {
            display_plot_led(j * 10 + i, color);
        }
    }
};
void display_fill_buttons(u16 color) {}

void display_draw_faders(u8 index, u8 *values, u16 color, u16 background_color) {
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
    for (u8 i = 1; i < 9; ++i) {
        display_plot_led(i * 10 + 9, 0x000);
    }

    for (u8 i = 0; i < sizeof(pages->values) / sizeof(pages[0]); ++i) {
        if (pages[i].index == index) {
            display_plot_led(index, MAXLED);
            return i;
        }
    }

    return 0;
}

void display_draw_mutes(u8 index, u8 *mutes, u16 muted_color, u16 unmuted_color) {
    for (u8 i = 1; i < 9; ++i) {
        display_plot_led(
            i + 10,
            mutes[i]? muted_color : unmuted_color
        );
    }
}

void display_draw_piano(u8 index) {
    const u16 black_key = 0x111;
    const u16 white_key = 0x222;
    display_plot_led(82, black_key);
    display_plot_led(83, black_key);
    display_plot_led(85, black_key);
    display_plot_led(86, black_key);
    display_plot_led(87, black_key);
    display_plot_led(71, white_key);
    display_plot_led(72, white_key);
    display_plot_led(73, white_key);
    display_plot_led(74, white_key);
    display_plot_led(75, white_key);
    display_plot_led(76, white_key);
    display_plot_led(77, white_key);
    display_plot_led(78, white_key);
}