#include "menu.h"

menu_t menu;

void pongText(){
    if(menu.titleState > 0) drawChar(0 * 120, 0, 'P', COLOR_WHITE, PONG_TEXT_SCALE);
    *rgb_led1 = 0xffffffff;
    *rgb_led2 = 0x00000000;
    
    if(menu.titleState > 1) drawChar(1 * 120, 0, 'O', COLOR_WHITE, PONG_TEXT_SCALE);
    *rgb_led1 = 0x00000000;
    *rgb_led2 = 0xffffffff;

    if(menu.titleState > 2) drawChar(2 * 120, 0, 'N', COLOR_WHITE, PONG_TEXT_SCALE);
    *rgb_led1 = 0xffffffff;
    *rgb_led2 = 0x00000000;

    if(menu.titleState > 3) drawChar(3 * 120, 0, 'G', COLOR_WHITE, PONG_TEXT_SCALE);
    *rgb_led1 = 0x00000000;
    *rgb_led2 = 0xffffffff;
}

void renderMenu(){
    if(menu.state == BEGIN || menu.state == PONG_HEADER_DONE){
        pongText();
    }
    if(menu.state == PONG_HEADER_DONE){
        drawStringToTheScreen(50, 170, "Hey Mate!", 4, 0);
		drawStringToTheScreen(50, 230, "Wanna play some pong? ;)", 2, 0);
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
        if(menu.ticker == 150){
            menu.ticker = 0;
            menu.state = MENU_BUTTONS;
        }
    }
    else if(menu.state == MENU_BUTTONS){
		// print rectangle scale
		menu.state = STARTED;
		// print rectangle new game
	}
}

void menuInit(){
    menu.ticker = 0;
    menu.titleState = 0;
    menu.state = BEGIN;
}

