#include "ball.h"

void updateBall(ball_t *ball, pads_t *pads){
    switch (handleCollision(ball, pads)){
        case V_COLLISION:
            ball->xVel *= -1;
            //x position is udpated in the handleCollision function
            ball->y += ball->yVel * BALL_SPEED;
            break;
        case H_COLLISION:
            ball->yVel *= -1;
            //y position is udpated in the handleCollision function
            ball->x += ball->xVel * BALL_SPEED;
            break;
        case VH_COLLISION:
            ball->xVel *= -1;
            ball->yVel *= -1;
            //position is udpated in the handleCollision function
            break;
        case L_EXIT:
            updateScore(2, 1);
            resetBall(ball);
            //WIP
            break;
        case R_EXIT:
            updateScore(1, 1);
            resetBall(ball);
            //WIP
            break;
        default:
            ball->x += ball->xVel * BALL_SPEED;
            ball->y += ball->yVel * BALL_SPEED;
            break;
    }
    //WIP
}

void renderBall(ball_t *ball){
    fillRect(ball->x, ball->y, BALL_SIZE, BALL_SIZE, COLOR_WHITE);
}

void resetBall(ball_t *ball){
    ball->x = START_POS_X;
    ball->y = START_POS_Y;
}

char handleCollision(ball_t *ball, pads_t *pads){
    char retValue = NO_COLLISION;
    if((ball->x < PAD_X_OFFSET + PAD_WIDTH - BALL_SPEED * ball->xVel)
            && (ball->y > pads->p1Pos - BALL_SIZE - BALL_SPEED)
            && (ball->y < pads->p1Pos + PAD_HEIGHT + BALL_SIZE + BALL_SPEED)){
        //Ball collides with the left pad
        ball->x = 2 * (BALL_SPEED + PAD_WIDTH) + BALL_SPEED - ball->x;
        retValue = V_COLLISION;
    }
    else if((ball->x > SCREEN_WIDTH - PAD_X_OFFSET - PAD_WIDTH - BALL_SIZE  + BALL_SPEED * ball->xVel)
            && (ball->y > pads->p2Pos - BALL_SIZE - BALL_SPEED)
            && (ball->y < pads->p2Pos + PAD_HEIGHT + BALL_SIZE + BALL_SPEED)){
        //Ball collides with the right pad
        int w = SCREEN_WIDTH - PAD_X_OFFSET - PAD_WIDTH;
        ball->x = 2 * (w - BALL_SIZE) - BALL_SPEED - ball->x;
        retValue = V_COLLISION;
    }
    else if(ball->x < BALL_SIZE){
        //Ball reaches the left edge of the screen
        return L_EXIT;
    }
    else if(ball->x > SCREEN_WIDTH - BALL_SIZE){
        //Ball reaches the right edge of the screen
        return R_EXIT;
    }
    if(ball->y < - BALL_SPEED * ball->yVel){
        //Ball reaches the top of the screen
        ball->y = BALL_SPEED - ball->y;
        if(retValue == V_COLLISION){
            retValue = VH_COLLISION;
        }
        else{
            retValue = H_COLLISION;
        }
    }
    else if(ball->y > SCREEN_HEIGHT - BALL_SIZE + BALL_SPEED * ball->yVel){
        //Ball reaches the bottom of the screen
        ball->y = 2 * (SCREEN_HEIGHT - BALL_SIZE) - ball->y;
        if(retValue == V_COLLISION){
            retValue = VH_COLLISION;
        }
        else{
            retValue = H_COLLISION;
        }
    }
    return retValue;
}
