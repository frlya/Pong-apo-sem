#define _POSIX_C_SOURCE 200112L

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

#include "peripherals.h"
#include "dimensions.h"
#include "pads.h"
#include "ball.h"

enum gameState{
	READY,
	RUNNING,
	RESULT,
	MENU
};

enum gameState state = RUNNING;

ball_t ball = {.x = START_POS_X, .y = START_POS_Y, .xVel = 1, .yVel = 1};
pads_t pads = {.p1Pos = SCREEN_HEIGHT / 2 - PAD_HEIGHT / 2, .p2Pos = SCREEN_HEIGHT / 2 - PAD_HEIGHT / 2};

void init(){
	// set coordinates of pads and ball
	// initialize window
	fb = malloc(SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(unsigned short));
	if(fb == NULL){
		exit(-1);
	}
	// sets font
}

void render(int state){
	clearScreen();
	if(state == RUNNING){
		renderBall(&ball, &pads);
		renderPads(&pads);
		//renderText(state);
		// if(score == max_score){ state = RESULT; }
	}
	else if(state == READY){
		resetBall(&ball);
		//renderText(state);
	}
	else if(state == RESULT){
		resetBall(&ball);
		//renderText(state);
	}
	else if(state == MENU){
		//WIP
	}
}

void update(int state){
	if(state == RUNNING){
		int p1Offset = getPlayerOffset(1);
		int p2Offset = getPlayerOffset(2);
		updatePads(p1Offset, p2Offset);
		updateBall(&ball);
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
	
	// Init menu screen
	init();
	printf("Welcome to Pong!\n");
	while(true){
		// Main program loop
		// Get input
		update(state);
		render(state);
	}

	printf("See you later!\n");
	return 0;
}