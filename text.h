#ifndef TEXT_H
#define TEXT_H

#include "font_types.h"
#include "peripherals.h"

extern font_descriptor_t *fdes; //  Pointer to a font descriptor from font_...c

void renderText(int state);

int charWidth(int ch);

void drawPixelBig(int x, int y, unsigned short color, int scale);

void drawText(int x, int y, char *text);

void drawChar(int x, int y, char ch, unsigned short color, int scale);

void drawStringToTheScreen(int x, int y, char* line, int scale, int kerning);

#endif