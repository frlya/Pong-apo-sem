#include "menu.h"

button_t b1;
button_t b2;
menuButtons_t mB;

menu_t menu;
int *state_c;



void pongText(){
    if(menu.titleState > 0) { 
        drawChar(0 * 120, 0, 'P', COLOR_WHITE, PONG_TEXT_SCALE);
    }
    
    if(menu.titleState > 1) {
        drawChar(1 * 120, 0, 'O', COLOR_WHITE, PONG_TEXT_SCALE);
    }

    if(menu.titleState > 2) { 
        drawChar(2 * 120, 0, 'N', COLOR_WHITE, PONG_TEXT_SCALE);
    }

    if(menu.titleState > 3) {
        drawChar(3 * 120, 0, 'G', COLOR_WHITE, PONG_TEXT_SCALE);
    }
}

void renderButtons() {
    // TODO: Add array of buttons.
    // fillRect(b1.x, b1.y, b1.w, b1.h, b1.colorBack);
    // drawStringToTheScreen(b1.x + 10, b1.y + 10, b1.text, 3, 0, b1.colorText);

    // fillRect(b2.x, b2.y, b2.w, b2.h, b2.colorBack);
    // drawStringToTheScreen(b2.x + 10, b2.y + 10, b2.text, 3, 0, b2.colorText);

    for(int i = 0; i < mB.max; i++){
        fillRect(mB.arr[i].x, mB.arr[i].y, mB.arr[i].w, mB.arr[i].h, mB.arr[i].colorBack);
        drawStringToTheScreen(mB.arr[i].x + 10, mB.arr[i].y + 10, mB.arr[i].text, 3, 0, mB.arr[i].colorText);
    }
}

void renderMenu(){
    if(menu.state == BEGIN || menu.state == PONG_HEADER_DONE || menu.state == MENU_BUTTONS){
        pongText();
    }
    if(menu.state == PONG_HEADER_DONE){
        drawStringToTheScreen(50, 170, "Hey Mate!", 4, 0, COLOR_WHITE);
		drawStringToTheScreen(50, 230, "Wanna play some pong? ;)", 2, 0, COLOR_WHITE);
    } 
    if(menu.state == MENU_BUTTONS) {
        renderButtons();
        //fillRect(50, 170, 100, 40, menu.color);
        //fillRect(50, 220, 100, 40, );
    }
}

void updateMenu(){
    if(menu.state == BEGIN){
        menu.ticker++;
        if(menu.ticker == 125){
            menu.ticker = 0;
            menu.state = PONG_HEADER_DONE;
        }
        else if(menu.ticker % 25 == 0){
            menu.titleState = menu.ticker / 25;
        }
    }
    else if(menu.state == PONG_HEADER_DONE){
        menu.ticker++;
        if(menu.ticker == 100){
            menu.ticker = 0;
            menu.state = MENU_BUTTONS;
        }
    }
    else if(menu.state == MENU_BUTTONS){
        menu.ticker++;
        if (knobPressed == (unsigned char)BLUE_PRESSED) {
                if(menu.ticker > 4) {
                    mB.arr[mB.current].colorBack = menu.color;
                    mB.current++;
                    mB.current %= mB.max;
                    mB.arr[mB.current].colorBack = COLOR_YELLOW;
                    menu.ticker = 0;
            }
        }
	if(knobPressed == RED_PRESSED){
		switch(mB.current)
		{
			case 0:
			  menu.state = STARTED; //Running
		  	  break;
			case 1:
			  printf("Test\n");
			  break;	  
		}
	}

    }
}

void menuInit(int *st){
    state_c = st;
    // Init menu handle
    menu.ticker = 0;
    menu.titleState = 0;
    menu.state = BEGIN;
    menu.color = COLOR_WHITE;

    // Buttons
    // 150, 170, 200, 60, COLOR_WHITE
    b1 = (button_t) { .x = 150, .y = 170, .w = 200, .h = 60, .colorBack = COLOR_YELLOW, .colorText = COLOR_BLACK, .text = "START"};
    b2 = (button_t) {.x = 150, .y = 240, .w = 200, .h = 60, .colorBack = menu.color, .colorText = COLOR_BLACK, .text = "TEST"};
    // Menu
    mB = (menuButtons_t) {.current = 0, .max = 2, .arr = {b1, b2}};
}
