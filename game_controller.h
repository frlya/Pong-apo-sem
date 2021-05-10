#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>

#include "mzapo_regs.h"
#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "colors.h"
#include "dimensions.h"
#include "peripherals.h"
#include "pads.h"
#include "text.h"
#include "font_types.h"
#include "menu.h"
#include "player_data.h"
#include "games_states.h"
#include "ball.h"

extern pads_t pads;
extern ball_t ball;

int state;
bool stateSwitch;
int scale;

struct timespec loopDelay;

void update(int *state);
void render(int *state);
void exitGame();

#endif