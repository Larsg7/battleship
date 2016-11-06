//
// Created by lars on 11/5/16.
//

#ifndef BATTLESHIP_SHIP_H
#define BATTLESHIP_SHIP_H


#include <vector>

class Ship
{
public:
    void set_pos ( std::vector<std::pair<int,int>> pos );

    void hit ( std::pair<int,int> pos );

    bool is_dead () const;

    std::vector<std::pair<int,int>> get_pos () const;

private:
    std::vector<std::pair<int,int>> shipPos;
    std::vector<std::pair<int,int>> damage;
    int hitsLeft;
};


#endif //BATTLESHIP_SHIP_H
