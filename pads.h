#ifndef PADS_H
#define PADS_H

#include "colors.h"
#include "dimensions.h"
#include "peripherals.h"

#define NO_COLLISION 100
#define V_COLLISION 101
#define H_COLLISION 102
#define VH_COLLISION 103
#define L_EXIT 104
#define R_EXIT 105

typedef struct{
    int p1Pos;
    int p2Pos;
    int p1Vel;
    int p2Vel;
}pads_t;

void updatePads(pads_t *pads, int p1Offset, int p2Offset);

void renderPads(pads_t *pads, unsigned short **fb);

void renderCentralLine(unsigned short **fb);
#endif