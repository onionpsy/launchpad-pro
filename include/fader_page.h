#ifndef FADER_PAGE_H
#define FADER_PAGE_H

typedef struct FaderPage {
    int values[10]; // TODO could be -1 if fader_value is between 0 and 8
    int mutes[10]; // TODO
    int index;
    int cc;
    int max_value;

    int backgroud_color;
    int color;

    int muted_color;
    int unmuted_color;
} FaderPage;

#endif