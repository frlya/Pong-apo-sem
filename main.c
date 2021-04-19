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

void render(int state){
	if(state == RUNNING){
		renderBall();
		renderPads();
		renderText(state);
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
		//WIP
	}
	else if(state == RESULT){
		//WIP
	}
}

int main(int argc, char *argv[]) {
	printf("Welcome to Pong!\n");
	resetBall();
	while(true){
		//Main program loop
		update(state);
		render(state);
	}

	printf("See you later!\n");
	return 0;
}