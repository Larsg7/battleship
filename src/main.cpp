#include <ncurses.h>
#include <iostream>

#include "../inc/Board.h"
#include "../inc/Game.h"

int main ()
{
    initscr();              // Initialise ncurses
    noecho();               // Don't echo input
    cbreak();               // Line buffering disabled. pass on everything
    keypad(stdscr, TRUE);   // let ncurses interpret arrow keys

    Board* b = new Board ( 10, 10, stdscr );
    Game g ( b );
    g.run();

    endwin();   // end ncurses

    return 0;
}