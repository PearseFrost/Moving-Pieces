//
// Created by Pearse Frost on 20/04/2020.
//

#ifndef UNTITLED9_GAME_FUNCTIONS_H
#define UNTITLED9_GAME_FUNCTIONS_H
#include "game_init.h"
#endif //UNTITLED9_GAME_FUNCTIONS_H
void gameloop(square board[BOARD_SIZE][BOARD_SIZE],player players[PLAYERS_NUM]);
void movepiece(square board[BOARD_SIZE][BOARD_SIZE],int x, int y,move direct);