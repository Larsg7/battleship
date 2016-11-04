//
// Created by lars on 11/4/16.
//

#include "../inc/Board.h"

using namespace std;

Board::Board ( unsigned int x, unsigned int y, WINDOW* win )
    : x_dim ( x ), y_dim ( y ), window ( win )
{
    // build vector *board*
    string separate      ( "  " );
    string fieldFree      ( "." );
    string fieldFail      ( "x" );
    string fieldSuccess   ( "o" );

    // start with the first row
    board[0][0] = " " + separate;
    for (int i = 0; i < x_dim; ++i) {
        board[0][i] = to_string(i) + separate;
    }

    // now all the other rows
}

void Board::draw ()
{
    // first get maximal dimensions of window
    int maxX, maxY;
    getmaxyx( window, maxY, maxX );
    
    // set some variables which will define the look of the board:


    
    // draw the board onto the window
    for (int i = 0; i < ; ++i) {
        
    }
}