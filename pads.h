#include <stdbool.h>
#include "dimensions.h"
#include "mzapo_parlcd.h"
#include "mzapo_regs.h"

#define NO_COLLISION 100
#define V_COLLISION 101
#define H_COLLISION 102
#define L_EXIT 103
#define R_EXIT 104

extern int p1Pos;
extern int p2Pos;

/*  Why not to define single pad as a struct? 
    typedef struct {
        int x, y;       // Coordinates of the pad
        int w, h;       // Parameteres of the pa
    } pad_t;
*/

void updatePads(int p1Offset, int p2Offset);

void renderPads();

char checkCollision(int x, int y);
