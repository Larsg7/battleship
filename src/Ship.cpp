//
// Created by lars on 11/5/16.
//

#include "../inc/Ship.h"


Ship::Ship ( unsigned int size )
    : shipSize ( size )
{}

void Ship::set_pos ( std::vector<std::pair<int, int>> pos )
{
    shipPos = pos;
}

bool Ship::is_dead () const
{
    return isDead;
}

void Ship::die ()
{
    isDead = true;
}

std::vector<std::pair<int,int>> Ship::get_pos () const
{
    return shipPos;
}