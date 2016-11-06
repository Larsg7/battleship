//
// Created by lars on 11/4/16.
//

#ifndef BATTLESHIP_GAME_H
#define BATTLESHIP_GAME_H

#include "Board.h"
#include "Ship.h"

/*
 * what does it need:
 * a way to store shipsBoard
 * a run function to start the game -> draws board + refresh
 *                                     checks if user has won
 *                                     checks if user has hit ENTER - update board
 *
 * a way to randomize shipsBoard
 * a debug mode
 */

/**
 * class making the actual game run
 */
class Game
{
public:
    /**
     * @brief constructor
     * @param b pointer to Board object
     */
    Game ( Board* b );

    /**
     * @brief main game function
     */
    void run ();

    /**
     * @brief this function udates the score (shipsLeft) by comparing ships to the board
     */
    void update_score ();

    /**
     * @brief randomize the ships positions
     * @return bool if placement was successful
     */
    bool randomize ();

    /**
     * @brief check if user has won
     * @return bool
     */
    bool has_user_won ();

private:
    /** pointer to the board being used */
    Board* mBoard;
    /** dimensions of the board (x,y) */
    const std::pair<unsigned int, unsigned int> dim;

    /** vector-vector keeping track of position of ships */
    std::vector<std::vector<int>> shipsBoard;
    std::vector<Ship*> activeShips;

    /** how many ships we have in total */
    const unsigned int shipsTotal;

    /**
     * @brief function which determines if a shot was successful
     * @param pos the position (local coords) where the user has shot to
     * @return string "SUCCESS" if shot was successful, "FAIL" otherwise
     */
    std::string shoot ( const std::pair<int,int> pos ) const;
};


#endif //BATTLESHIP_GAME_H
