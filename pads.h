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

uint8_t previousKnobP1;
uint8_t currentKnobP1;

uint8_t previousKnobP2;
uint8_t currentKnobP2;

unsigned char padsSpeedScale;

typedef struct
{
    int p1Pos;
    int p2Pos;
    int p1Vel;
    int p2Vel;
} pads_t;

void updatePads(pads_t *pads, int p1Offset, int p2Offset);

void renderPads(pads_t *pads);

void renderCentralLine();

void initHandle();

void resetPads(pads_t *pads);

#endif