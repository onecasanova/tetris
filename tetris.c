/*

tetris game

*/

//first start with static board in the terminal

#include <ncurses.h> //drawing to the terminal
#include <stdlib.h> //general utilities


//define board dimensions
#define ROWS 20
#define COLS 10


//2D array of integers to represent the board data
int board[ROWS][COLS]; //all values start at zero automatically for a newly created array. the rows and cols just speciy dimensions


void draw_board() {

    
}


int main() {
    initscr(); //initialize ncurses to take ove terminal
    noecho(); //stops typed keys from appearing on screen
    curs_set(0); //removes blinking cursor



    return 0;
}








