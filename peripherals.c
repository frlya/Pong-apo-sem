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
void draw_pixel(int x, int y, unsigned short color, unsigned short **fb) {
  if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
    (*fb)[x + SCREEN_WIDTH * y] = color;
  }
}

void clearScreen(unsigned short **fb){
  for(int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++){
    (*fb)[i] = COLOR_BLACK;
  }
}

void renderScreenData(unsigned short **fb, unsigned char *parlcdMemBase){
  parlcd_write_cmd(parlcdMemBase, 0x2c);
  for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
    parlcd_write_data(parlcdMemBase, (*fb)[i]);
  }
}

void fillRect(int x, int y, int width, int height, unsigned short color, unsigned short **fb){
  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
      draw_pixel(x + i, y + j, color, fb);
    }   
  }
}