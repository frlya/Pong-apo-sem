#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "ball.h"
#include "colors.h"
#include "dimensions.h"
#include "font_types.h"
#include "games_states.h"
#include "menu.h"
#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "pads.h"
#include "peripherals.h"
#include "player_data.h"
#include "text.h"

extern pads_t pads;
extern ball_t ball;

extern int state;
extern bool stateSwitch;
extern int scale;

extern struct timespec loopDelay;

void update(int *state);
void render(int *state);
void exitGame();

#endif