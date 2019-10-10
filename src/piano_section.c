
/*void piano_section_control(u8 index, u8 value) {
    u8 octave = 0;
    u8 r, g, b;
    hal_read_led(TYPEPAD, index, &r, &g, &b);
    plot_led(index, 0x635214 * rand()/1000);
    //if (value > 0) {
        hal_send_midi(DINMIDI, NOTEON, 30, value);
    //}

    hal_plot_led(TYPEPAD, index, r, g, b);
}*/