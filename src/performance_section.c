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

ModulationPad pitch_pad;
ModulationPad filter_pad;

void performance_section_draw() {
    piano_draw(&piano);
    modulation_pad_draw(&pitch_pad);
    modulation_pad_draw(&filter_pad);
}

void performance_section_change_page(u8 index) {
}

void performance_section_init() {
    piano.octave = 3;
    piano.c = 61;
    piano.midi_channel = 8;
    piano.keys_color = 0xAAAAAA;

    pitch_pad.color = 0x345723;
    pitch_pad.midi_channel = 8;
    pitch_pad.cc = 16; // Pitch
    pitch_pad.index = 11;
    pitch_pad.value_range[0] = 64;
    pitch_pad.value_range[1] = 84;

    filter_pad.color = 0x748371;
    filter_pad.midi_channel = 8;
    filter_pad.cc = 74;
    filter_pad.index = 12;
    filter_pad.value_range[0] = 127;
    filter_pad.value_range[1] = 50;
}

void performance_section_handler(u8 index, u8 value) {
    piano_handler(&piano, index, value);
    modulation_pad_handler(&pitch_pad, index, value);
    modulation_pad_handler(&filter_pad, index, value);
}

void performance_section_aftertouch_handler(u8 index, u8 value) {
    modulation_pad_aftertouch_handler(&pitch_pad, index, value);
    modulation_pad_aftertouch_handler(&filter_pad, index, value);
}

