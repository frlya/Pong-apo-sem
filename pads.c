#include "pads.h"

void updatePads(int p1Offset, int p2Offset){
    //WIP
}

void renderPads(pads_t *pads, unsigned short **fb){
    fillRect(BAR_X_OFFSET, pads->p1Pos, PAD_WIDTH, PAD_HEIGHT, COLOR_WHITE, fb);
    fillRect(SCREEN_WIDTH - BAR_X_OFFSET - PAD_WIDTH - 1, pads->p2Pos, PAD_WIDTH, PAD_HEIGHT, COLOR_WHITE, fb);
}

void renderCentralLine(unsigned short **fb){
    int segmentSize = SCREEN_HEIGHT / (CL_SEGMENTS * 2);
    for(int i = 0; i < CL_SEGMENTS; i++){
        fillRect(SCREEN_WIDTH / 2 - PAD_WIDTH / 2, 2 * i * segmentSize, CL_WIDTH, segmentSize, COLOR_WHITE, fb);
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
