//
// Created by lars on 11/4/16.
//

#ifndef BATTLESHIP_BOARD_H
#define BATTLESHIP_BOARD_H

#include <ncurses.h>
#include <vector>
#include <string>

/**
 * class which is responsible for drawing the board
 */
class Board
{
public:
    /**
     * constructor
     * @param x x dimension of board
     * @param y y dimension of board
     * @param win window to draw on
     */
    Board ( unsigned int x, unsigned int y, WINDOW* win )
            : x_dim ( x ), y_dim ( y ), window ( win )
    {}

    /**
     * function to draw the actual board onto window
     */
    void draw ();

private:
    /** x dimension of the board */
    const unsigned int x_dim;
    /** y dimension of the board */
    const unsigned int y_dim;
    /** window to draw on */
    WINDOW* window;
    /** vector holding all information about the board */
    std::vector<std::vector<std::string>> board;
    /** variables which define the look of the board */
    std::string fieldFree;
    std::string fieldFail;
    std::string fieldSuccess;
};


#endif //BATTLESHIP_BOARD_H
