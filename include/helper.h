#ifndef HELPER_H
#define HELPER_H

#include "app_defs.h"

u8 is_pad(u8 index);
u8 is_menu_button(u8 index);
u8 is_page_button(u8 index);
u8 is_section_button(u8 index);
u8 in_array(u8 value, u8 *array, u8 size);

#endif