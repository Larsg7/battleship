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

    /** information about ships in game (just sizes) */
    std::vector<unsigned int> shipSizes;
    /** vector-vector keeping track of position of ships */
    std::vector<std::vector<int>> shipsBoard;
    /** vector holding the active ships pointer */
    std::vector<Ship*> ships;

    /**
     * @brief function which determines if a shot was successful
     * @param pos the position (local coords) where the user has shot to
     * @return string "SUCCESS" if shot was successful, "FAIL" otherwise
     */
    std::string shoot ( const std::pair<int,int> pos ) const;

    /**
     * show debug information (for now only the ships location)
     */
    void show_debug () const;

    /**
     * @brief check if a postion is valid for a new ship.
     *        That means: a) the pos is on the board
     *                    b) the pos is free (there is no ship there)
     *                    c) there is no ship within one tile
     * @param pos the pos to be checkesd (local coords)
     * @return if pos is valid
     */
    bool check_position ( std::pair<int, int> pos ) const;

    std::vector<std::pair<int,int>> check_placement ( std::pair<int, int> startPos, int size ) const;
};


#endif //BATTLESHIP_GAME_H
