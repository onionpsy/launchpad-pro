#include "piano.h"
#include "helper.h"
#include "hit_pad.h"
#include "modulation_pad.h"
#include "app_defs.h"
#include "cc_pad.h"
#include "note.h"
#include "app.h"

u8 intervals[] = {0, 11, 1, 12, 2, 3, 14, 4, 15, 5, 16, 6, 7};
Piano pianos[4];

u8 n_notes = 0;
Note notes[8] = {
    0,
    0,
    NOTEOFF,
    0,
    8   // midi channel
};
u8 arp_counter = 0;
u8 clear_arp_index = 81;
u8 clear_arp_color = 0xAA0000;

void piano_page_draw() {
    for (u8 i = 0; i < 4; ++i) {
        piano_draw(&pianos[i]);
    }

    for (u8 i = 0; i < sizeof pianos / sizeof *pianos; ++i) {
        if (notes[i].note > 0) {
            display_plot_led(notes[i].index, 0x005500);
        }
    }

    display_plot_led(clear_arp_index, clear_arp_color);

}

void piano_page_clear_arp() {
    for (u8 i = 0; i < sizeof pianos / sizeof *pianos; ++i) {
        notes[i].note = 0;
    }
}

void piano_page_init() {

    pianos[0].octave = 3;
    pianos[0].c = 71;
    pianos[0].midi_channel = 8;
    pianos[0].keys_color = 0xAAAAAA;
    memcpy(pianos[0].pads_intervals, intervals, sizeof(intervals));

    pianos[1].octave = 2;
    pianos[1].c = 51;
    pianos[1].midi_channel = 8;
    pianos[1].keys_color = 0xAAAAAA;
    memcpy(pianos[1].pads_intervals, intervals, sizeof(intervals));

    pianos[2].octave = 1;
    pianos[2].c = 31;
    pianos[2].midi_channel = 8;
    pianos[2].keys_color = 0xAAAAAA;
    memcpy(pianos[2].pads_intervals, intervals, sizeof(intervals));

    pianos[3].octave = 0;
    pianos[3].c = 11;
    pianos[3].midi_channel = 8;
    pianos[3].keys_color = 0xAAAAAA;
    memcpy(pianos[3].pads_intervals, intervals, sizeof(intervals));

}

void piano_page_handler(u8 index, u8 value) {
    if (index == clear_arp_index) {
        piano_page_clear_arp();
    }

    // TODO being able to assign velocity to a midi cc
    // And aftertouch to another (same for arp)
    u8 midi_note = 0;
    for (u8 i = 0; i < sizeof pianos / sizeof *pianos; ++i) {
        midi_note = piano_handler(&pianos[i], index, value);
        if (midi_note == 0) {
            continue;
        }

        debug(20);

        if (value > 0) {
            piano_page_press_note(index, midi_note, value);
        }
    }
}

void piano_page_handle_arp() {
    if (notes[arp_counter].note > 0) {
        midi_send(
            DINMIDI,
            NOTEON,
            8,
            notes[arp_counter].note,
            10 + notes[arp_counter].velocity >> 2
        );

        // TODO plot if current page
        // display_plot_led(notes[arp_counter].index, 0xAAAA00);
    }

    if (arp_counter >= n_notes - 1) {
        arp_counter = 0;
        return;
    }

    arp_counter++;
}

void piano_page_remove_note(u8 i) {
    // Shift all existing notes
    // TODO reduce complexity ?
    for (u8 j = i; j < (sizeof notes / sizeof *notes) - 1; ++j) {
        notes[j] = notes[j + 1]; 
    }
}

void piano_page_press_note(u8 index, u8 midi_note, u8 value) {

    // Clear notes
    for (u8 i = 0; i < sizeof notes / sizeof *notes; ++i) {

        // Notoff existing note if clicked on it
        if (notes[i].index == index && notes[i].note > 0) {
            midi_send(
                DINMIDI,
                NOTEOFF,
                8,
                notes[arp_counter].note,
                0
            );

            notes[i].note = 0;
            n_notes--;

            display_plot_led(notes[i].index, 0xAAAAAA);

            piano_page_remove_note(i);

            return;
        }
    }

    for (u8 i = 0; i < sizeof notes / sizeof *notes; ++i) {
        if (notes[i].note == 0) {
            notes[i].index = index;
            notes[i].note = midi_note;
            notes[i].velocity = value;

            display_plot_led(notes[i].index, 0x005500);

            n_notes++;
            return;
        }
    }
}

void piano_page_unpress_note(u8 index, u8 midi_note, u8 value) {
    for (u8 i = 0; i < sizeof notes / sizeof *notes; ++i) {
        if (notes[i].index == index) {

            // instantly send noteoff
            midi_send(
                DINMIDI,
                NOTEOFF,
                8,
                notes[arp_counter].note,
                0
            );

            n_notes--;
        }
    }
}