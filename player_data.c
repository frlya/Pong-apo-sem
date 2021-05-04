#include "player_data.h"

player_t player1;
player_t player2;

void initPlayers(){
    //Player1 init
    player1.score = 0;
    player1.winner = false;

    //Player2 init
    player2.score = 0;
    player2.winner = false;
}

bool updateScore(int player, int value){
    if(player == 1){
        player1.score = (player1.score + 1) * value;
        if(player1.score == 10) player1.winner = true;
        return true;
    }
    else if(player == 2){
        player2.score = (player2.score + 1) * value;
        if(player1.score == 10) player1.winner = true;
        return true;
    }
    return false;
}

int getScore(int player){
    return (player == 1 ? player1.score : (player == 2 ? player2.score : -1));
}

void resetPlayers(){
    //Difference apart from initPlayer may occur later
    //Player1 reset
    player1.score = 0;
    player1.winner = false;

    //Player2 reset
    player2.score = 0;
    player2.winner = false;
}

int checkWin(){
    return (player1.winner ? 1 : (player2.winner ? 2 : 0));
}