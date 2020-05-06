//
// Created by Pearse Frost on 20/04/2020.
//
//Includes libraries necessary
#include <stdio.h>
#include "game_functions.h"
#include"input_output.h"
#include <stdlib.h>

void gameloop(square board[BOARD_SIZE][BOARD_SIZE],player players[PLAYERS_NUM]){//Function used to take users input for what piece they want to move,where they want move it etc.
   int count=0;//Sets integer count to 0
   int winnerFound=0;//Sets integer winnerFound to 0
    while(winnerFound==0){//While there isn't a winner found in the game
        if(count%2==0) {//Begins the game with player 1's turn
            printf("Player1 turn");//Prints Player1 turn
            printPlayerInfo(players, count % 2);//Includes function from input_output.c which contains all the player info
            print_board(board);//Prints the board
            int x, y,switchCase;//Declares variables we need to use
            move direct;//Calls the enum from game_init.h and names it direct
            if(players[count%2].num_reserved>0 && players[count%2].num_controlled>0){//If statement for when a player has pieces reserved and controlled
                do {
                    printf("Do you want to:\n 1.Move a stack, 2.Place a reserved piece");//Prints would like to move a current stack on the board or place a reserved piece
                    scanf("%d", &switchCase);//Scans their input
                }while(switchCase!=1||switchCase!=2);//Only runs while input is 1 or 2
                   }else if(players[count%2].num_reserved>0){
                       switchCase=2;
                   }else{
                       switchCase=1;
                   }
                   do {//Do loop asks the co-ordinates of the piece the user would like to move while the co-oridnate is less than7 and greater than 0
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
                            board[y][x].stack->p_color != players[count % 2].player_color);//Also only runs when the square is valid,when there is one or more pieces
                            // on that square and the color on top of the stack is the player moving its color
                   int newx, newy;
                   switch(switchCase) {
                       case 1://Case one it moves a current piece on the board

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
                           }while(newx<0||newx>7||newy<0||newy>7||board[newy][newx].type==INVALID);//Asks user to move piece while newx and newy lie outside the limits and while the square is invalid




                           movepiece(board, x, y, newx, newy, players, count % 2);//Includes function that is used to move the pieces
                           break;


                       case 2://Lets the user place a reserved piece
                           placeReserved(board,players,count%2,x,y);

                           break;
                   }
                   if(players[(count+1)%2].num_controlled==0 && players[(count+1)%2].num_reserved==0){//If player has no captured and reserved pieces left
                       winnerFound=1;//Winner is found
                       printf("Player %d has won\nWinners info is: ",count%2);
                       printPlayerInfo(players,count%2);//Prints player info
                   }

               }

               if(count%2==1){//Switches to player 2's turn
                   printf("Player2 turn");//Prints player 2's turn
                   printPlayerInfo(players, count % 2);//Use player info function to print the players info
                   print_board(board);//Prints player info
                   int x, y,switchCase;//Declaration of the variables needed
                   move direct;//Calls the enum from in game_init and names it direct
                   if(players[count%2].num_reserved>0 && players[count%2].num_controlled>0){//If player still have pieces reserved and controlled
                       do {
                           printf("Do you want to:\n 1.Move a stack, 2.Place a reserved piece");//Asks if they would like to move a current piece or a reserved piece
                           scanf("%d", &switchCase);//Scans the users input as switchCase
                       }while(switchCase!=1||switchCase!=2);//Only runs while the users input is 1 or 2
                   }else if(players[count%2].num_reserved>0){//If no. of reserved pieces is greater than zero
                       switchCase=2;//switchCase is automatically 2
                   }else{//If they dont fall under any of the other if statements
                       switchCase=1;//switchCase is automatically 1
                   }
                   do {
                       printf("Choose the co-ordinates of the piece you would like to move\n");
                       do {
                           printf("x co-oridnate: ");
                           scanf(" %d", &x);
                       } while (x < 0 || x > 7);//Asks for x co-ordinate of the piece they want to move while x is greater than 0 and less than 7
                       do {
                           printf("y co-ordinate: ");
                           scanf(" %d", &y);
                       } while (y < 0 || y > 7);//Asks for x co-ordinate of the piece they want to move while x is greater than 0 and less than 7
                   } while (board[y][x].type == INVALID || board[y][x].num_pieces < 1 ||
                            board[y][x].stack->p_color != players[count % 2].player_color);//Also only runs when the square is valid,when there is one or more pieces
                   // on that square and the color on top of the stack is the player moving its color
                   int newx, newy;
                   switch(switchCase) {
                       case 1://If user chooses 1,they move a current piece on the board

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
                           }while(newx<0||newx>7||newy<0||newy>7||board[newy][newx].type==INVALID);//Asks user to move piece while newx or newy lie outside the limits or while the square is invalid




                           movepiece(board, x, y, newx, newy, players, count % 2);//Includes function to actually move pieces
                           break;//Breaks


                       case 2:
                           placeReserved(board,players,count%2,x,y);//Includes function to place a reserved piece

                           break;//Breaks
                   }
                   if(players[(count+1)%2].num_controlled==0 && players[(count+1)%2].num_reserved==0){//If player has no captured and reserved pieces left
                       winnerFound=1;//Winner is found
                       printf("Player %d has won\nWinners info is: ",count%2);
                       printPlayerInfo(players,count%2);//Prints info of the winner
                   }

               }
               count++;//Increases count by one
           }
}
 void movepiece(square board[BOARD_SIZE][BOARD_SIZE],int x, int y,int nextx,int nexty,struct player players[PLAYERS_NUM],int player_no) {//Function used to actually move the pieces


     if (board[nexty][nextx].num_pieces == 0) {//If there is no pieces on the next square
         board[nexty][nextx].num_pieces = board[y][x].num_pieces;//No. of pieces on the next square is equal to no.of pieces on current square
         board[y][x].num_pieces = 0;//No. of pieces on current square then points to zero
         board[nexty][nextx].stack = board[y][x].stack;//Top piece on stack of next square is equal to top piece of current square
         board[y][x].stack = 0;//There are no pieces on top of our current stack so it points to zero
     } else {
         struct piece *temp = board[y][x].stack;//Points temp to stack at y x

         while (temp->next != 0) {//While next value in linked list does not point to 0
             temp = temp->next;//Temp points to next value
         }
         temp->next = board[nexty][nextx].stack;
         board[nexty][nextx].stack = board[y][x].stack;
         board[y][x].stack = 0;//Points next to the next stack on board and points the current stack to 0

         board[nexty][nextx].num_pieces += board[y][x].num_pieces;
         board[y][x].num_pieces = 0;//Adds the no. of pieces from the last square with the next and puts no. of pieces of last square equal 0

         if(board[nexty][nextx].num_pieces>5){//If no. of pieces less than 0
             for(int i=board[nexty][nextx].num_pieces - 5;i>0;i--){//For loop that runs until i=0 and decreases by one every time it runs
                 struct piece *current=board[nexty][nextx].stack;//Current points to next stack
                 struct piece *previous;//Creates pointer called previous
                 while(current->next!=0){//While the next element in the linked list points to 0
                     previous=current;//Previous becomes  current
                     current=current->next;//Current points to next element in linked list
                 }
                 if(current->p_color==players[player_no].player_color){//If the color of current is the players color
                     players[player_no].num_reserved++;//Increase no. of reserved by one
                 }else{//Otherwise
                     players[player_no].num_captured++;//Increase no. of captured by one
                 }
                 free(current);//De-allocates the memory used by current
                 previous->next=0;//Previous points to next

             }
             board[nexty][nextx].num_pieces=5;//Next square has 5 pieces on it
         }

     }
 }
 void findCord(int *x,int *y,move direct){//Function used to sort the directions
     if (direct == UP) {
         *y=*y-1;//Moves the chosen piece up by decreasing the y co-ordinate
     } else if (direct == DOWN) {
         *y=*y+1;//Moves the chosen piece down by increasing the y co-ordinate
     } else if (direct == LEFT) {
         *x=*x-1;//Moves chosen piece to left by decreasing the x co-ordinate
     } else if (direct == RIGHT) {
         *x=*x+1;//Moves choosen piece to right by increasing the x co-ordinate
     }
}
void placeReserved(square board[BOARD_SIZE][BOARD_SIZE],player players[PLAYERS_NUM],int player_no,int x,int y){//Function used to place a reserved piece
    players[player_no].num_reserved--;//Decreases number of reserved by the player by one if they use a reserved piece
    if(board[y][x].stack->p_color!=players[player_no].player_color){//If the color of the piece on top of stack is not the players
        players[player_no].num_controlled++;//Increase no. of controlled by one
        players[(player_no+1)%2].num_controlled--;//Decrease the other players no. of controlled by one
    }
    piece* addPiece=(piece*)malloc(sizeof(piece));//Allocates memory to addPiece
    addPiece->next=0;//addPiece points to next element which points to zero
    addPiece->p_color=players[player_no].player_color;//

    piece* temp=0;//Pointer temp equal 0
    temp=board[y][x].stack;//temp equal to stack on y x
    board[y][x].stack=addPiece;//stack at y x is now equal to addPiece
    board[y][x].stack->next=temp;//stack at y x now points to next element which equals temp

    if(board[y][x].num_pieces==5){//If no.of pieces on a certain stack is equal to 5
        if(board[y][x].stack->next->next->next->next->next->p_color==players[player_no].player_color){//If the last piece on the stack is equal to players color
            players[player_no].num_reserved++;//Increases no. of reserved pieces by one
        }else{//If not players color
            players[player_no].num_captured++;//Increases no. of captured pieces by one
        }
        free(board[y][x].stack->next->next->next->next->next);//De-allocates memory used by the stack
        board[y][x].stack->next->next->next->next=0;

    }else{
        board[y][x].num_pieces++;//Increases the no. of pieces on that square by one
    }
}
