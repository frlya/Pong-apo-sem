#include "menu.h"

//button_t b1;
//button_t b2;
//menuButtons_t mB;

menu_t menu;
int *state_c;

uint8_t previousKnobMenu;
uint8_t currentKnobMenu;

void pongText(){
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
    drawStringToTheScreen(
        MENU_TEXT_SPACE,
        MENU_TEXT_Y_OFFSET - MENU_TEXT_SCALE_NORMAL * (CHAR_HEIGHT / 2),
        menu.mainItems[(menu.mainIndex - 1 + menu.maxMain) % menu.maxMain],
        MENU_TEXT_SCALE_NORMAL,
        0,
        COLOR_WHITE
    );

    drawStringToTheScreen(
        SCREEN_WIDTH / 2 - stringWidth(menu.mainItems[(menu.mainIndex) % menu.maxMain]) * MENU_TEXT_SCALE_SELECTED / 2,
        MENU_TEXT_Y_OFFSET - MENU_TEXT_SCALE_SELECTED * (CHAR_HEIGHT / 2),
        menu.mainItems[(menu.mainIndex) % menu.maxMain],
        MENU_TEXT_SCALE_SELECTED,
        0,
        COLOR_YELLOW
    );

    drawStringToTheScreen(
        SCREEN_WIDTH - MENU_TEXT_SPACE - stringWidth(menu.mainItems[(menu.mainIndex + 1) % menu.maxMain]) * MENU_TEXT_SCALE_NORMAL,
        MENU_TEXT_Y_OFFSET - MENU_TEXT_SCALE_NORMAL * (CHAR_HEIGHT / 2),
        menu.mainItems[(menu.mainIndex + 1) % menu.maxMain],
        MENU_TEXT_SCALE_NORMAL,
        0,
        COLOR_WHITE
    );
}

void renderMenu(){
    if(menu.state == BEGIN || menu.state == PONG_HEADER_DONE || menu.state == MENU_BUTTONS || menu.state == SETTINGS){
        pongText();
    }
    if(menu.state == PONG_HEADER_DONE){
        drawStringToTheScreen(50, 170, "Hey Mate!", 4, 0, COLOR_WHITE);
		drawStringToTheScreen(50, 230, "Wanna play some pong? ;)", 2, 0, COLOR_WHITE);
    } 
    if(menu.state == MENU_BUTTONS) {
        renderButtons();
    }
    if(menu.state == SETTINGS) {
        
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
        //currentKnobMenu = greenKnob;

        if(menu.buttonCooldown == 0) {
            //int check = previousKnobMenu - currentKnobMenu;

            if (knobPressed == BLUE_PRESSED){
                menu.mainIndex = (menu.mainIndex + 1) % 3;
            }
            if (knobPressed == RED_PRESSED){
                menu.mainIndex = (menu.mainIndex - 1 + menu.maxMain) % 3;
            }

            menu.buttonCooldown = 2;
            
        } else { menu.buttonCooldown--; }

        //previousKnobMenu = currentKnobMenu;
        
        printf("MENU STATE: %d\n", menu.mainIndex);

        /*if (menu.buttonCooldown == 0) {
            if (knobPressed == (unsigned char)BLUE_PRESSED){
                mB.arr[mB.current].colorBack = menu.color;
                mB.current++;
                mB.current %= mB.max;
                mB.arr[mB.current].colorBack = COLOR_YELLOW;
                menu.buttonCooldown = 5;
            }
        }
        else {
            menu.buttonCooldown--;
        }
        */
	    if(knobPressed == GREEN_PRESSED){
		    switch(menu.mainIndex){
			    case 0:
			        menu.state = STARTED; //Running
		  	        break;
			    case 1:
			        menu.state = SETTINGS;
			        break;
                case 2:
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
    /*
    else if (menu.state == SETTINGS)
    {
        menu.ticker++;
        if (knobPressed == (unsigned char)BLUE_PRESSED)
        {
            if (menu.ticker > 4)
            {
                
            }
        }
        if (knobPressed == RED_PRESSED)
        {
           
        }
    }
    */
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
    sprintf(menu.mainItems[1], "%s", "SETTINGS");
    sprintf(menu.mainItems[2], "%s", "EXIT");

    menu.mainIndex = 0;    
    menu.maxMain = 3;

    previousKnobMenu = greenKnob;
    currentKnobMenu = greenKnob;

    // Buttons
    // 150, 170, 200, 60, COLOR_WHITE
    //b1 = (button_t){.w = 250, .h = 60, .x = 0, .y = 0, .colorBack = COLOR_YELLOW, .colorText = COLOR_BLACK, .text = "START"};
    //b2 = (button_t){.w = 250, .h = 60, .x = 0, .y = 0, .colorBack = menu.color, .colorText = COLOR_BLACK, .text = "SETTINGS"};
    //b3 = (button_t){.w = 250, .h = 60, .x = 0, .y = 0, .colorBack = menu.color, .colorText = COLOR_BLACK, .text = "QUIT"};

    //b1.x = SCREEN_WIDTH/2 - b1.w/2;
    //b1.y = SCREEN_HEIGHT/2;

    //b2.x = SCREEN_WIDTH/2 - b2.w/2;
    //b2.y = b1.y + b1.h + 20; 


    // Menu
    //mB = (menuButtons_t) {.current = 0, .max = 2, .arr = {b1, b2}};
}

void settingsInit() {
    
}
