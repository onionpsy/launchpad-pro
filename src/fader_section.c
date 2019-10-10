#include "fader_section.h"
#include "display.h"

FaderSection fader_section;

void fader_section_change_page(u8 index) {
    u8 i = display_change_page(index, &fader_section.pages);
    fader_section.current_page = fader_section.pages[i];
    display_draw_all_faders
        fader_section.current_page->values,
        fader_section.current_page->color,
        fader_section.current_page->backgroud_color
    );

    display_draw_all_mutes(
        fader_section.current_page->mutes,
        fader_section.current_page->muted_color,
        fader_section.current_page->unmuted_color
    );
}

void mute_per_track_control(u8 index) {
    u8 col = index % 10;

    display_draw_pad(
        10 + col,
        fader_section.current_page->mutes[col]? fader_section.current_page->unmuted_color : fader_section.current_page->muted_color
    );
    //hal_send_midi(DINMIDI, CC + col - 1, 94, fader_section.current_page->enabled[col]);
    hal_send_midi(
        DINMIDI,
        CC + col - 1,
        fader_section.current_page->cc,
        fader_section.current_page->mutes[col] * (fader_section.current_page->values[col] - 1) * 15
    );

    fader_section.current_page->mutes[col] = !fader_section.current_page->mutes[col];

    //fader_section.current_page->enabled[col] * fader_section.current_page->values[col]
}

// Controls
/*void fader_per_track_control(u8 index) {
    if (!fader_section.current_page) {
        return;
    }

    // TODO ignore if fader same value
    //u8 divider = current_page.max_value / 7; // TODO, should be done 1 time

    u8 col = index % 10;
    u8 fader_value = (index - col) / 10; // range 1->8(?)

    fader_section.current_page->values[col] = fader_value;
    for (u8 i = 2; i <= fader_value; ++i) {
        display_draw_pad(
            i * 10 + col,
            fader_section.current_page->color
        );
    }

    for (u8 i = 8; i > fader_value; --i) {
        display_draw_pad(
            i * 10 + col,
            fader_section.current_page->backgroud_color
        );
    }


    //fader_section.current_page->color = fader_value * 5;
    //hal_plot_led(TYPEPAD, 95, fader_section.current_page->values[col], 0, 0);

    // Only send fader value if not muted
    if (!fader_section.current_page->mutes[col]) {
        hal_send_midi(DINMIDI, CC + col - 1, fader_section.current_page->cc, (fader_value - 1) * 15);
    }
}*/


void fader_section_add_page(FaderSection *fader_section, u8 index, u8 cc, u8 max_value, u16 color, u16 backgroud_color, u16 muted_color, u16 unmuted_color) {
    u8 i = sizeof(fader_section) / sizeof(fader_section[0]);
    fader_section->pages[i].index = index;
    fader_section->pages[i].cc = cc;
    fader_section->pages[i].max_value = max_value;
    fader_section->pages[i].color = color;
    fader_section->pages[i].backgroud_color = backgroud_color;
    fader_section->pages[i].muted_color = muted_color;
    fader_section->pages[i].unmuted_color = unmuted_color;
}

void fader_section_init() {
    

    fader_section_add_page(&fader_section, 89, 95, 127, 0xE00, 0x500, 0x211, 0xa99);
    //fader_section_add_page(&fader_section, 79, 82, 127, 0x00EE00, 0x000500, 0x010201, 0x99aa99);

    // Reberv send
    /*fader_section.pages[2].index = 69;
    fader_section.pages[2].cc = 83;
    fader_section.pages[2].max_value = 127;
    fader_section.pages[2].color = 0x0000EE;
    fader_section.pages[2].backgroud_color = 0x000005;
    fader_section.pages[2].muted_color = 0x010102;
    fader_section.pages[2].unmuted_color = 0x9999aa;

    // Filter TODO, get the filter type and change the muted value = 0 OR 127
    fader_section.pages[3].index = 59;
    fader_section.pages[3].cc = 74;
    fader_section.pages[3].max_value = 127;
    fader_section.pages[3].color = 0x00EEEE;
    fader_section.pages[3].backgroud_color = 0x000505;
    fader_section.pages[3].muted_color = 0x010202;
    fader_section.pages[3].unmuted_color = 0x99aaaa;

    // Pitch
    fader_section.pages[4].index = 49;
    fader_section.pages[4].cc = 16;
    fader_section.pages[4].max_value = 24;
    fader_section.pages[4].color = 0xEE00EE;
    fader_section.pages[4].backgroud_color = 0x050005;
    fader_section.pages[4].muted_color = 0x020102;
    fader_section.pages[4].unmuted_color = 0xaa99aa;*/
}

void fader_section_draw() {

}