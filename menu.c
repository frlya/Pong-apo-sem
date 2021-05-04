#include "menu.h"

button_t b1;
button_t b2;
menuButtons_t menuButtons;

menu_t menu;

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
    fillRect(b1.x, b1.y, b1.w, b1.h, b1.colorBack);
    drawStringToTheScreen(b1.x + 10, b1.y + 10, b1.text, 1, 0, b1.colorText);

    fillRect(b2.x, b2.y, b2.w, b2.h, b2.colorBack);
    drawStringToTheScreen(b2.x + 10, b2.y + 10, b2.text, 1, 0, b2.colorText);
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
        if(menu.ticker == 150){
            menu.ticker = 0;
            menu.state = MENU_BUTTONS;
        }
    }
    else if(menu.state == MENU_BUTTONS){
    
		// print rectangle scale
        // True
        // print rectangle new game
	}
}

void menuInit(){
    // Init menu handle
    menu.ticker = 0;
    menu.titleState = 0;
    menu.state = MENU_BUTTONS;
    menu.color = COLOR_WHITE;

    // Buttons
    // 150, 170, 200, 60, COLOR_WHITE
    b1 = (button_t) { .x = 150, .y = 170, .w = 200, .h = 60, .colorBack = menu.color, .colorText = COLOR_WHITE, .text = "START"};
    b2 = (button_t) {.x = 150, .y = 240, .w = 200, .h = 60, .colorBack = menu.color, .colorText = COLOR_WHITE, .text = "TEST"};

    // Menu
    menuButtons = (menuButtons_t) {.current = 0, .max = 2};
}

