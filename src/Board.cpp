//
// Created by lars on 11/4/16.
//

#include <sstream>
#include <iostream>

#include "../inc/Board.h"
#include "../inc/Error.h"

using namespace std;

Board::Board ( unsigned int x, unsigned int y, WINDOW* win )
    : x_dim ( x ), y_dim ( y ), window ( win ), board ( y_dim ),
      vSpace ( 1 )
{
    // set some cosmetics
    fieldSeparate = "  ";  // horizontal separation of fields
    fieldFree     =  ".";  // symbol for a filed where you can shoot
    fieldFail     =  "x";  // sysmbol for a filed where you missed
    fieldSuccess  =  "o";  // sysmbol for a field where you hit a ship

    // build vector *board*
    // remember x are the columns and y the rows
    for (int row = 0; row < y_dim; ++row)
    {
        // initialise row vector
        board[row] = vector<string> ( x_dim );
        for (int col = 0; col < x_dim; ++col)
        {
            //cout << "row: " << row << ", col: " << col << endl;
            board[row][col] = fieldFree;
        }
    }
}

void Board::draw ()
{
    // first get maximal dimensions of window
    int maxX, maxY;
    getmaxyx( window, maxY, maxX );

    // starting pos
    int startX ( (maxX - x_dim * ( (int)fieldSeparate.length() + 1 ) - 1)/2 );
    int startY ( (maxY - y_dim - 1)/2 );

    // draw the first line with numbers
    // TODO: after 10 we need less space between numbers
    vector<string> firstLine ( x_dim + 1 );
    firstLine[0] = " ";
    for ( int i = 1; i < firstLine.size(); ++i ) {
        firstLine[i] = to_string(i);
    }
    mvprintw( startY, startX, "%s", print_vector( firstLine, fieldSeparate ).c_str() );

    // draw the board onto the window
    for (unsigned int row = 0; row < board.size(); ++row) {
        mvprintw ( startY + vSpace * row + 1, startX, "%c%s", (const char)('A' + row), fieldSeparate.c_str() );
        printw ( "%s", print_vector( board[row], fieldSeparate ).c_str() );
    }
}

template <typename T>
string Board::print_vector ( const vector<T>& vector, const string& separate ) const
{
    // use streams as they are heavily overloaded
    stringstream finalStrStr;

    for (int i = 0; i < vector.size(); ++i) {
        finalStrStr << vector[i] << separate;
    }

    return finalStrStr.str();
}