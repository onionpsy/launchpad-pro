#include "display.h"
#include "app_defs.h"

void display_draw_pad(u8 index, u16 color) {
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
        display_draw_pad(i, color);
    }    
}
void display_fill_pads(u16 color) {
    for (u8 i = 1; i < 9; ++i) {
        for (u8 j = 1; j < 9; ++j) {
            display_draw_pad(j * 10 + i, color);
        }
    }
};
void display_fill_buttons(u16 color) {}

void display_draw_faders(u8 index, u8 *values, u16 color, u16 background_color) {
    for (u8 i = 1; i < 9; ++i) {
        for (u8 j = 2; j < 9; ++j) {
            if (j <= values[i]) {
                display_draw_pad(
                    j * 10 + i,
                    color
                );
            } else {
                display_draw_pad(
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
        hal_plot_led(TYPEPAD, i * 10 + 9, 0, 0, 10);
    }

    hal_plot_led(TYPEPAD, 91, 0, 0, 0);
    for (u8 i = 0; i < sizeof(pages) / sizeof(pages[0]); ++i) {
        if (pages[i].index == index) {
            //fader_section.current_page = &fader_section.pages[i];
            hal_plot_led(TYPEPAD, index, MAXLED, MAXLED, MAXLED);
            return i;
        }
    }

    return 0;
}

void display_draw_mutes(u8 index, u8 *mutes, u16 muted_color, u16 unmuted_color) {
    for (u8 i = 1; i < 9; ++i) {
        display_draw_pad(
            i + 10,
            mutes[i]? muted_color : unmuted_color
        );
    }
}
void display_draw_piano(u8 index) {
    const u16 black_key = 0x111;
    const u16 white_key = 0x222;
    display_draw_pad(82, black_key);
    display_draw_pad(83, black_key);
    display_draw_pad(85, black_key);
    display_draw_pad(86, black_key);
    display_draw_pad(87, black_key);
    display_draw_pad(71, white_key);
    display_draw_pad(72, white_key);
    display_draw_pad(73, white_key);
    display_draw_pad(74, white_key);
    display_draw_pad(75, white_key);
    display_draw_pad(76, white_key);
    display_draw_pad(77, white_key);
    display_draw_pad(78, white_key);
}