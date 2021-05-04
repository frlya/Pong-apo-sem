#ifndef MENU_H
#define MENU_H

#include "mzapo_parlcd.h"
#include "mzapo_regs.h"
#include "mzapo_phys.h"
#include "colors.h"
#include "text.h"

#define  PONG_TEXT_SCALE 10

enum menuStates {
	BEGIN = 1111, 
	PONG_HEADER_DONE,
	MENU_BUTTONS,
	STARTED
};

typedef struct {
	unsigned char current;
	unsigned char max;
} menuButtons_t;

typedef struct {
	unsigned char x;
	unsigned char y;
	unsigned short w;
	unsigned short h;
	unsigned short colorBack;
	unsigned short colorText;
	char *text;
} button_t;

typedef struct {
    unsigned int ticker;
    char titleState;
    int state;
	unsigned short color;
}menu_t;

extern menu_t menu;

//Prints title screen
void pongText();

void renderMenu();

void updateMenu();

void menuInit();

#endif