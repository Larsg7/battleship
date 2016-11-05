//
// Created by lars on 11/4/16.
//

#ifndef BATTLESHIP_GAME_H
#define BATTLESHIP_GAME_H

#include "Board.h"

/*
 * what does it need:
 * a way to store ships
 * a run function to start the game -> draws board + refresh
 *                                     checks if user has won
 *                                     checks if user has hit ENTER - update board
 *
 * a way to randomize ships
 * a debug mode
 */

class Game
{
public:
    Game ( Board* b );

    /**
     * @brief main game function
     */
    void run ();

    /**
     * randomize the ships positions
     * @return bool of placement was successful
     */
    bool randomize ();

    /**
     * @brief check if user has won
     * @return bool
     */
    bool has_user_won ();
private:
    Board* mBoard;
    std::vector<std::vector<int>> ships;
    const int shipsTotal;
    int shipsLeft;
    const std::pair<int,int> dim;
};


#endif //BATTLESHIP_GAME_H
