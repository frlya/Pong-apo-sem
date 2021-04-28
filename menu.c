#include "menu.h"

void pongText(unsigned short **fb, font_descriptor_t *fdes, menu_t *menu){
    if(menu->titleState > 0) draw_char(0 * 120, 0, 'P', COLOR_WHITE, fb, PONG_TEXT_SCALE, fdes);
    if(menu->titleState > 1) draw_char(1 * 120, 0, 'O', COLOR_WHITE, fb, PONG_TEXT_SCALE, fdes);
    if(menu->titleState > 2) draw_char(2 * 120, 0, 'N', COLOR_WHITE, fb, PONG_TEXT_SCALE, fdes);
    if(menu->titleState > 3) draw_char(3 * 120, 0, 'G', COLOR_WHITE, fb, PONG_TEXT_SCALE, fdes);
}

void renderMenu(unsigned short **fb, font_descriptor_t *fdes, menu_t *menu){
    if(menu->state == BEGIN || menu->state == PONG_HEADER_DONE){
        pongText(fb, fdes, menu);
    }
    if(menu->state == PONG_HEADER_DONE){
        drawStringToTheScreen(50, 170, "Hey Mate!", 4, 0, fb, fdes);
		drawStringToTheScreen(50, 230, "Wanna play some pong? ;)", 2, 0, fb, fdes);
    }
}

void updateMenu(menu_t *menu){
    if(menu->state == BEGIN){
        menu->ticker++;
        if(menu->ticker == 125){
            menu->ticker = 0;
            menu->state = PONG_HEADER_DONE;
        }
        else if(menu->ticker % 25 == 0){
            menu->titleState = menu->ticker / 25;
        }
    }
    else if(menu->state == PONG_HEADER_DONE){
        menu->ticker++;
        if(menu->ticker == 150){
            menu->ticker = 0;
            menu->state = MENU_BUTTONS;
        }
    }
    else if(menu->state == MENU_BUTTONS) {
		// print rectangle scale
		menu->state = STARTED;
		// print rectangle new game
	}
}

void menuInit(menu_t *menu){
    menu->ticker = 0;
    menu->titleState = 0;
    menu->state = BEGIN;
}

