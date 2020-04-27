//
// Created by Pearse Frost on 20/04/2020.
//
#include <stdio.h>
#include "game_functions.h"
#include"input_output.h"

void gameloop(square board[BOARD_SIZE][BOARD_SIZE],player players[PLAYERS_NUM]){
   int count=0;
           while(count<10){
               if(count%2==0) {
                   printf("Player1 turn");
                   print_board(board);
                   int x,y;
                   move direct;
                   do {
                       printf("Choose the co-ordinates of the piece you would like to move\n");
                       printf("x co-oridnate:\n");
                       scanf(" %d", &x);
                       printf("y co-ordinate:\n");
                       scanf(" %d", &y);
                       while(board[x][y]!= INVALID||x<8||y<8||);
                   }
                  printf("What way would you like to move:\n");
                  printf("1.Moves RIGHT\n");
                  printf("2.Moves LEFT\n");
                  printf("3.Moves UP\n");
                  printf("4.Moves DOWN\n");
                  scanf("%d",&direct);



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
    int nexty=y;
    if(direct==UP){
        nexty--;
    }else if(direct==DOWN){
        nexty++;
    }else if(direct==LEFT){
        nextx++;
    }else if(direct==RIGHT){
        nextx--;
    }

    if(board[nexty][nextx].num_pieces==0) {
        board[nexty][nextx].num_pieces = board[y][x].num_pieces;
        board[y][x].num_pieces = 0;
        board[nexty][nextx].stack=board[y][x].stack;
        board[y][x].stack=0;
    }
    struct piece* temp=board[y][x].stack;

    while(temp->next!=0){
        temp=temp->next;
    }
    temp->next=board[nexty][nextx].stack;
    board[nexty][nextx].stack=board[y][x].stack;
    board[y][x].stack=0;

    board[nexty][nextx].num_pieces+=board[y][x].num_pieces;
    board[y][x].num_pieces=0;






}
