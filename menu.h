#ifndef MENU_H
#define MENU_H

#include "mzapo_parlcd.h"
#include "mzapo_regs.h"
#include "mzapo_phys.h"
#include "colors.h"
#include "text.h"

uint8_t previousKnobMenu;
uint8_t currentKnobMenu;

#define PONG_TEXT_SCALE 10
#define PONG_TEXT_ANIMATION_SPEED 8
#define MENU_TEXT_Y_OFFSET 260
#define MENU_TEXT_SCALE_NORMAL 2
#define MENU_TEXT_SCALE_SELECTED 3
#define MENU_TEXT_SPACE 20

	enum menuStates {
		BEGIN = 1111,
		PONG_HEADER_DONE,
		MENU_BUTTONS,
		STARTED,
		SETTINGS
	};

/*typedef struct {
	unsigned short w;
	unsigned short h;
	unsigned short x;
	unsigned short y;
	unsigned short colorBack;
	unsigned short colorText;
	char *text;
} button_t;


typedef struct {
	unsigned char current;
	unsigned char max;
	button_t arr[2];
} menuButtons_t;*/
//=========================================================
/*typedef struct {
	unsigned char current;
	unsigned char max;
	button_t arr[2];
} settings_t;*/

typedef struct {
	unsigned char buttonCooldown;
	unsigned int ticker;
    char titleState;
    int state;
	int pongTextShift;
	unsigned short color;
	int mainIndex;
	//unsigned char settingsIndex;
	char mainItems[3][14];
	int maxMain;
	//char *settingsItems[3];
}menu_t;

extern menu_t menu;

//Prints title screen
void pongText();

void renderMenu();

void updateMenu();

void menuInit(int *st);

void settingsInit();

#endif
