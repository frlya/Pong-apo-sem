#include "pads.h"

void updatePads(int p1Offset, int p2Offset){
    //WIP
}

void renderPads(pads_t *pads){
    for(int i = 0; i < PAD_WIDTH; i++){
        for(int j = 0; j < PAD_HEIGHT; j++){
            draw_pixel(BAR_X_OFFSET + i, pads->p1Pos + j, COLOR_WHITE);
        }
    }

    for(int i = 0; i < PAD_WIDTH; i++){
        for(int j = 0; j < PAD_HEIGHT; j++){
            draw_pixel(SCREEN_WIDTH - BAR_X_OFFSET - i - 1, pads->p2Pos + j, COLOR_WHITE);
        }
    }
}

char checkCollision(int x, int y, pads_t *pads){
    char retValue = NO_COLLISION;
    if(((x < BAR_X_OFFSET + PAD_WIDTH + BALL_SIZE)
            && (y > pads->p1Pos - 2 * BALL_SIZE)
            && (y < pads->p1Pos + PAD_WIDTH + 2 * BALL_SIZE))
            || ((x >= SCREEN_WIDTH - BAR_X_OFFSET - PAD_WIDTH - BALL_SIZE)
            && (x > pads->p2Pos - 2 * BALL_SIZE)
            && (x < pads->p2Pos + PAD_WIDTH + 2 * BALL_SIZE))){
        retValue = V_COLLISION;
    }
    else if(x < BALL_SIZE){
        retValue = V_COLLISION;
        //return L_EXIT;
    }
    else if(x >= SCREEN_WIDTH - BALL_SIZE){
        retValue = V_COLLISION;
        //return R_EXIT;
    }
    else if((y < BALL_SIZE) || (y >= SCREEN_HEIGHT - BALL_SIZE)){
        if(retValue == V_COLLISION){
            retValue = VH_COLLISION;
        }
        else{
            retValue = H_COLLISION;
        }
    }
    return retValue;
}
