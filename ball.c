#include "ball.h"

void updateBall(ball_t *ball, pads_t *pads){
    switch (checkCollision(ball->x, ball->y, pads)){
        case V_COLLISION:
            ball->xVel *= -1;
            //This part will be optimized later
            ball->y += ball->xVel * BASE_SPEED;
            break;
        case H_COLLISION:
            ball->yVel *= -1;
            //This part will be optimized later
            ball->x += ball->xVel * BASE_SPEED;
            break;
        case VH_COLLISION:
            ball->xVel *= -1;
            ball->yVel *= -1;
            
            break;
        default:
            ball->x += ball->xVel * BASE_SPEED;
            ball->y += ball->xVel * BASE_SPEED;
            break;
    }
    //WIP
}

void renderBall(ball_t *ball, unsigned short **fb){
    fillRect(ball->x, ball->y, BALL_SIZE, BALL_SIZE, COLOR_WHITE, fb);
}

void resetBall(ball_t *ball){
    ball->x = START_POS_X;
    ball->y = START_POS_Y;
}