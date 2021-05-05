#ifndef SCORE_H
#define SCORE_H

#include <math.h>

#include "peripherals.h"


typedef struct {
    unsigned char pl1;
    unsigned char pl2;
    int ledState;
} score_t;

score_t scoreTable;

void initScore();

void addPointToPlayer(int player);

#endif