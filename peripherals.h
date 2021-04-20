#ifndef PERIPHERALS_H
#define PERIPHERALS_H

#include "colors.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"

unsigned short *fb;         //  Array of pixels

int getPlayerOffset(int player);

void draw_pixel(int x, int y, unsigned short color);

void clearScreen();

#endif