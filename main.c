#define _POSIX_C_SOURCE 200112L

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

#include "ball.h"
#include "peripherals.h"
#include "pads.h"

enum gameState{
	READY,
	RUNNING,
	RESULT
};

enum gameState state = RUNNING;

void init(){
	resetBall();
	// set coordinates of pads and ball
	// initialize window
	// sets font
}

void render(int state){
	if(state == RUNNING){
		renderBall();
		renderPads();
		renderText(state);
		// if score == max_score { state = RESULT; }
	}
	else if(state == READY){
		resetBall();
		renderText(state);
	}
	else if(state == RESULT){
		resetBall();
		renderText(state);
	}
}

void update(int state){
	if(state == RUNNING){
		int p1Offset = getPlayerOffset(1);
		int p2Offset = getPlayerOffset(2);
		updatePads(p1Offset, p2Offset);
		updateBall();
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
}

int main(int argc, char *argv[]) {
	
	// Init menu screen

	printf("Welcome to Pong!\n");
	while(true){
		double start = getCurrentTime();
		// Main program loop
		// Get input
		update(state);
		render(state);
	}

	printf("See you later!\n");
	return 0;
}