#ifndef TEXT_H
#define TEXT_H

#define OFFSET1 92
#define OFFSET2 52 
#define OFFSET3 8
#define OFFSET4 4

#include "font_types.h"
#include "peripherals.h"
#include "player_data.h"
#include "games_states.h"

extern font_descriptor_t *fdes; //  Pointer to a font descriptor from font_...c

void renderResults();

int stringWidth(char *str);

void renderText(int state);

void renderScore();

int charWidth(int ch);

void drawPixelBig(int x, int y, unsigned short color, int scale);

void drawText(int x, int y, char *text);

void drawChar(int x, int y, char ch, unsigned short color, int scale);

void drawStringToTheScreen(int x, int y, char* line, int scale, int kerning, unsigned short color);

#endif
