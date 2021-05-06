#include <stdio.h>

typedef struct
{
	unsigned char x;
	unsigned char y;
	unsigned short w;
	unsigned short h;
	unsigned short colorBack;
	unsigned short colorText;
	char *text;
} button_t;

typedef struct {
	unsigned char current;
	unsigned char max;
	button_t buttonArray[2];
} menuButtons_t;

button_t b1;
button_t b2;
menuButtons_t menuButtons;

int main(void) {
    b1 = (button_t) { .x = 150, .y = 170, .w = 200, .h = 60, .colorBack = 1, .colorText = 1, .text = "START"};
    b2 = (button_t) {.x = 150, .y = 240, .w = 200, .h = 60, .colorBack = 1, .colorText = 1, .text = "TEST"};
    // Menu
    menuButtons = (menuButtons_t) {.current = 0, .max = 2, .buttonArray = {b1, b2}};

    printf("%d\n", menuButtons.)
    return 0;
}