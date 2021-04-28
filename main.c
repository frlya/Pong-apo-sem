#define _POSIX_C_SOURCE 200112L

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

#include "mzapo_regs.h"
#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "colors.h"
#include "dimensions.h"
#include "peripherals.h"
#include "pads.h"
#include "ball.h"
#include "text.h"
#include "font_types.h"

enum gameState{
	READY = 1,
	RUNNING,
	RESULT,
	MENU
};

enum menuStates {
	BEGIN = 1111, 
	PONG_HEADER_DONE,
	MENU_BUTTONS,
	STARTED
};

int state = MENU;

// Initialization of a screen.
unsigned char *parlcdMemBase;
unsigned short *fb;

// Initialization of a font
font_descriptor_t *fdes; //  Pointer to a font descriptor from font_...c


struct timespec loopDelay = {.tv_sec = 0, .tv_nsec = 20 * 1000 * 1000};
struct timespec pongDelay = {.tv_sec = 0, .tv_nsec = 500000000};
struct timespec readDelay = {.tv_sec = 3, .tv_nsec = 0};

pads_t pads = {.p1Pos = SCREEN_HEIGHT / 2 - PAD_HEIGHT / 2, .p2Pos = SCREEN_HEIGHT / 2 - PAD_HEIGHT / 2, .p1Vel = 1, .p2Vel = -1};
ball_t ball = {.x = START_POS_X, .y = START_POS_Y, .xVel = 1, .yVel = 1};
_Bool stateSwitch = true;


int scale;
int stateOfTheScreen = BEGIN;

// Drafts of functions
//----------------------------------------------------------------------------------
// Big bad function to try some timing.
int pongText() {
	clearScreen(&fb);
	draw_char(0, 0, 'P', COLOR_WHITE, &fb, scale, fdes);
	renderScreenData(&fb, parlcdMemBase);
	clock_nanosleep(CLOCK_MONOTONIC, 0, &pongDelay, NULL);
	draw_char(0+120, 0, 'O', COLOR_WHITE, &fb, scale, fdes);
	renderScreenData(&fb, parlcdMemBase);
	clock_nanosleep(CLOCK_MONOTONIC, 0, &pongDelay, NULL);
	draw_char(0 + 240, 0, 'N', COLOR_WHITE, &fb, scale, fdes);
	renderScreenData(&fb, parlcdMemBase);
	clock_nanosleep(CLOCK_MONOTONIC, 0, &pongDelay, NULL);
	draw_char(0+360, 0, 'G', COLOR_WHITE, &fb, scale, fdes);
	clock_nanosleep(CLOCK_MONOTONIC, 0, &pongDelay, NULL);
	renderScreenData(&fb, parlcdMemBase);

	clock_nanosleep(CLOCK_MONOTONIC, 0, &pongDelay, NULL);
	clock_nanosleep(CLOCK_MONOTONIC, 0, &pongDelay, NULL);

	return PONG_HEADER_DONE;
}


// Drows a string of characters to the screen.
// int x, y 	- left upper corner of a screen.
// char* line   - string to draw.
// scale 		- well... just scale.
// int kerning  - space between two latters.

void drawStringToTheScreen(int x, int y, char* line, int scale, int kerning) {
	int concatinated = 0;
	while (*line != '\0')
	{
		draw_char(x + (concatinated), y, *(line), COLOR_WHITE, &fb, scale, fdes);	
		concatinated += (char_width(*(line), fdes) + kerning ) * scale;
		line++;
	}
	
	
}
//-----------------------------------------------------------------------------

void setup(){
	//Screen data init
	fb = malloc(SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(unsigned short));
  	if(fb == NULL){
		exit(-1);
	}

	//LCD screen setup
	parlcdMemBase = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
	if(parlcdMemBase == NULL){
		exit(-1);
	}
	parlcd_hx8357_init(parlcdMemBase);

	//Clear the screen
	parlcd_write_cmd(parlcdMemBase, 0x2c);
	int ptr = 0;
	unsigned int c;
  	for (int i = 0; i < SCREEN_HEIGHT; i++){
    	for (int j = 0; j < SCREEN_WIDTH; j++){
			c = 0;
      		fb[ptr] = c;
      		parlcd_write_data(parlcdMemBase, fb[ptr++]);
    	}
  	}
	//Loop timer setup
	loopDelay.tv_sec = 0;
  	loopDelay.tv_nsec = 17 * 1000 * 1000;

	//Font is added
	fdes = &font_winFreeSystem14x16;
	scale = 10;
}

void render(int* state){
	clearScreen(&fb);
	if(*state == RUNNING){
		printf("Im running baby!");
		if(stateSwitch){
			stateSwitch = true;
			renderCentralLine(&fb);
		}
		renderBall(&ball, &fb);
		renderPads(&pads, &fb);
		//renderText(state);
		// if(score == max_score){ state = RESULT; }
	}
	else if(*state == READY){
		//resetBall(&ball);
		//renderText(state);
	}
	else if(*state == RESULT){
		//resetBall(&ball);
		//renderText(state);
	}
	else if(*state == MENU){

		if(stateOfTheScreen == BEGIN) {
			stateOfTheScreen = pongText();
		}

		if ( stateOfTheScreen == PONG_HEADER_DONE) {
			drawStringToTheScreen(50, 170, "Hey Mate!", 4, 0);
			drawStringToTheScreen(50, 230, "Wanna play some pong? ;)", 2, 0);
			renderScreenData(&fb, parlcdMemBase);
			clock_nanosleep(CLOCK_MONOTONIC, 0, &readDelay, NULL);
			stateOfTheScreen = MENU_BUTTONS;
		}

		printf("Done!\n");

		if (stateOfTheScreen == MENU_BUTTONS) {
			// print rectangle scale
			stateOfTheScreen = STARTED;
			// print rectangle new game
		}

		// if start is detected -- then game begins
		if( stateOfTheScreen == STARTED){
			*state = RUNNING;
		}
	}
	renderScreenData(&fb, parlcdMemBase);
}

void update(int state){
	if(state == RUNNING){
		int p1Offset = getPlayerOffset(1);
		int p2Offset = getPlayerOffset(2);
		updatePads(&pads, p1Offset, p2Offset);
		updateBall(&ball, &pads);
	}
	else if(state == READY){
		// Get information from knobs to start 
		//WIP

	}
	else if(state == RESULT){
		// Score screen, win_sound, led and rgb animation 
		//WIP
		state = READY;
	}
	else if(state == MENU){
		
	}
}

int main(int argc, char *argv[]) {
	setup();
	printf("Welcome to Pong!\n");
	while(true){
		// Main program loop
		update(state);
		printf("State in main: %i\n", state);
		render(&state);
		clock_nanosleep(CLOCK_MONOTONIC, 0, &loopDelay, NULL);
	}

	printf("See you later!\n");
	return 0;
}