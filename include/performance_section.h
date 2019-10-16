#ifndef PERFORMANCE_SECTION_H
#define PERFORMANCE_SECTION_H

#include "app_defs.h"

typedef struct PerformanceSection {
} PerformanceSection;


void performance_section_draw();

void performance_section_handler(u8 index, u8 value);

void performance_section_init();

void performance_section_change_page(u8 index);

#endif