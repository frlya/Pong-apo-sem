#include "peripherals.h"

unsigned short *fb;
unsigned char *parlcdMemBase;
volatile uint32_t *led_line;
volatile u_int32_t *rgb_led1;
volatile u_int32_t *rgb_led2;
volatile u_int32_t *knobs;
unsigned char knobPressed;
u_int8_t redKnob;
u_int8_t greenKnob;
u_int8_t blueKnob;

 uint8_t ledCounter;
uint8_t baseColor;
uint8_t currentLed;

unsigned char right;
unsigned int ledCount;

bool redReleased;
bool greenReleased;
bool blueReleased;

void ledPulse(uint8_t color, uint8_t led)
{
	currentLed = led;
	ledCounter = 255;
	baseColor = color;
}

void inputHandler(){
	char redPressed = knobPressed & 0b100;
	char greenPressed = knobPressed & 0b010;
	char bluePressed = knobPressed & 0b001;

	redReleased = false;
	greenReleased = false;
	blueReleased = false;

	knobPressed = (*knobs) >> 24;
	redKnob = (*knobs >> 16) & 0xFF;
	greenKnob = (*knobs >> 8) & 0xFF;
	blueKnob = *knobs & 0xFF;

	if (redPressed - (knobPressed & 0b100) == 0b100) redReleased = true;
	if (greenPressed - (knobPressed & 0b010) == 0b010) greenReleased = true;
	if (bluePressed - (knobPressed & 0b001) == 0b001) blueReleased = true;
}

int getPlayerOffset(int player)
{
	int returnVal = 0;
    //WIP
    return returnVal;
}

/*
*   Draws single pixel
*   Service finction
*/
void draw_pixel(int x, int y, unsigned short color){
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT){
		fb[x + SCREEN_WIDTH * y] = color;
	}
}

void clearScreen(){
	for(int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++){
		fb[i] = COLOR_BLACK;
	}
}

void renderScreenData(unsigned char *parlcdMemBase){
	parlcd_write_cmd(parlcdMemBase, 0x2c);
	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++){
		parlcd_write_data(parlcdMemBase, fb[i]);
	}
}

void fillRect(int x, int y, int width, int height, unsigned short color){
	for(int i = 0; i < width; i++){
		for(int j = 0; j < height; j++){
			draw_pixel(x + i, y + j, color);
		}
	}
}

void updateLed() {
	uint8_t R = ((baseColor >> 2) * ledCounter);
	uint8_t G =	((baseColor >> 1)%2) * ledCounter;
	uint8_t B = (baseColor % 2) * ledCounter;

	if(ledCounter != 0){
		ledCounter -= 15;
	}

	if (currentLed == 1)
	{
		*rgb_led1 = ((uint32_t)R << 16) + ((uint32_t)G << 8) + (uint32_t)B;
	}
	if (currentLed == 2)
	{
		*rgb_led2 = ((uint32_t)R << 16) + ((uint32_t)G << 8) + (uint32_t)B;
	}
}

void initSnake()
{
	*led_line = 0x80000000;
	right = 1;
	ledCount = 0;
}

void snakeLED()
{
	if (ledCount % 10000)
	{
		if (right)
		{
			if (*led_line == 1)
			{
				right = 0;
			}
			else
			{
				*led_line >>= 1;
			}
		}
		else
		{
			if (*led_line == 0x80000000)
			{
				right = 1;
			}
			else
			{
				*led_line <<= 1;
			}
		}
	}
	ledCount++;
}

void initWinSnakeLED() {
	*led_line = 0x00018000;
	ledCount = 0;
}

void winSnakeLED() {
	if(ledCount % 1000) {
		unsigned int tmpLF;
		unsigned int tmpRT;
		if(*led_line == 0xFFFFFFFF) {
			*led_line = 0x00018000;
		} else {
			tmpLF = *led_line;
			tmpRT = *led_line;
			tmpLF <<= 1;
			tmpRT >>= 1;
			*led_line = *led_line | tmpLF | tmpRT ;
		}
	}
	ledCount++;
}

