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

u8 current_section = FADER_SECTION;

// ----------------------------------------------------------------

void app_sysex_event(u8 port, u8 * data, u16 count) { }
void app_aftertouch_event(u8 index, u8 value) { }

void app_surface_event(u8 type, u8 index, u8 value)
{
    // TMP ?
    if (!value) {
        return;
    }

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
    switch (current_section) {
        case FADER_SECTION: fader_section_change_page(index); break;
        case PIANO_SECTION: break;
    }
}

// Button !pads
void app_button_event(u8 index, u8 value) {
    //case is_menu_button(index):;
    if (is_page_button(index)) {
        display_draw_pad(92, rand()/100);
        switch (current_section) {
            case FADER_SECTION: debug(93); fader_section_change_page(index); break;
            case PIANO_SECTION: break;
        }
    }
}

void app_midi_event(u8 port, u8 status, u8 d1, u8 d2)
{
    // example - MIDI interface functionality for USB "MIDI" port -> DIN port
    if (port == USBMIDI)
    {
        hal_send_midi(DINMIDI, status, d1, d2);
    }
    
    // // example -MIDI interface functionality for DIN -> USB "MIDI" port port
    if (port == DINMIDI)
    {
        hal_send_midi(USBMIDI, status, d1, d2);
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
}

void app_init(const u16 *adc_raw)
{
    //display_fill_all(0x83823);

    fader_section_init();   
    //hal_read_device_id();
    //change_section();

    // example - load button states from flash
    //hal_read_flash(0, g_Buttons, BUTTON_COUNT);

    /*hal_plot_led(TYPEPAD, 1, 255, 255, 0);
    hal_plot_led(TYPEPAD, 11, 255, 255, 0);*/

    
    // borders
    /*for (int i=0; i < 10; ++i)
    {
        for (int j=0; j < 10; ++j)
        {
            u8 b = g_Buttons[j*10 + i];
            
            hal_plot_led(TYPEPAD, j*10 + i, 0, 0, b);
        }
    }*/

	
	// store off the raw ADC frame pointer for later use
	g_ADC = adc_raw;
}
