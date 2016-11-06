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
    keypad(stdscr, TRUE);   // let ncurses interpret arrow keys

    try
    {
        Board* b = new Board ( 10, 10, stdscr );
        Game g ( b );
        g.run();
    }
    catch ( const Error& e )
    {
        endwin();
        std::cerr << "Oops, an Error occurred: " << e.what() << std::endl;
        return 1;
    }


    endwin();   // end ncurses

    return 0;
}