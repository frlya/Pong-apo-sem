#include "ball.h"

void updateBall(){
    switch (checkCollision(x, y)){
        case V_COLLISION:
            xVel *= -1;
            //This part will be optimized later
            x += xVel * BASE_SPEED;
            y += xVel * BASE_SPEED;
            break;
        case H_COLLISION:
            yVel *= -1;
            //This part will be optimized later
            x += xVel * BASE_SPEED;
            y += xVel * BASE_SPEED;
            break;
        default:
            x += xVel * BASE_SPEED;
            y += xVel * BASE_SPEED;
            break;
    }
    //WIP
}

void renderBall(){
    //WIP
}

void resetBall(){
    x = START_POS_X;
    y = START_POS_Y;
}