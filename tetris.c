/*

tetris game

*/

//first start with static board in the terminal

#include <ncurses.h> //drawing to the terminal
#include <stdlib.h> //general utilities
#include <time.h> //time library


//define board dimensions
#define ROWS 24
#define COLS 12
#define PCS 7
#define G_TIME 0.5 //seconds

//score
int score = 0;

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
    
    //display score
    mvprintw(0, 4 + COLS*2, "score: %d", score);


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

//function to detect collisions
int collision(int p_row, int p_col, int type) {
    //p_row is proposed row
    //p_col is proposed column

    //loop through 4x4 piece grid
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (shapes[type][i][j] == 1) { //if filled
                //collision conditions, return 1 if any are true
                if (p_row + i < 0 || p_row + i > ROWS - 1) {
                    return 1;
                }
                else if (p_col + j < 0 || p_col + j > COLS -1) {
                    return 1;
                }
                //check if board is already occupied
                else if (board[p_row + i][p_col + j]) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

void lock_piece(){
    //loop through 4x4 shape array. Very similar to draw peice, but we write to the board permanently now.
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            //if shape array val is 1
            if (shapes[current.type][i][j]){
                board[current.row + i][current.col + j] = 1;
            }
        }
    }
}

void spawn_piece() {

    current.type = (rand() % PCS);
    // current.type = 2;
    current.row = 0;
    current.col = COLS/2 - 2;

}

void line_clear() {
    //loop through rows, find a full one
    int n = 0;
    for (int r = ROWS-1; r >=  0; r--) { //start from bottom rows
        int k = 1; //bool to detect full row
        for (int c = 0; c < COLS; c++) {
            //if the value at board[r][c] is non-zero, then do nothing, otherwise 
            if (!board[r][c]) {
                k = 0;
                break;
            }
        }

        //if full then shift rows and clear top one
        if (k) {
            for (int rr = r; rr > 0; rr--) {
                for (int c = 0; c < COLS; c++) {
                    board[rr][c] = board[rr-1][c];
                    }
                }
                //clear top row
                for (int c = 0; c < COLS; c++) {
                    board[0][c] = 0;
                }
            n +=1;
            r++; //re-check new "current" row on next iteration
        }
    }

    //add score based on how many lines cleared
    switch (n) {
        case 0: 
            score += 0;
            break;
        case 1:
            score += 100;
            break;
        case 2:
            score += 300;
            break;
        case 3:
            score += 500;
            break;
        case 4:
            score += 800;
            break;
    }
}

void transpose() {
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            int temp = shapes[current.type][i][j];
            shapes[current.type][i][j] = shapes[current.type][j][i];
            shapes[current.type][j][i] = temp;
        }
    }
}


void reverse_r() {
    //copy array
    int temp[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            temp[i][j] = shapes[current.type][i][j];
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            shapes[current.type][i][j] = temp[3-i][j];
        }
    }
}

void reverse_c() {
    //copy array
    int temp[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            temp[i][j] = shapes[current.type][i][j];
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            shapes[current.type][i][j] = temp[i][3-j];
        }
    }
}

void rotate_cclock() {
    //rotate a piece clockwise
    transpose();
    reverse_r();
}

void rotate_clock() {
    //rotate a piece counter clockwise
    reverse_r();
    transpose();
}

void game_over() {
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x); // Get terminal dimensions

    clear(); // Clear the current game screen

    // mvprintw(y, x, format, ...)
    // Centering the text on the screen:
    mvprintw(max_y / 2, (max_x - 10) / 2, "GAME OVER");
    mvprintw(max_y / 2 + 1, (max_x - 18) / 2, "Final Score: %d", score);
    mvprintw(max_y / 2 + 3, (max_x - 26) / 2, "Press any key to exit...");

    refresh(); // Push changes to the actual terminal
    getch();   // Wait for user input before closing
}

int main() {
    initscr(); //initialize ncurses to take ove terminal
    noecho(); //stops typed keys from appearing on screen
    curs_set(0); //removes blinking cursor
    keypad(stdscr, TRUE); //enable arrow key detection
    nodelay(stdscr, TRUE); //makes getch() non-blocking so it deosn't stop the program when waiting for a key press

    //random seed
    srand(time(NULL));

    //define piece
    current.type = rand() % 7;
    current.row = 0;
    current.col = 0;

    //game loop

    clock_t last_drop_t = clock(); //get initial clock time before loop

    while (true) {

        
            
        //Gravity
        clock_t now = clock(); //get time right now
        double elapsed = (double)(now - last_drop_t) / CLOCKS_PER_SEC; //put (double) to divide with floating point precision, add CLOCKS_PER_SEC to convert the delta_t to seconds
        if (elapsed > G_TIME) {
            //I piece is length 4
            if (!collision(current.row + 1, current.col, current.type)) {
                current.row += 1;
            }

            else {
                lock_piece();
                line_clear();
                spawn_piece();
                if (collision(current.row, current.col, current.type)) {
                    //print game over screen
                    game_over();
                    break;
                }
            }   
            last_drop_t = now; //update time

        }
        //check for keyboard input
        int ch = getch();

        //update piece position after input
        switch (ch) {
            case KEY_LEFT:
                //move piece left
                if (!collision(current.row, current.col - 1, current.type)) {
                    current.col -= 1;
                }
                break;
            case KEY_RIGHT:
                //for pieces with width = 2
                if (!collision(current.row, current.col + 1, current.type)) {
                    current.col += 1;
                }
                break;

            //this key up and down will be removed for the real game.
            case KEY_UP:
                if (!collision(current.row - 1, current.col, current.type)) {
                    // current.row -= 1;
                    rotate_clock();
                } 
                break;
            case KEY_DOWN:
                if (!collision(current.row + 1, current.col, current.type)) {
                    // current.row += 1;
                    rotate_cclock();
                }
                break;
            case ' ':
                if (!collision(current.row + 1, current.col, current.type)) {
                    // current.row += 1;
                    current.row += 1;
                }
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
    endwin();

}








