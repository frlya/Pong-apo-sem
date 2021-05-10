#ifndef MENU_H
#define MENU_H

#include <stdbool.h>

#include "mzapo_parlcd.h"
#include "mzapo_regs.h"
#include "mzapo_phys.h"
#include "colors.h"
#include "text.h"

uint8_t previousKnobMenu;
uint8_t currentKnobMenu;
unsigned char navigationScaleLeft;
unsigned char navigationScaleRight;
unsigned char navigationScaleCenter;

#define PONG_TEXT_SCALE 10
#define PONG_TEXT_ANIMATION_SPEED 8
#define MENU_TEXT_Y_OFFSET 260
#define MENU_TEXT_SCALE_NORMAL 2
#define MENU_TEXT_SCALE_SELECTED 3
#define MENU_TEXT_CREDITS 5
#define MENU_TEXT_SPACE 20

	enum menuStates {
		BEGIN = 1111,
		PONG_HEADER_DONE,
		MENU_BUTTONS,
		STARTED,
		CREDITS
	};

typedef struct {
	unsigned char buttonCooldown;
	unsigned int ticker;
    char titleState;
    int state;
	int pongTextShift;
	unsigned short color;
	int mainIndex;
	char mainItems[3][14];
	int maxMain;
} menu_t;

extern menu_t menu;

//Prints title screen
void pongText();

void renderMenu();

void updateMenu();

void menuInit(int *st);

void settingsInit();

void handleMenu();

void handlePause(int *state);

#endif
