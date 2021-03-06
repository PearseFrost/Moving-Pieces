//
// Created by Pearse Frost on 27/03/2020.
//

#include <stdio.h>
#include "input_output.h"

/* FUnction to print the board:
 * Invalid Squares are printed as | - |
 * Valid empty squares are printed as |   |
 * Valid squares with a GREEN piece are printed as | G |
 * Valid squares with a RED piece are printed as | R | */

void print_board(square board[BOARD_SIZE][BOARD_SIZE]){//Function to print the board
    printf("****** The Board ******\n");
    for(int i = 0; i < BOARD_SIZE; i ++){
        for (int j = 0; j < BOARD_SIZE; j++){
            if(board[i][j].type == VALID) {
                if (board[i][j].stack == NULL)
                    printf("|   ");
                else {
                    if (board[i][j].stack->p_color == GREEN)
                        printf("| G ");
                    else if (board[i][j].stack->p_color == RED)
                        printf("| R ");
                    else {
                        printf("| E");
                    }
                }
                if (board[i][j].num_pieces > 1) {
                    if (board[i][j].stack->next->p_color == GREEN) {
                        printf("G");
                    } else if (board[i][j].stack->next->p_color == RED) {
                        printf("R");
                    } else {
                        printf("E");
                    }
                }
                if (board[i][j].num_pieces > 2) {
                    if (board[i][j].stack->next->next->p_color == GREEN) {
                        printf("G");
                    } else if (board[i][j].stack->next->next->p_color == RED) {
                        printf("R");
                    } else {
                        printf("E");
                    }
                }
                if (board[i][j].num_pieces > 3) {
                    if (board[i][j].stack->next->next->next->p_color == GREEN) {
                        printf("G");
                    } else if (board[i][j].stack->next->next->next->p_color == RED) {
                        printf("R");
                    } else {
                        printf("E");
                    }
                }
                if (board[i][j].num_pieces > 4) {
                    if (board[i][j].stack->next->next->next->next->p_color == GREEN) {
                        printf("G");
                    } else if (board[i][j].stack->next->next->next->next->p_color == RED) {
                        printf("R");
                    } else {
                        printf("E");
                    }
                }
            }

            else
                printf("| - ");
        }
        printf("|\n");
    }
}
void printPlayerInfo(struct player players[PLAYERS_NUM],int player_no){//Function to print player information

    printf("\nPlayers name is :%s\n",players[player_no].name);//Prints name user inputed
    printf("No. of controlled stacks :%d\n",players[player_no].num_controlled);//Prints no. of controlled stacks that player has
    printf("No. of reserved pieces :%d\n",players[player_no].num_reserved);//Prints no. of reserved pieces that player has
    printf("No of captured pieces :%d\n",players[player_no].num_captured);//Prints no. of reserved pieces that player has


}