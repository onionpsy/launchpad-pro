#include "performance_section.h"
#include "piano.h"
#include "helper.h"
#include "modulation_pad.h"
#include "app_defs.h"

Piano piano = {
    0,
    0, 
    0,
    {0, 11, 1, 12, 2, 3, 14, 4, 15, 5, 16, 6, 7}
};

ModulationPad test_pad = {};


void performance_section_draw() {
    piano_draw(&piano);
    modulation_pad_draw(&test_pad);
}

void performance_section_change_page(u8 index) {
}

void performance_section_init() {
    piano.octave = 3;
    piano.c = 61;
    piano.midi_channel = 8;
    piano.keys_color = 0xAAAAAA;

    test_pad.color = 0x345723;
    test_pad.midi_channel = 8;
    test_pad.cc = 16; // Pitch
    test_pad.index = 11;
}

void performance_section_handler(u8 index, u8 value) {
    piano_handler(&piano, index, value);
    modulation_pad_handler(&test_pad, index, value);
}

