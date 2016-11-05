#include <ncurses.h>
#include <iostream>

#include "../inc/Board.h"

int main ()
{
    initscr();              // Initialise ncurses
    noecho();               // Don't echo input
    cbreak();               // Line buffering disabled. pass on everything
    keypad(stdscr, TRUE);   // let ncurses interpret arrow keys

    int ch;
    Board b ( 10, 10, stdscr );
    b.draw();
    refresh();
    //getch();

    while ( ( ch = getch() ) != KEY_F(2) )
    {
        b.user_move_cursor( ch );
        //std::cout << "you pressed " << ch << std::endl;
    }
    //printw("%s", "test");

    endwin();   // end ncurses

    return 0;
}