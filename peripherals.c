#include "dimensions.h"
#include "peripherals.h"

int getPlayerOffset(int player){
    int returnVal = 0;
    //WIP
    return returnVal;
}

/*
*   Draws single pixel
*   Service finction
*/
void draw_pixel(int x, int y, unsigned short color) {
  if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
    fb[x + SCREEN_WIDTH * y] = color;
  }
}

void clearScreen(){
  for(int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++){
    fb[i] = COLOR_BLACK;
  }
}