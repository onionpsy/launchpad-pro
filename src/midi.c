#include "midi.h"

void midi_send(u8 port, u8 type, u8 channel, u8 data1, u8 data2) {
    hal_send_midi(port, type + channel - 1, data1, data2);
}
