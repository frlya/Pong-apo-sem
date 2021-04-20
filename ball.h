#include "dimensions.h"
#include "mzapo_parlcd.h"
#include "mzapo_regs.h"
#include "pads.h"

#define START_POS_X 300
#define START_POS_Y 200
#define BASE_SPEED 4 //Defined as pixels per frame

extern int x;
extern int y;
extern int xVel;
extern int yVel;

/*  Why not to consider a struct to represent the ball?
    typedef struct {
        int x, y;       // Coordinates of the ball
        int w, h;       // Width and height of the ball
    } ball_t;
*/

void updateBall();

void renderBall();

void resetBall();