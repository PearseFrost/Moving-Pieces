//
// Created by Pearse Frost on 20/04/2020.
//
#include <stdio.h>
#include "game_functions.h"


void gameloop(square board[BOARD_SIZE][BOARD_SIZE],player players[PLAYERS_NUM]){
   int count=0;
           while(count<2){
               if(count%2==0) {
                   printf("Player1 turn");
                   int x,y;
                   move direct;
                   printf("Choose the co-ordinates of the piece you would like to move");
                   printf("x co-oridnate:");
                   scanf("%d",x);
                   printf("y co-ordinate:");
                   scanf("%d",y);
                  printf("What way would you like to move:");
                  printf("1.Moves RIGHT");
                  printf("2.Moves LEFT");
                  printf("3.Moves UP");
                  printf("4.Moves DOWN");
                  scanf("")



                   movepiece(board,x,y,direct);

               }

               if(count%2==1){
                   printf("Player2 turn");
               }
               count++;
           }
}
void movepiece(square board[BOARD_SIZE][BOARD_SIZE],int x, int y,move direct){
    int nextx=x;
    int nexty=y-1;

    if(board[nexty][nextx].num_pieces==0) {
        board[nexty][nextx].num_pieces = board[y][x].num_pieces;
        board[y][x].num_pieces = 0;
        board[nexty][nextx].stack=board[y][x].stack;
        board[y][x].stack=0;
    }





}
