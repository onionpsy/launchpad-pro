#include "sample_page.h"
#include "helper.h"
#include "app_defs.h"
#include "cc_pad.h"

CcPad cc_pads[64];
u8 saved_values[8] = {11};

void sample_page_draw() {
    for (int i = 0; i < 64; ++i) {
        cc_pad_draw(&cc_pads[i]);
    }

    for (u8 i = 0; i < 8; ++i) {
        display_plot_led(saved_values[i], 0xFFFF22);
    }
}

void sample_page_init() {
    u8 y = 0;
    for (u8 i = 1; i < 9; ++i) {
        for (u8 j = 1; j < 9; ++j) {
            cc_pads[y].cc = 19;
            cc_pads[y].midi_channel = i;
            cc_pads[y].color = 0xAAAAAA;
            cc_pads[y].index = j * 10 + i;
            cc_pads[y].value = y + 1;

            ++y;
        }
    }
}

void sample_page_handler(u8 index, u8 value) {
    saved_values[(index - 1) % 10] = index;
    sample_page_draw();
    for (int i = 0; i < 64; ++i) {
        cc_pad_handler(&cc_pads[i], index, value);
    }
}