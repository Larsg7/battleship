//
// Created by lars on 11/5/16.
//

#ifndef BATTLESHIP_SHIP_H
#define BATTLESHIP_SHIP_H


#include <vector>

class Ship
{
public:
    Ship ( unsigned int size );

    void set_pos ( std::vector<std::pair<int,int>> pos );

    void die ();

    bool is_dead () const;

    std::vector<std::pair<int,int>> get_pos () const;

private:
    std::vector<std::pair<int,int>> shipPos;
    const unsigned int shipSize;
    bool isDead;
};


#endif //BATTLESHIP_SHIP_H
