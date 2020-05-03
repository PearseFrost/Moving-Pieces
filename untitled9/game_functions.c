//
// Created by Pearse Frost on 20/04/2020.
//
#include <stdio.h>
#include "game_functions.h"
#include"input_output.h"
#include <stdlib.h>

void gameloop(square board[BOARD_SIZE][BOARD_SIZE],player players[PLAYERS_NUM]){
   int count=0;
   int winnerFound=0;
           while(winnerFound==0){
               if(count%2==0) {
                   printf("Player1 turn");
                   printPlayerInfo(players, count % 2);
                   print_board(board);
                   int x, y,switchCase;
                   move direct;
                   if(players[count%2].num_reserved>0 && players[count%2].num_controlled>0){
                       do {
                           printf("Do you want to:\n 1.Move a stack, 2.Place a reserved piece");
                           scanf("%d", &switchCase);
                       }while(switchCase!=1||switchCase!=2);
                   }else if(players[count%2].num_reserved>0){
                       switchCase=2;
                   }else{
                       switchCase=1;
                   }
                   do {
                       printf("Choose the co-ordinates of the piece you would like to move\n");
                       do {
                           printf("x co-oridnate: ");
                           scanf(" %d", &x);
                       } while (x < 0 || x > 7);
                       do {
                           printf("y co-ordinate: ");
                           scanf(" %d", &y);
                       } while (y < 0 || y > 7);
                   } while (board[y][x].type == INVALID || board[y][x].num_pieces < 1 ||
                            board[y][x].stack->p_color != players[count % 2].player_color);
                   int newx, newy;
                   switch(switchCase) {
                       case 1:

                           do {
                               newx = x;
                               newy = y;
                               printf("What way would you like to move:\n");
                               for (int i = board[y][x].num_pieces; i > 0; i--) {
                                   printf("1=RIGHT, 2=LEFT, 3=UP, 4=DOWN : ");
                                   scanf("%d", &direct);
                                   direct--;
                                   findCord(&newx, &newy, direct);
                               }
                           }while(newx<0||newx>7||newy<0||newy>7||board[newy][newx].type==INVALID);




                           movepiece(board, x, y, newx, newy, players, count % 2);
                           break;


                       case 2:
                           placeReserved(board,players,count%2,x,y);

                           break;
                   }
                   if(players[(count+1)%2].num_controlled==0 && players[(count+1)%2].num_reserved==0){
                       winnerFound=1;
                       printf("Player %d has won\nWinners info is: ",count%2);
                       printPlayerInfo(players,count%2);
                   }

               }

               if(count%2==1){
                   printf("Player2 turn");
                   printPlayerInfo(players, count % 2);
                   print_board(board);
                   int x, y,switchCase;
                   move direct;
                   if(players[count%2].num_reserved>0 && players[count%2].num_controlled>0){
                       do {
                           printf("Do you want to:\n 1.Move a stack, 2.Place a reserved piece");
                           scanf("%d", &switchCase);
                       }while(switchCase!=1||switchCase!=2);
                   }else if(players[count%2].num_reserved>0){
                       switchCase=2;
                   }else{
                       switchCase=1;
                   }
                   do {
                       printf("Choose the co-ordinates of the piece you would like to move\n");
                       do {
                           printf("x co-oridnate: ");
                           scanf(" %d", &x);
                       } while (x < 0 || x > 7);
                       do {
                           printf("y co-ordinate: ");
                           scanf(" %d", &y);
                       } while (y < 0 || y > 7);
                   } while (board[y][x].type == INVALID || board[y][x].num_pieces < 1 ||
                            board[y][x].stack->p_color != players[count % 2].player_color);
                   int newx, newy;
                   switch(switchCase) {
                       case 1:

                           do {
                               newx = x;
                               newy = y;
                               printf("What way would you like to move:\n");
                               for (int i = board[y][x].num_pieces; i > 0; i--) {
                                   printf("1=RIGHT, 2=LEFT, 3=UP, 4=DOWN : ");
                                   scanf("%d", &direct);
                                   direct--;
                                   findCord(&newx, &newy, direct);
                               }
                           }while(newx<0||newx>7||newy<0||newy>7||board[newy][newx].type==INVALID);




                           movepiece(board, x, y, newx, newy, players, count % 2);
                           break;


                       case 2:
                           placeReserved(board,players,count%2,x,y);

                           break;
                   }
                   if(players[(count+1)%2].num_controlled==0 && players[(count+1)%2].num_reserved==0){
                       winnerFound=1;
                       printf("Player %d has won\nWinners info is: ",count%2);
                       printPlayerInfo(players,count%2);
                   }

               }
               count++;
           }
}
 void movepiece(square board[BOARD_SIZE][BOARD_SIZE],int x, int y,int nextx,int nexty,struct player players[PLAYERS_NUM],int player_no) {


     if (board[nexty][nextx].num_pieces == 0) {
         board[nexty][nextx].num_pieces = board[y][x].num_pieces;
         board[y][x].num_pieces = 0;
         board[nexty][nextx].stack = board[y][x].stack;
         board[y][x].stack = 0;
     } else {
         struct piece *temp = board[y][x].stack;

         while (temp->next != 0) {
             temp = temp->next;
         }
         temp->next = board[nexty][nextx].stack;
         board[nexty][nextx].stack = board[y][x].stack;
         board[y][x].stack = 0;

         board[nexty][nextx].num_pieces += board[y][x].num_pieces;
         board[y][x].num_pieces = 0;

         if(board[nexty][nextx].num_pieces>5){
             for(int i=board[nexty][nextx].num_pieces - 5;i>0;i--){
                 struct piece *current=board[nexty][nextx].stack;
                 struct piece *previous;
                 while(current->next!=0){
                     previous=current;
                     current=current->next;
                 }
                 if(current->p_color==players[player_no].player_color){
                     players[player_no].num_reserved++;
                 }else{
                     players[player_no].num_captured++;
                 }
                 free(current);
                 previous->next=0;

             }
             board[nexty][nextx].num_pieces=5;
         }

     }
 }
 void findCord(int *x,int *y,move direct){
     if (direct == UP) {
         *y=*y-1;
     } else if (direct == DOWN) {
         *y=*y+1;
     } else if (direct == LEFT) {
         *x=*x-1;
     } else if (direct == RIGHT) {
         *x=*x+1;
     }
}
void placeReserved(square board[BOARD_SIZE][BOARD_SIZE],player players[PLAYERS_NUM],int player_no,int x,int y){
    players[player_no].num_reserved--;
    if(board[y][x].stack->p_color!=players[player_no].player_color){
        players[player_no].num_controlled++;
        players[(player_no+1)%2].num_controlled--;
    }
    piece* addPiece=(piece*)malloc(sizeof(piece));
    addPiece->next=0;
    addPiece->p_color=players[player_no].player_color;

    piece* temp=0;
    temp=board[y][x].stack;
    board[y][x].stack=addPiece;
    board[y][x].stack->next=temp;

    if(board[y][x].num_pieces==5){
        if(board[y][x].stack->next->next->next->next->next->p_color==players[player_no].player_color){
            players[player_no].num_reserved++;
        }else{
            players[player_no].num_captured++;
        }
        free(board[y][x].stack->next->next->next->next->next);
        board[y][x].stack->next->next->next->next=0;

    }else{
        board[y][x].num_pieces++;
    }
}
