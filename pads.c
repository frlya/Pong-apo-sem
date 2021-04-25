#include "pads.h"

void updatePads(pads_t *pads, int p1Offset, int p2Offset){
    //Simulating pads movement, will be replaced by controlled movement later
    if((pads->p1Pos < 4) || (pads->p1Pos > SCREEN_HEIGHT - PAD_HEIGHT - 4)){
        pads->p1Vel *= -1;
    }
    pads->p1Pos += 2 * pads->p1Vel;

    if((pads->p2Pos < 4) || (pads->p2Pos > SCREEN_HEIGHT - PAD_HEIGHT - 4)){
        pads->p2Vel *= -1;
    }
    pads->p2Pos += 2 * pads->p2Vel;
}

void renderPads(pads_t *pads, unsigned short **fb){
    fillRect(PAD_X_OFFSET, pads->p1Pos, PAD_WIDTH, PAD_HEIGHT, COLOR_WHITE, fb);
    fillRect(SCREEN_WIDTH - PAD_X_OFFSET - PAD_WIDTH - 1, pads->p2Pos, PAD_WIDTH, PAD_HEIGHT, COLOR_WHITE, fb);
}

void renderCentralLine(unsigned short **fb){
    int segmentSize = SCREEN_HEIGHT / (CL_SEGMENTS * 2);
    for(int i = 0; i < CL_SEGMENTS; i++){
        fillRect(SCREEN_WIDTH / 2 - PAD_WIDTH / 2, 2 * i * segmentSize, CL_WIDTH, segmentSize, COLOR_WHITE, fb);
    }
}
