#ifndef TEXT_H
#define TEXT_H

#define CHAR_HEIGHT 14

#define OFFSET1 8
#define OFFSET2 4

#define COUNTDOWN_PERIOD 60

#include "font_types.h"
#include "peripherals.h"
#include "player_data.h"
#include "games_states.h"

extern font_descriptor_t *fdes; //  Pointer to a font descriptor from font_...c

extern int countdownTimer;
extern int currentCountdownState;

void renderResults();

int stringWidth(char *str);

void renderText(int state);

void updateText(int *state);

void renderScore();

void renderCountdown();

int charWidth(int ch);

void drawPixelBig(int x, int y, uint16_t color, int scale);

void drawText(int x, int y, char *text);

void drawChar(int x, int y, char ch, uint16_t color, int scale);

void drawStringToScreen(int x, int y, char *line, int scale, int kerning, uint16_t color);

int stringWidth(char *str);

void renderPause();

#endif
