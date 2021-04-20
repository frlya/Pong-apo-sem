#ifndef BALL_H
#define BALL_H

#include "colors.h"
#include "dimensions.h"
#include "mzapo_parlcd.h"
#include "mzapo_regs.h"
#include "pads.h"
#include "peripherals.h"

#define START_POS_X 300
#define START_POS_Y 200
#define BASE_SPEED 4 //Defined as pixels per frame

typedef struct {
    int x, y;       // Coordinates of the ball
    int xVel, yVel; // Width and height of the ball
} ball_t;

void updateBall(ball_t *ball, pads_t *pads);

void renderBall(ball_t *ball, unsigned short **fb);

void resetBall();

#endif