#ifndef MIDI_H
#define MIDI_H

#include "app_defs.h"

void midi_send(u8 port, u8 type, u8 channel, u8 data1, u8 data2);

#endif