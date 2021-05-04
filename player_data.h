#include <stdbool.h>

typedef struct {
    int score;
    bool winner;
    //More data may be added later in development (like pad height)
} player_t;

extern player_t player1;
extern player_t player2;

void initPlayers();

/*  If value is one score is increased by one, if value is zero, score is set to zero
 *  Returns true on success and false on error*/
bool updateScore(int player, int value);

//Returns score of a given player or -1 on error
int getScore(int player);

void resetPlayers();

//Returns number of a player that won or zero if nobody won
int checkWin();
