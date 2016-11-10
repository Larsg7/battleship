/**
 * Battleship game - solution to problem 3 of sheet 4
 *
 * to complile:
 * cd build
 * cmake .. && make
 *
 * or
 *
 * g++ src/*.cpp inc/*.h -lncurses -std=c++11
 *
 * Controls:
 */

#include <ncurses.h>
#include <iostream>

#include "../inc/Board.h"
#include "../inc/Game.h"
#include "../inc/Error.h"

int main ()
{
    initscr();              // Initialise ncurses
    noecho();               // Don't echo input
    cbreak();               // Line buffering disabled. pass on everything
    keypad( stdscr, TRUE ); // Let ncurses interpret arrow keys

    try
    {
        Board* b = new Board ( 10, 10, stdscr );
        Game* g = new Game ( b );
        g->run();
    }
    catch ( const Error& e )
    {
        endwin();
        std::cerr << "Oops, an Error occurred: " << e.what() << std::endl;
        return 1;
    }
    catch ( ... )
    {
        endwin();
        std::cerr << "Oops, an unknown Error occurred!" << std::endl;
        return 2;
    }

    endwin();   // end ncurses

    return 0;
}