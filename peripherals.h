#ifndef PERIPHERALS_H
#define PERIPHERALS_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "colors.h"
#include "dimensions.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "mzapo_parlcd.h"

extern uint16_t *fb;
extern uint8_t *parlcdMemBase; // Screen
extern volatile uint32_t *led_line;  // Led line
extern volatile uint32_t *rgb_led1; // RGBs
extern volatile uint32_t *rgb_led2; //
extern volatile uint32_t *knobs;    // Knobs
extern u_int8_t redKnob;
extern u_int8_t greenKnob;
extern u_int8_t blueKnob;

extern uint8_t ledCounter;
extern uint8_t baseColor;
extern uint8_t currentLed;
extern uint32_t ledCount;

extern uint8_t knobPressed;

extern bool redReleased;
extern bool greenReleased;
extern bool blueReleased;

extern uint8_t right;

enum knobsPressed
{
    URGENT_EXIT = 7,
    RED_PRESSED = 4,
    GREEN_PRESSED = 2,
    BLUE_PRESSED = 1
};

void ledPulse(uint8_t color, uint8_t led);

void updateLed();

int getPlayerOffset(int player);

void draw_pixel(int x, int y, uint16_t color);

void clearScreen();

void renderScreenData(uint8_t *parlcdMemBase);

void fillRect(int x, int y, int width, int height, uint16_t color);

void snakeLED();

void initSnake();

void initWinSnakeLED();

void winSnakeLED();

void initWinLights();

void winLights();

void inputHandler();

#endif