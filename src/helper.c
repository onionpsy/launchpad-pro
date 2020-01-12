#include "helper.h"

u8 is_pad(u8 index) {
    u8 r = index % 10;
    u8 q = index / 10;
    return (r > 0 && r < 9 && q < 9 && q > 0);
}

u8 is_faders_page(u8 index) {
    return (index == FADER_VOLUME_PAGE
        || index == FADER_FILTER_PAGE
        || index == FADER_REVERB_PAGE
        || index == FADER_DELAY_PAGE
    );
}

u8 is_sample_page(u8 index) {
    return (index % 10 == 9);
}

u8 is_mute_button(u8 index) {
    return (index < 9);
}

u8 in_array(u8 value, u8 arr[], u8 size) {
    for (u8 i = 0; i < size; ++i) {
        if (arr[i] == value) {
            return i;
        }
    }

    return 0;
}

void debug(u8 index) {
    display_plot_led(index, rand()/100);
}