#include "ball.h"

void updateBall(ball_t *ball, pads_t *pads){
    if(ball->left) ball->left = false;
    switch (handleCollision(ball, pads)){
        case V_COLLISION:
            ball->xVel *= -1;
            //x position is udpated in the handleCollision function
            ball->y += ball->yVel * ball->speed;
            ball->speed++;
            break;
        case H_COLLISION:
            ball->yVel *= -1;
            //y position is udpated in the handleCollision function
            ball->x += ball->xVel * ball->speed;
            break;
        case VH_COLLISION:
            ball->xVel *= -1;
            ball->yVel *= -1;
            ball->speed++;
            //position is udpated in the handleCollision function
            break;
        case L_EXIT:
            updateScore(2, 1);
            ball->left = true;
            break;
        case R_EXIT:
            updateScore(1, 1);
            ball->left = true;
            break;
        default:
            ball->x += ball->xVel * ball->speed;
            ball->y += ball->yVel * ball->speed;
            break;
    }
    if(ball->left) resetBall(ball);
}

void renderBall(ball_t *ball){
    fillRect(ball->x, ball->y, BALL_SIZE, BALL_SIZE, COLOR_WHITE);
}

void resetBall(ball_t *ball){
    ball->x = START_POS_X;
    ball->y = START_POS_Y;
    ball->speed = BASE_BALL_SPEED;
}

char handleCollision(ball_t *ball, pads_t *pads){
    char retValue = NO_COLLISION;
    int xCheck = 0;
    int yCheck = 0;
    for(int i = 0; i < ball->speed; i++){
        if(ball->xVel == 1){
            xCheck = ball->x + BALL_SIZE + i;
        }
        else{
            xCheck = ball->x - i;
        }
        if(ball->yVel == 1){
            yCheck = ball->y + BALL_SIZE + i;
        }
        else{
            yCheck = ball->y - i;
        }

        if(
            yCheck >= pads->p1Pos
            && yCheck < pads->p1Pos + PAD_HEIGHT
            && xCheck < PAD_X_OFFSET + PAD_WIDTH
        ){
            ledPulse(0b111, 1);
            retValue = V_COLLISION;
            ball->x = PAD_X_OFFSET + PAD_WIDTH + ball->speed - i;
        }
        else if(
            yCheck >= pads->p2Pos
            && yCheck < pads->p2Pos + PAD_HEIGHT
            && xCheck >= SCREEN_WIDTH - PAD_X_OFFSET - PAD_WIDTH
        ){
            ledPulse(0b111, 2);
            retValue = V_COLLISION;
            ball->x = SCREEN_WIDTH - PAD_X_OFFSET - PAD_WIDTH - BALL_SIZE - ball->speed + i;
        }
        else if(xCheck < 0){
            retValue = L_EXIT;
            ledPulse(0b001, 1);
            break;
        }
        else if(xCheck >= SCREEN_WIDTH){
            retValue = R_EXIT;
            ledPulse(0b100, 2);
            break;
        }

        if(yCheck < 0){
            if(retValue == H_COLLISION){
                retValue = VH_COLLISION;
            }
            else{
                retValue = H_COLLISION;
            }
            ball->y = ball->speed - i;
        }
        else if(yCheck >= SCREEN_HEIGHT){
            if(retValue == H_COLLISION){
                retValue = VH_COLLISION;
            }
            else{
                retValue = H_COLLISION;
            }
            ball->y = SCREEN_HEIGHT - ball->speed - BALL_SIZE + i;
        }
        if(retValue != NO_COLLISION){
            break;
        }
    }
    /*if((ball->x < PAD_X_OFFSET + PAD_WIDTH - ball->speed * ball->xVel)
            && (ball->y > pads->p1Pos - BALL_SIZE - ball->speed)
            && (ball->y < pads->p1Pos + PAD_HEIGHT + BALL_SIZE + ball->speed)){
        //Ball collides with the left pad
        ledPulse(0b111,1);
        ball->x = 2 * (ball->speed + PAD_WIDTH) + ball->speed - ball->x;
        retValue = V_COLLISION;
    }
    else if((ball->x > SCREEN_WIDTH - PAD_X_OFFSET - PAD_WIDTH - BALL_SIZE  + ball->speed * ball->xVel)
            && (ball->y > pads->p2Pos - BALL_SIZE - ball->speed)
            && (ball->y < pads->p2Pos + PAD_HEIGHT + BALL_SIZE + ball->speed)){
        //Ball collides with the right pad
        ledPulse(0b111, 2);
        int w = SCREEN_WIDTH - PAD_X_OFFSET - PAD_WIDTH;
        ball->x = 2 * (w - BALL_SIZE) - ball->speed - ball->x;
        retValue = V_COLLISION;
    }
    else if(ball->x < BALL_SIZE){
        //Ball reaches the left edge of the screen
        ledPulse(0b010, 1);
        return L_EXIT;
    }
    else if(ball->x > SCREEN_WIDTH - BALL_SIZE){
        ledPulse(0b001, 2);
        //Ball reaches the right edge of the screen
        return R_EXIT;
    }
    if(ball->y < - ball->speed * ball->yVel){
        //Ball reaches the top of the screen
        ball->y = ball->speed - ball->y;
        if(retValue == V_COLLISION){
            retValue = VH_COLLISION;
        }
        else{
            retValue = H_COLLISION;
        }
    }
    else if(ball->y > SCREEN_HEIGHT - BALL_SIZE + ball->speed * ball->yVel){
        //Ball reaches the bottom of the screen
        ball->y = 2 * (SCREEN_HEIGHT - BALL_SIZE) - ball->y;
        if(retValue == V_COLLISION){
            retValue = VH_COLLISION;
        }
        else{
            retValue = H_COLLISION;
        }
    }*/
    return retValue;
}
