#include "text.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

font_descriptor_t *fdes;

int countdownTimer = COUNTDOWN_PERIOD;
int currentCountdownScale = COUNTDOWN_BASE_SCALE;
int currentCountdownState = 3;

void renderText(int state)
{
	if (state == RESULT)
	{
		renderResults();
	}
	else if (state == RUNNING)
	{
		renderScore();
	}
	else if (state == READY)
	{
		renderCountdown();
	}
	else if (state == PAUSE)
	{
		renderPause();
	}
}

void updateText(int *state)
{
	if (*state == READY)
	{
		if (countdownTimer % 10 == 0)
		{
			currentCountdownScale -= 1;
		}
		if (countdownTimer % 20 == 0 && countdownTimer != COUNTDOWN_PERIOD)
		{
			countdownTimer = COUNTDOWN_PERIOD;
			currentCountdownState -= 1;
			countdownTimer -= 1;
		}
		else
		{
			countdownTimer -= 1;
		}
		if (currentCountdownState == 0)
		{
			countdownTimer = COUNTDOWN_PERIOD;
			currentCountdownScale = COUNTDOWN_BASE_SCALE;
			currentCountdownState = 3;
			*state = RUNNING;
		}
	}
}

void renderResults()
{
	int playerNum = checkWin();
	if (playerNum > 0)
	{
		char winMessage[14] = "Player X wins";
		winMessage[7] = ((char)playerNum) + '0';
		drawStringToScreen(
			SCREEN_WIDTH / 2 - (stringWidth(winMessage) * WIN_TEXT_SCALE) / 2,
			SCREEN_HEIGHT / 2 - (CHAR_HEIGHT * WIN_TEXT_SCALE) / 2, winMessage,
			WIN_TEXT_SCALE,
			0,
			COLOR_YELLOW);
	}

	char *wph = "PRESS GREEN";
	int wphScale = 2;
	drawStringToScreen(
		SCREEN_WIDTH / 2 - (stringWidth(wph) * wphScale) / 2,
		SCREEN_HEIGHT - 10 - CHAR_HEIGHT * wphScale,
		wph,
		wphScale,
		0,
		COLOR_GREEN);
}

void renderPause()
{
	char *question = "Back to menu?";

	drawStringToScreen(
		(SCREEN_WIDTH / 2) - (stringWidth(question) / 2) * INFO_TEXT_SCALE,
		SCREEN_HEIGHT / 2 - (CHAR_HEIGHT * INFO_TEXT_SCALE) / 2,
		question,
		INFO_TEXT_SCALE,
		0,
		COLOR_YELLOW);

	drawStringToScreen(0, SCREEN_HEIGHT - CHAR_HEIGHT * NAV_TEXT_SCALE, "YES", NAV_TEXT_SCALE, 0, COLOR_BLUE);
	drawStringToScreen(SCREEN_WIDTH - stringWidth("NO") * NAV_TEXT_SCALE, SCREEN_HEIGHT - CHAR_HEIGHT * NAV_TEXT_SCALE, "NO", NAV_TEXT_SCALE, 0, COLOR_RED);
}

void renderScore()
{
	// 1.
	char p[3];
	sprintf(p, "%d", player1.score);
	drawStringToScreen(SCREEN_WIDTH / 2 - (OFFSET1 + SCORE_TEXT_SCALE * stringWidth(p)), OFFSET2, p, SCORE_TEXT_SCALE, 0, COLOR_RED);

	// 2.
	sprintf(p, "%d", player2.score);
	drawStringToScreen(SCREEN_WIDTH / 2 + OFFSET1, OFFSET2, p, SCORE_TEXT_SCALE, 0, COLOR_BLUE);
}

void renderCountdown()
{
	drawChar(
		SCREEN_WIDTH / 2 - (currentCountdownScale * charWidth((char)currentCountdownState + '0')) / 2,
		SCREEN_HEIGHT / 2 - (currentCountdownScale * CHAR_HEIGHT) / 2,
		(char)currentCountdownState + '0',
		COLOR_GREEN,
		currentCountdownScale);
}

/*
*----------------------------------------------------
* Code below is taken from 8.lecture 
*----------------------------------------------------
*/

int charWidth(int ch)
{
	int width;
	if (!fdes->width)
	{
		width = fdes->maxwidth;
	}
	else
	{
		width = fdes->width[ch - fdes->firstchar];
	}
	return width;
}

int stringWidth(char *str)
{
	int i = 0;
	int w = 0;
	while (str[i] != '\0')
	{
		w += charWidth(str[i]);
		++i;
	}
	return w;
}

/*
*   Adjusts scale of character.
*   Service function
*/
void drawPixelBig(int x, int y, unsigned short color, int scale)
{
	int i, j;
	for (i = 0; i < scale; i++)
	{
		for (j = 0; j < scale; j++)
		{
			draw_pixel(x + i, y + j, color);
		}
	}
}

/*
 *  Draws character on the screen.
 *
 *  int x, y             - coordinates of left upper corner of char box.
 *  char ch              - character or its code from font table
 *  unsigned short color - color of the char      
 */
void drawChar(int x, int y, char ch, unsigned short color, int scale)
{
	int w = charWidth(ch);
	const font_bits_t *ptr;
	if ((ch >= fdes->firstchar) && (ch - fdes->firstchar < fdes->size))
	{
		if (fdes->offset)
		{
			ptr = &fdes->bits[fdes->offset[ch - fdes->firstchar]];
		}
		else
		{
			int bw = (fdes->maxwidth + 15) / 16;
			ptr = &fdes->bits[(ch - fdes->firstchar) * bw * fdes->height];
		}
		int i, j;
		for (i = 0; i < fdes->height; i++)
		{
			font_bits_t val = *ptr;
			for (j = 0; j < w; j++)
			{
				if ((val & 0x8000) != 0)
				{
					drawPixelBig(x + scale * j, y + scale * i, color, scale);
				}
				val <<= 1;
			}
			ptr++;
		}
	}
}

// Draws a string of characters to the screen.
// int x, y 	- left upper corner of a screen.
// char* line   - string to draw.
// scale 		- well... just scale.
// int kerning  - space between two latters.

void drawStringToScreen(int x, int y, char *line, int scale, int kerning, unsigned short color)
{
	int concatinated = 0;
	while (*line != '\0')
	{
		drawChar(x + (concatinated), y, *(line), color, scale);
		concatinated += (charWidth(*(line)) + kerning) * scale;
		line++;
	}
}
//-----------------------------------------------------------------------------
