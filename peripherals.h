#ifndef PERIPHERALS_H
#define PERIPHERALS_H

#include <stdlib.h>
#include <stdio.h>

#include "colors.h"
#include "dimensions.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "mzapo_parlcd.h"

extern unsigned short *fb;

int getPlayerOffset(int player);

void draw_pixel(int x, int y, unsigned short color);

void clearScreen();

void renderScreenData(unsigned char *parlcdMemBase);

void fillRect(int x, int y, int width, int height, unsigned short color);

#endif