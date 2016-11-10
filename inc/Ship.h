#ifndef BATTLESHIP_SHIP_H
#define BATTLESHIP_SHIP_H


#include <vector>

/**
 * @brief Class responsible for holding all information about one ship
 * @author Lars Groeber
 */
class Ship
{
public:
    // use default constructor

    /**
     * @brief Function to set ships internal positions
     * @param pos vector of pairs containing every position of the ships
     */
    void set_pos ( std::vector<std::pair<int,int>> pos );

    /**
     * @brief Function which lets ship getting hit
     * Adds pos to damage to keep track of damage
     * @param pos the position of the hit
     */
    void hit ( std::pair<int,int> pos );

    /**
     * @brief Function which checks if ship is dead
     * @return bool
     */
    bool is_dead () const;

    /**
     * @brief Function to return ships positions
     * @return vector of all positions
     */
    std::vector<std::pair<int,int>> get_pos () const;

private:
    /** vector of ships position */
    std::vector<std::pair<int,int>> shipPos;
    /** vector keeping track of damage */
    std::vector<std::pair<int,int>> damage;
};


#endif //BATTLESHIP_SHIP_H
