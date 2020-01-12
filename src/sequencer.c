#include "app.h"

u8 counter = 0;
u8 started = 0;

void sequencer_handle_clock() {
    sequencer_draw_tempo_led();

    if (counter % 6 == 0) {
        sequencer_eight();
    }

    if (counter % 24 == 0) { // TODO depends on speed of kind of arp
        sequencer_tick();
        counter = 0;
    }

    counter++;
}

void sequencer_eight() {
    piano_page_handle_arp();
}

void sequencer_tick() {
    display_plot_led(10, 0xFFFFFF);
}


void sequencer_handle_stop() {
    counter = 0;
}

void sequencer_handle_start() {
    counter = 0;
}

void sequencer_draw_tempo_led() {
    if (counter == 2) {
        display_plot_led(10, 0x000000);
    }
}
