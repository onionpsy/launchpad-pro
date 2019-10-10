#include "fader_section.h"
#include "display.h"

FaderSection fader_section;
u8 page_counter = 0;

void fader_section_change_page(u8 index) {
    display_plot_led(fader_section.current_page->index, fader_section.current_page->color);

    u8 s = sizeof(fader_section.pages) / sizeof(*fader_section.pages);
    for (u8 i = 0; i < sizeof(fader_section.pages) / sizeof(*fader_section.pages); ++i) {
        if (fader_section.pages[i].index == index) {
            display_plot_led(index, 0xFFFFFF);
            fader_section.current_page = &fader_section.pages[i];
            break;
        }
    }

    if (!fader_section.current_page) {
        return;
    }

    display_draw_faders(
        81, 
        fader_section.current_page->values,
        fader_section.current_page->color,
        fader_section.current_page->backgroud_color
    );

    display_draw_mutes(
        11,
        fader_section.current_page->mutes,
        fader_section.current_page->muted_color,
        fader_section.current_page->unmuted_color
    );
}

void fader_section_mutes_handler(u8 index) {
    u8 col = index % 10;


    hal_send_midi(
        DINMIDI,
        CC + col - 1,
        fader_section.current_page->cc,
        fader_section.current_page->mutes[col] * (fader_section.current_page->values[col] - 1) * 15
    );

    fader_section.current_page->mutes[col] = !fader_section.current_page->mutes[col];
}

void fader_section_faders_controller(u8 col, u8 fader_value) {
    fader_section.current_page->values[col] = fader_value;

    for (u8 i = 2; i <= fader_value; ++i) {
        display_plot_led(
            i * 10 + col,
            fader_section.current_page->color
        );
    }

    for (u8 i = 8; i > fader_value; --i) {
        display_plot_led(
            i * 10 + col,
            fader_section.current_page->backgroud_color
        );
    }

    // Only send fader value if not muted
    if (!fader_section.current_page->mutes[col]) {
        hal_send_midi(DINMIDI, CC + col - 1, fader_section.current_page->cc, (fader_value - 1) * 15);
    }
}

void fader_section_mutes_controller(u8 col) {
    display_plot_led(
        10 + col,
        fader_section.current_page->mutes[col]? fader_section.current_page->unmuted_color : fader_section.current_page->muted_color
    );

    hal_send_midi(
        DINMIDI,
        CC + col - 1,
        fader_section.current_page->cc,
        fader_section.current_page->mutes[col] * (fader_section.current_page->values[col] - 1) * 15
    );

    fader_section.current_page->mutes[col] = !fader_section.current_page->mutes[col];
}

void fader_section_faders_handler(u8 index) {
    if (!fader_section.current_page) {
        return;
    }

    u8 col = index % 10;
    u8 fader_value = (index - col) / 10; // range 1->8(?)

    if (fader_value == 1) {
        fader_section_mutes_controller(col);
    } else {
        fader_section_faders_controller(col, fader_value);
    }
}

void fader_section_add_page(u8 index, u8 cc, u8 max_value, int color, int backgroud_color, int muted_color, int unmuted_color) {
    fader_section.pages[page_counter].index = index;
    fader_section.pages[page_counter].cc = cc;
    fader_section.pages[page_counter].max_value = max_value;
    fader_section.pages[page_counter].color = color;
    fader_section.pages[page_counter].backgroud_color = backgroud_color;
    fader_section.pages[page_counter].muted_color = muted_color;
    fader_section.pages[page_counter].unmuted_color = unmuted_color;
    page_counter++;
}

void fader_section_init() {
    fader_section_add_page(89, 95, 127, 0xEE0000, 0x050000, 0x010000, 0xaa9999);
    fader_section_add_page(79, 82, 127, 0x00EE00, 0x000500, 0x000100, 0x99aa99);
    fader_section_add_page(69, 83, 127, 0x0000EE, 0x000005, 0x000001, 0x9999aa);
    page_counter = 0;
}

void fader_section_draw() {
    for (u8 i = 0; i < sizeof(fader_section.pages) / sizeof(*fader_section.pages); ++i) {
        if (fader_section.pages[i].index > 0) {
            display_plot_led(fader_section.pages[i].index, fader_section.pages[i].color);
        }
    }
}