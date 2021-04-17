#include <stdbool.h>

#include "mzapo_parlcd.h"
#include "mzapo_regs.h"

void updatePads(int p1Offset, int p2Offset);

void renderPads();

_Bool checkCollision(int x, int y);
