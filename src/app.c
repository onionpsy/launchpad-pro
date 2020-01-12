/******************************************************************************
 
 Copyright (c) 2015, Focusrite Audio Engineering Ltd.
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 
 * Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.
 
 * Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.
 
 * Neither the name of Focusrite Audio Engineering Ltd., nor the names of its
 contributors may be used to endorse or promote products derived from
 this software without specific prior written permission.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
 *****************************************************************************/

//______________________________________________________________________________
//
// Headers
//______________________________________________________________________________

#include "app.h"

// store ADC frame pointer
static const u16 *g_ADC = 0;

// buffer to store pad states for flash save
#define BUTTON_COUNT 100

FaderSection fader_section;

u8 buttons[BUTTON_COUNT] = {0};

HitPad *hit_pad_buffer[10]; // tmp
u8 buffer_pos = 0;

u8 muted_tracks[8] = {0};

// ----------------------------------------------------------------

void app_sysex_event(u8 port, u8 * data, u16 count) { }

void app_aftertouch_event(u8 index, u8 value) {
    /*switch (current_section) {
        case FADER_SECTION: break; // TODO
        case PERFORMANCE_SECTION: performance_section_aftertouch_handler(index, value); break;
    } */ 
}

void app_surface_event(u8 type, u8 index, u8 value) {
    switch (type)
    {
        case  TYPEPAD:
        {
            if (is_pad(index)) {
                app_pad_event(index, value);
            } else {
                app_button_event(index, value);
            }
        }
        break;
            
        case TYPESETUP:
        {
            if (value)
            {
                // save button states to flash (reload them by power cycling the hardware!)
                //hal_write_flash(0, g_Buttons, BUTTON_COUNT);
            }
        }
        break;
    }
}

// Pads event (11->18 ... 81->88)
void app_pad_event(u8 index, u8 value) {
    
    // TODO clean, switch
    if (is_faders_page(current_page)) {
        fader_section_handler(index, value);
    } else if (current_page == SAMPLE_PAGE) {
        sample_page_handler(index, value);
    } else if (current_page == PIANO_PAGE) {
        piano_page_handler(index, value);
    } 
}

// Button !pads
void app_button_event(u8 index, u8 value) {
    if (value == 0) {
        return;
    }

    // Handle track mutes
    if (is_mute_button(index)) {
        muted_tracks[(index - 1) % 10] = !muted_tracks[(index - 1) % 10];
        display_draw_track_buttons(muted_tracks, 0x00AA00);
        midi_send(DINMIDI, CC, index, 94, muted_tracks[(index - 1) % 10]);
        return;
    }

    display_fill_all(0x000000);
    display_plot_led(index, 0xFFFFFF);
    current_page = index;


    if (is_faders_page(index)) {
        fader_section_change_page(index);
    } else if (index == SAMPLE_PAGE) {
        sample_page_draw();
    } else if (index == PIANO_PAGE) {
        piano_page_draw();
    }
}

void app_midi_event(u8 port, u8 status, u8 d1, u8 d2)
{
    // example - MIDI interface functionality for USB "MIDI" port -> DIN port
    if (port == USBMIDI)
    {
    }
    
    // // example -MIDI interface functionality for DIN -> USB "MIDI" port port
    if (port == DINMIDI)
    {
        hal_send_midi(USBMIDI, status, d1, d2);

        switch (status) {
            case MIDITIMINGCLOCK: sequencer_handle_clock(); break;
            case MIDISTART:
            sequencer_handle_start(); break;
            case MIDISTOP: sequencer_handle_stop(); break;
        }
    }
}

void app_cable_event(u8 type, u8 value)
{
    // example - light the Setup LED to indicate cable connections
    if (type == MIDI_IN_CABLE)
    {
        hal_plot_led(TYPESETUP, 0, 0, 0, 0);
    }
    else if (type == MIDI_OUT_CABLE)
    {
        hal_plot_led(TYPESETUP, 0, 0, value, 0);
    }
}

void app_timer_event()
{
    #define TICK_MS 100
    static int ms = TICK_MS;

    if (++ms >= TICK_MS) {
        ms = 0;
        
        /*midi_send(USBMIDI, CC, pad->midi_channel, pad->cc, pad->value);
        midi_send(USBMIDI, NOTEON, pad->midi_channel, 36, value);*/

        /*for (u8 i = 0; i < 10; ++i) {
            if (!hit_pad_buffer[i]) {
                continue;
            };

            midi_send(
                DINMIDI,
                NOTEON,
                1,
                36,
                100
            );

            hit_pad_buffer[i] = '\0';
            buffer_pos = buffer_pos - 1;

            midi_send(
                DINMIDI,
                NOTEOFF,
                8,
                36,
                100
            );
        }*/
    }
}

void app_init(const u16 *adc_raw)
{
    fader_section_init();  
    sample_page_init();
    piano_page_init();
	
	g_ADC = adc_raw;
}
