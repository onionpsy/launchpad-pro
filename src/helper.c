#include "helper.h"

u8 is_pad(u8 index) {
    u8 r = index % 10;
    u8 q = index / 10;
    return (r > 0 && r < 9 && q < 9 && q > 0);
}

u8 is_menu_button(u8 index) {
    return (index > 1 && index < 9);
}

u8 is_page_button(u8 index) {
    return (index % 10 == 9);
}

void debug(u8 index) {
    display_plot_led(index, rand()/100);
}