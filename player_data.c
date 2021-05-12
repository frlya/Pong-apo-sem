#include "player_data.h"

player_t player1;
player_t player2;

void initPlayers()
{
    //Player1 init
    player1.score = 0;
    player1.winner = false;

    //Player2 init
    player2.score = 0;
    player2.winner = false;
}

bool updateScore(int player, int value)
{
    unsigned int tmpInt;
    unsigned short tmpShort;
    if (player == 1)
    {
        player1.score = (player1.score + 1) * value;
        if (player1.score == 1)
        {
            tmpInt = 0x80000000;
            *led_line |= tmpInt;
        }
        else
        {
            tmpInt = *led_line;
            tmpInt >>= 1;
            *led_line |= tmpInt;
        }
        if (player1.score == 16)
            player1.winner = true;
        return true;
    }
    else if (player == 2)
    {
        player2.score = (player2.score + 1) * value;
        if (player2.score == 1)
        {
            tmpShort = 0x1;
            *led_line |= tmpShort;
        }
        else
        {
            tmpShort = *led_line;
            tmpShort <<= 1;
            *led_line |= tmpShort;
        }
        if (player2.score == 16)
            player2.winner = true;
        return true;
    }
    return false;
}

int getScore(int player)
{
    return (player == 1 ? player1.score : (player == 2 ? player2.score : -1));
}

void resetPlayers()
{
    //Difference apart from initPlayer may occur later
    //Player1 reset
    player1.score = 0;
    player1.winner = false;

    //Player2 reset
    player2.score = 0;
    player2.winner = false;

    *led_line = 0;
}

int checkWin()
{
    return (player1.winner ? 1 : (player2.winner ? 2 : 0));
}