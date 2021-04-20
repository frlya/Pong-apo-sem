#ifndef TEXT_H
#define TEXT_H

#include "font_types.h"
#include "peripherals.h"

font_descriptor_t *fdes;    //  Pointer to a font descriptor from font_...c

int scale;                  //  Scale of a character 

void renderText(int state);

void draw_pixel_big(int x, int y, unsigned short color);

void drawText(int x, int y, char *text);

#endif