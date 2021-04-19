#include "pads.h"

void updatePads(int p1Offset, int p2Offset){
    //WIP
}

void renderPads(){
    //WIP
}

char checkCollision(int x, int y){
    if(((x < BAR_X_OFFSET + PAD_WIDTH + BALL_SIZE)
            && (y > p1Pos - 2 * BALL_SIZE)
            && (y < p1Pos + PAD_WIDTH + 2 * BALL_SIZE))
            || ((x >= SCREEN_WIDTH - BAR_X_OFFSET - PAD_WIDTH - BALL_SIZE)
            && (x > p2Pos - 2 * BALL_SIZE)
            && (x < p2Pos + PAD_WIDTH + 2 * BALL_SIZE))){
        return V_COLLISION;
    }
    else if(x < BALL_SIZE){
        return V_COLLISION;
        //return L_EXIT;
    }
    else if(x >= SCREEN_WIDTH - BALL_SIZE){
        return V_COLLISION;
        //return R_EXIT;
    }
    else if((y < BALL_SIZE) || (y >= SCREEN_HEIGHT - BALL_SIZE)){
        return H_COLLISION;
    }
    return NO_COLLISION;
}
