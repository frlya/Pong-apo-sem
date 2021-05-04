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
unsigned char *parlcdMemBase; // Screen
volatile uint32_t *led_line;  // Led line
volatile u_int32_t *rgb_led1; // RGBs
volatile u_int32_t *rgb_led2; //
volatile u_int32_t *knobs;    // Knobs

int getPlayerOffset(int player);

void draw_pixel(int x, int y, unsigned short color);

void clearScreen();

void renderScreenData(unsigned char *parlcdMemBase);

void fillRect(int x, int y, int width, int height, unsigned short color);

#endif