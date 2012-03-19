#ifndef GB_SCREEN_H
#define GB_SCREEN_H

#include "gb_types.h"

gb_error gb_screen_init();
void gb_screen_draw(const unsigned char *buffer);

#endif
