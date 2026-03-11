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
    /*
    board will be a box so I'll define it in 3 parts: top, middle, and bottom
    */
    //top "+-----...-----+"
    mvprintw(0, 0, "+"); //top left
    //loop over the COL values and print "--"
    for (int c = 0; c < COLS; c++){
        mvprintw(0, 1 + c*2, "--"); //double because tetris blocks will be [] (two characters)
    }
    mvprintw(0, 1 + COLS, "+"0); //top right corner



}


int main() {
    initscr(); //initialize ncurses to take ove terminal
    noecho(); //stops typed keys from appearing on screen
    curs_set(0); //removes blinking cursor



    return 0;
}








