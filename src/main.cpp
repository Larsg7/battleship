#include <ncurses.h>

#include "../inc/Board.h"

int main ()
{
    initscr();

    Board b ( 10, 10, stdscr );
    b.draw();
    //printw("%s", "test");
    refresh();
    getch();
    endwin();

    return 0;
}