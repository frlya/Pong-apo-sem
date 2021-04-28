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

typedef struct{
    unsigned int ticker;
    char titleState;
    int state;
}menu_t;

//Prints title screen
void pongText(unsigned short **fb, font_descriptor_t *fdes, menu_t *menu);

void renderMenu(unsigned short **fb, font_descriptor_t *fdes, menu_t *menu);

void updateMenu(menu_t *menu);

void menuInit(menu_t *menu);

#endif