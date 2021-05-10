#include "menu.h"

//button_t b1;
//button_t b2;
//menuButtons_t mB;

menu_t menu;
int *state_c;

uint8_t previousKnobMenu;
uint8_t currentKnobMenu;

unsigned char navigationScaleLeft;
unsigned char navigationScaleRight;
unsigned char navigationScaleCenter;

void pongText()
{
    uint16_t pongColors[4] = {COLOR_RED, COLOR_YELLOW, COLOR_GREEN, COLOR_BLUE};

    if(menu.titleState > 0) { 
        drawChar(0 * 120, 0, 'P', pongColors[(menu.pongTextShift) % 4], PONG_TEXT_SCALE);
    }
    
    if(menu.titleState > 1) {
        drawChar(1 * 120, 0, 'O', pongColors[(menu.pongTextShift + 1) % 4], PONG_TEXT_SCALE);
    }

    if(menu.titleState > 2) { 
        drawChar(2 * 120, 0, 'N', pongColors[(menu.pongTextShift + 2) % 4], PONG_TEXT_SCALE);
    }

    if(menu.titleState > 3) {
        drawChar(3 * 120, 0, 'G', pongColors[(menu.pongTextShift + 3) % 4], PONG_TEXT_SCALE);
    }

    if((menu.ticker % PONG_TEXT_ANIMATION_SPEED == 0) && menu.state == MENU_BUTTONS){
        menu.pongTextShift++;
    }
}

void renderButtons() {
    drawStringToScreen(
        MENU_TEXT_SPACE,
        MENU_TEXT_Y_OFFSET - MENU_TEXT_SCALE_NORMAL * (CHAR_HEIGHT / 2),
        menu.mainItems[(menu.mainIndex - 1 + menu.maxMain) % menu.maxMain],
        MENU_TEXT_SCALE_NORMAL,
        0,
        COLOR_WHITE
    );

    drawStringToScreen(
        SCREEN_WIDTH / 2 - stringWidth(menu.mainItems[(menu.mainIndex) % menu.maxMain]) * MENU_TEXT_SCALE_SELECTED / 2,
        MENU_TEXT_Y_OFFSET - MENU_TEXT_SCALE_SELECTED * (CHAR_HEIGHT / 2),
        menu.mainItems[(menu.mainIndex) % menu.maxMain],
        MENU_TEXT_SCALE_SELECTED,
        0,
        COLOR_YELLOW
    );

    drawStringToScreen(
        SCREEN_WIDTH - MENU_TEXT_SPACE - stringWidth(menu.mainItems[(menu.mainIndex + 1) % menu.maxMain]) * MENU_TEXT_SCALE_NORMAL,
        MENU_TEXT_Y_OFFSET - MENU_TEXT_SCALE_NORMAL * (CHAR_HEIGHT / 2),
        menu.mainItems[(menu.mainIndex + 1) % menu.maxMain],
        MENU_TEXT_SCALE_NORMAL,
        0,
        COLOR_WHITE
    );

    drawChar(
        SCREEN_WIDTH/2 - charWidth(0x5e)/2 * navigationScaleCenter,
        SCREEN_HEIGHT - CHAR_HEIGHT * navigationScaleCenter,
        0x5e,
        COLOR_GREEN,
        navigationScaleCenter
    );

    drawChar(
        0,
        MENU_TEXT_Y_OFFSET - MENU_TEXT_SCALE_SELECTED * (CHAR_HEIGHT / 2),
        0x3c,
        COLOR_RED,
        navigationScaleLeft
    );
    drawChar(
        SCREEN_WIDTH - charWidth(0x5e) * navigationScaleRight,
        MENU_TEXT_Y_OFFSET - MENU_TEXT_SCALE_SELECTED * (CHAR_HEIGHT / 2),
        0x3e,
        COLOR_BLUE,
        navigationScaleRight
    );
}

void renderMenu(){
    if(menu.state == BEGIN || menu.state == PONG_HEADER_DONE || menu.state == MENU_BUTTONS){
        pongText();
    }
    if(menu.state == PONG_HEADER_DONE){
        drawStringToScreen(50, 170, "Hey Mate!", 4, 0, COLOR_WHITE);
		drawStringToScreen(50, 230, "Wanna play some pong? ;)", 2, 0, COLOR_WHITE);
    } 
    if(menu.state == MENU_BUTTONS) {
        renderButtons();
    }
    if(menu.state == CREDITS) {
        if(menu.ticker < 400){
            drawStringToScreen(
                SCREEN_WIDTH / 2 - stringWidth("Ilya Fralou") * MENU_TEXT_CREDITS / 2,
                SCREEN_HEIGHT - menu.ticker,
                "Ilya Fralou",
                MENU_TEXT_CREDITS,
                0,
                COLOR_RED
            );
        }
        else{
            drawStringToScreen(
                SCREEN_WIDTH / 2 - stringWidth("Jakub Sakar") * MENU_TEXT_CREDITS / 2,
                SCREEN_HEIGHT - menu.ticker + 400,
                "Jakub Sakar",
                MENU_TEXT_CREDITS,
                0,
                COLOR_BLUE
            );
        }
        printf("Ticker: %d\n", menu.ticker);
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
        
        if(knobPressed == BLUE_PRESSED) {
            navigationScaleRight = 3;
        }

        if (knobPressed == RED_PRESSED)
        {
            navigationScaleLeft = 3;
        }

        if (blueReleased){
            navigationScaleRight = 2;
            menu.mainIndex = (menu.mainIndex + 1) % menu.maxMain;
        }
        if (redReleased){
            navigationScaleLeft = 2;
            menu.mainIndex = (menu.mainIndex - 1 + menu.maxMain) % menu.maxMain;
        }

	    if(greenReleased){
		    switch(menu.mainIndex){
			    case 0:
			        menu.state = STARTED; //Running
		  	        break;
			    case 1:
			        menu.state = CREDITS;
			        break;
                case 2:
                    menu.ticker = 0;
                    clearScreen();
                    renderScreenData(parlcdMemBase);
                    *rgb_led1 = 0;
                    *rgb_led2 = 0;
                    *led_line = 0;
                    exit(0);
                    break;	  
		    }
        }
    }

    else if(menu.state == CREDITS){
        menu.ticker += 4;
        if(menu.ticker == 800){
            menu.ticker = 0;
            menu.state = MENU_BUTTONS;
        }
    }
}

void handlePause(int *state){
    if(redReleased) {
        *state = MENU;
        menu.state = MENU_BUTTONS;
    } 
    else if (blueReleased) {
        *state = RUNNING;
    }
}

void menuInit(int *st){
    state_c = st;
    // Init menu handle
    menu.ticker = 0;
    menu.titleState = 0;
    menu.pongTextShift = 0;
    menu.state = BEGIN;
    menu.color = COLOR_WHITE;
    menu.buttonCooldown = 0;

    sprintf(menu.mainItems[0],"%s", "START");
    sprintf(menu.mainItems[1], "%s", "CREDITS");
    sprintf(menu.mainItems[2], "%s", "EXIT");

    menu.mainIndex = 0;    
    menu.maxMain = 3;

    previousKnobMenu = greenKnob;
    currentKnobMenu = greenKnob;

    navigationScaleCenter = 2;
    navigationScaleLeft = 2;
    navigationScaleRight = 2;
}
