#ifndef BALL_H
#define BALL_H

#include "colors.h"
#include "dimensions.h"
#include "mzapo_parlcd.h"
#include "mzapo_regs.h"
#include "pads.h"
#include "peripherals.h"
#include "player_data.h"

#define START_POS_X 240
#define START_POS_Y 270

typedef struct
{
    int x, y;       // Coordinates of the ball
    int xVel, yVel; // Width and height of the ball
    int speed;
    bool left;
} ball_t;

void updateBall(ball_t *ball, pads_t *pads);

void renderBall(ball_t *ball);

char handleCollision(ball_t *ball, pads_t *pads);

void resetBall(ball_t *ball);

#endif