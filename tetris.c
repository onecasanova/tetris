/*

tetris game

*/

//first start with static board in the terminal

#include <ncurses.h> //drawing to the terminal
#include <stdlib.h> //general utilities


//define board dimensions
#define ROWS 24
#define COLS 12
#define PCS 7

//2D array of integers to represent the board data
int board[ROWS][COLS]; //all values start at zero automatically for a newly created array. the rows and cols just speciy dimensions

//3D array for pieces
int shapes[PCS][4][4] = {
    //square
    {
    {0, 0, 0, 0},
    {1, 1, 0, 0},
    {1, 1, 0, 0},
    {0, 0, 0, 0}},

    //T piece
    {
    {0, 0, 0, 0},
    {0, 1, 0, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 0}
    },

    //I piece
    {
    {1, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 0, 0, 0}
    },

    //S piece
    {
    {0, 0, 0, 0},
    {0, 1, 1, 0},
    {1, 1, 0, 0},
    {0, 0, 0, 0}
    },

    //Z piece
    {
    {0, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0}
    },

    //L piece
    {
    {1, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 0, 0, 0}
    },

    //J piece
    {
    {0, 1, 0, 0},
    {0, 1, 0, 0},
    {1, 1, 0, 0},
    {0, 0, 0, 0}
    },

};

//struct for piece information
struct Piece {
    int type;
    int row;
    int col;
    int rot;
};

//define global struct, so functions can access this current falling piece
struct Piece current;


void draw_piece(){

    //loop through 4x4 shape array
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            //if shape array val is 1
            if (shapes[current.type][i][j]){
                mvprintw(current.row + i + 1, (current.col + j)*2 + 1, "[]");
            }
        }
    }

}

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
    mvprintw(0, 1 + COLS*2, "+"); //top right corner


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
    Note: use "ROWS + 1" because the game space will use up to ROWS max value so the bottom border should right outside
    of that at ROWS + 1.    
    */

    mvprintw(ROWS + 1, 0, "+"); //bottom left
    //loop over the COL values and print "--"
    for (int c = 0; c < COLS; c++){
        mvprintw(ROWS + 1, 1 + c*2, "--"); //double because tetris blocks will be [] (two characters)
    }
    mvprintw(ROWS + 1, 1 + COLS*2, "+"); //bottom right corner


}


int main() {
    initscr(); //initialize ncurses to take ove terminal
    noecho(); //stops typed keys from appearing on screen
    curs_set(0); //removes blinking cursor
    keypad(stdscr, TRUE); //enable arrow key detection
    nodelay(stdscr, TRUE); //makes getch() non-blocking so it deosn't stop the program when waiting for a key press


    //define piece
    current.type = 2;
    current.row = 0;
    current.col = 0;

    //game loop
    while (true) {
        
        //check for keyboard input
        int ch = getch();

        //update piece position after input
        switch (ch) {
            case KEY_LEFT:
                //move piece left
                current.col -= (current.col - 1 >= 0) ? 1 : 0; //use terinary operateor "condition ? expression_if_true : expression_if_false;"
                break;
            case KEY_RIGHT:
                //for pieces with width = 2
                if (current.type == 0 || current.type == 5 || current.type == 6){
                    current.col += (current.col < (COLS - 2)) ? 1 : 0;
                }
                //I piece
                else if (current.type == 2){
                    current.col += (current.col < (COLS - 1)) ? 1 : 0;
                }
                //pieces with width = 3
                else {
                    current.col += (current.col < (COLS - 3)) ? 1 : 0;
                }
                
                break;
            case KEY_UP:
                current.row -= 1; 
                break;
            case KEY_DOWN:
                current.row += 1;
                break;

            //quit
            case 'q':
                endwin(); //shuts down ncurses, returns terminal back to normal
                return 0;

        }

        //redraw board and piece
        draw_board();
        draw_piece();

    //print everything all at once on the terminal. ncurses puts all the stuff we defined in
    //draw_board() in a buffer in memory, and refresh() sends it all to the terminal at once.
    refresh();

    }

}








