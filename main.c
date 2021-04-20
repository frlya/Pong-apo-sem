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

enum gameState{
	READY,
	RUNNING,
	RESULT,
	MENU
};

enum gameState state = RUNNING;

unsigned char *parlcdMemBase;
unsigned short *fb;
struct timespec loopDelay = {.tv_sec = 0, .tv_nsec = 20 * 1000 * 1000};
pads_t pads = {.p1Pos = SCREEN_HEIGHT / 2 - PAD_HEIGHT / 2, .p2Pos = SCREEN_HEIGHT / 2 - PAD_HEIGHT / 2};
ball_t ball = {.x = START_POS_X, .y = START_POS_Y, .xVel = 1, .yVel = 1};

void setup(){
	//Screen data init
	fb = malloc(SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(unsigned short));
  	if(fb == NULL){
		exit(1);
	}

	//LCD screen setup
	parlcdMemBase = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
	if(parlcdMemBase == NULL){
		exit(1);
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
  	loopDelay.tv_nsec = 150 * 1000 * 1000;
}

void render(int state){
	clearScreen(&fb);
	if(state == RUNNING){
		renderBall(&ball, &fb);
		renderPads(&pads, &fb);
		//renderText(state);
		// if(score == max_score){ state = RESULT; }
	}
	else if(state == READY){
		//resetBall(&ball);
		//renderText(state);
	}
	else if(state == RESULT){
		//resetBall(&ball);
		//renderText(state);
	}
	else if(state == MENU){
		//WIP
	}
	renderScreenData(&fb, parlcdMemBase);
}

void update(int state){
	if(state == RUNNING){
		int p1Offset = getPlayerOffset(1);
		int p2Offset = getPlayerOffset(2);
		updatePads(p1Offset, p2Offset);
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
		//WIP
	}
}

int main(int argc, char *argv[]) {
	setup();
	printf("Welcome to Pong!\n");
	while(true){
		// Main program loop
		update(state);
		render(state);
		clock_nanosleep(CLOCK_MONOTONIC, 0, &loopDelay, NULL);
	}

	printf("See you later!\n");
	return 0;
}