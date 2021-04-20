#ifndef PADS_H
#define PADS_H

#include "colors.h"
#include "dimensions.h"
#include "peripherals.h"

#define NO_COLLISION 100
#define V_COLLISION 101
#define H_COLLISION 102
#define VH_COLLISION 103
#define L_EXIT 103
#define R_EXIT 104

typedef struct{
    int p1Pos;
    int p2Pos;
}pads_t;

void updatePads(int p1Offset, int p2Offset);

void renderPads();

char checkCollision(int x, int y, pads_t *pads);
#endif