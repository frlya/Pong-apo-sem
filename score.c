#include "score.h"

score_t scoreTable;

void initScore() {
    scoreTable.pl1 = 0;
    scoreTable.pl2 = 0;
    *led_line = 0;
}

void addPointToPlayer(int player) {
    switch (player)
    {
    case 1:
        scoreTable.pl1++;
         break;
    case 2:
        if((++scoreTable.pl2) == 1) {
		 *led_line = 1;
	} else {
        	unsigned short tmp = *led_line;
        	tmp <<= 1;
        	*led_line |= tmp;
	}
        break;
    }
}

/*
void scoreAddLED(int player) {
    switch(player) {
        case 1:
            
            break;
        case 2:
            unsigned short tmp = *led_line;

            break;
    }
}
*/
