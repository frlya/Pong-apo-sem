#ifndef TEXT_H
#define TEXT_H

#include "font_types.h"
#include "peripherals.h"

font_descriptor_t *fdes;    //  Pointer to a font descriptor from font_...c

int char_width(int ch);

void renderText(int state);

void draw_pixel_big(int x, int y, unsigned short color, unsigned short **fb, int scale);

void drawText(int x, int y, char *text);

void draw_char(int x, int y, char ch, unsigned short color, unsigned short **fb, int scale);

#endif