#include "pads.h"
uint8_t previousKnobP1;
u_int8_t currentKnobP1;

uint8_t previousKnobP2;
u_int8_t currentKnobP2;

unsigned char padsSpeedScale = 6;

void initHandle()
{
    previousKnobP1 = redKnob;
    currentKnobP1 = redKnob;

    previousKnobP2 = blueKnob;
    currentKnobP2 = blueKnob;
}

void updatePads(pads_t *pads, int p1Offset, int p2Offset)
{
    currentKnobP1 = redKnob;
    if (pads->p1Pos < 4)
    {
        pads->p1Pos += 10;
    }
    else if (pads->p1Pos > SCREEN_HEIGHT - PAD_HEIGHT - 4)
    {
        pads->p1Pos -= 10;
    }
    else
    {
        int check = previousKnobP1 - currentKnobP1;

        if (check < -1 && check > -50)
        {
            pads->p1Pos += (padsSpeedScale * PAD_SPEED);
        }
        if (check > 1 && check < 50)
        {
            pads->p1Pos -= (padsSpeedScale * PAD_SPEED);
        }
    }

    previousKnobP1 = currentKnobP1;

    currentKnobP2 = blueKnob;
    if (pads->p2Pos < 4)
    {
        pads->p2Pos += 10;
    }
    else if (pads->p2Pos > SCREEN_HEIGHT - PAD_HEIGHT - 4)
    {
        pads->p2Pos -= 10;
    }
    else
    {
        int check = previousKnobP2 - currentKnobP2;

        if (check < -1 && check > -50)
        {
            pads->p2Pos += (padsSpeedScale * PAD_SPEED);
        }
        if (check > 1 && check < 50)
        {
            pads->p2Pos -= (padsSpeedScale * PAD_SPEED);
        }
    }
    previousKnobP2 = currentKnobP2;
}

void renderPads(pads_t *pads)
{
    fillRect(PAD_X_OFFSET, pads->p1Pos, PAD_WIDTH, PAD_HEIGHT, COLOR_RED);
    fillRect(SCREEN_WIDTH - PAD_X_OFFSET - PAD_WIDTH - 1, pads->p2Pos, PAD_WIDTH, PAD_HEIGHT, COLOR_BLUE);
}

void renderCentralLine()
{
    int segmentSize = SCREEN_HEIGHT / (CL_SEGMENTS * 2);
    for (int i = 0; i < CL_SEGMENTS; i++)
    {
        fillRect(SCREEN_WIDTH / 2 - PAD_WIDTH / 2, 2 * i * segmentSize, CL_WIDTH, segmentSize, COLOR_WHITE);
    }
}

void resetPads(pads_t *pads)
{
    pads->p1Pos = SCREEN_HEIGHT / 2 - PAD_HEIGHT / 2;
    pads->p2Pos = SCREEN_HEIGHT / 2 - PAD_HEIGHT / 2;
}
