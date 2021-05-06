#include "score.h"

score_t scoreTable;

void initScore()
{
    scoreTable.pl1 = 0;
    scoreTable.pl2 = 0;
    *led_line = 0;
}

void addPointToPlayer(int player)
{
    unsigned int tmpInt;
    unsigned short tmpShort;
    switch (player) {
        case 1:
            if ((++scoreTable.pl1) == 1) {
                tmpInt = 0x80000000;
                *led_line |= tmpInt;
            } else {
                tmpInt = *led_line;
                tmpInt >>= 1;
                *led_line |= tmpInt;
            }
            break;
        case 2:
            if ((++scoreTable.pl2) == 1) {
                tmpShort = 0x1;
                *led_line |= tmpShort;
            } else {
                tmpShort = *led_line;
                tmpShort <<= 1;
                *led_line |= tmpShort;
            }
            break;
    }
}
