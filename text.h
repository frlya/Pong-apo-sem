#ifndef TEXT_H
#define TEXT_H

#include "font_types.h"
#include "peripherals.h"

int char_width(int ch, font_descriptor_t *fdes);

void renderText(int state);

void draw_pixel_big(int x, int y, unsigned short color, unsigned short **fb, int scale);

void drawText(int x, int y, char *text);

void draw_char(int x, int y, char ch, unsigned short color, unsigned short **fb, int scale, font_descriptor_t *fdes);

void drawStringToTheScreen(int x, int y, char* line, int scale, int kerning, unsigned short **fb, font_descriptor_t *fdes);

#endif