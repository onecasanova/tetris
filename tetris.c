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
    mvprintw(0, 1 + COLS, "+"); //top right corner


    //rows, so the middle part
    for (int r = 0; r < ROWS; r++) {
        mvprintw(r + 1, 0, "|"); //LHS. use r + 1 because the top row is taken already
        for (int c = 0; c < COLS; c++) {
            //if the value at board[r][c] is non-zero, then print a block
            if (board[r][c]) {
                mvprintw(r + 1, 1 + c*2, "[]");
            }
            else { //otherwise it is empty. initially all values are zero so it will print the spaces. Note they are double spaces
                mvprintw(r + 1, 1 + c*2, "  ");
            }
        }
        mvprintw(r + 1, 1 + COLS*2, "|"); //RHS
    }


    //bottom border, similar to top
    /*
    Note: use "ROWS + 1" because the game spave will use up to ROWS max value so the bottom border should right outside
    of that at ROWS + 1.    
    */

    mvprintw(ROWS + 1, 0, "+"); //bottom left
    //loop over the COL values and print "--"
    for (int c = 0; c < COLS; c++){
        mvprintw(ROWS + 1, 1 + c*2, "--"); //double because tetris blocks will be [] (two characters)
    }
    mvprintw(ROWS + 1, 1 + COLS, "+"); //bottom right corner


}


int main() {
    initscr(); //initialize ncurses to take ove terminal
    noecho(); //stops typed keys from appearing on screen
    curs_set(0); //removes blinking cursor

    draw_board(); //draw the board
    
    //print everything all at once on the terminal. ncurses puts all the stuff we defined in
    //draw_board() in a buffer in memory, and refresh() sends it all to the terminal at once.
    refresh();

    //waits for any key to be pressed. It's a waiting function, otherwise 
    //the program would immediately draw the board and exit before I could see it.
    getch(); 
    endwin();  //shuts down ncurses, returns terminal back to normal

    return 0;
}








