#ifndef SAMPLE_PAGE_H
#define SAMPLE_PAGE_H

#include "app_defs.h"

typedef struct SamplePage {
} SamplePage;

void sample_page_draw();

void sample_page_handler(u8 index, u8 value);

void sample_page_init();

#endif