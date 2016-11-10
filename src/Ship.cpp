//
// Created by lars on 11/5/16.
//

#include <iostream>
#include "../inc/Ship.h"
#include "../inc/Error.h"


void Ship::set_pos ( std::vector<std::pair<int, int>> pos )
{
    shipPos = pos;
}

/**
 * Ship is dead if every positon of ship got hit
 */
bool Ship::is_dead () const
{
    return damage.size() == shipPos.size();
}

void Ship::hit ( std::pair<int,int> pos )
{
    // check if we find pos in damage
    // -> ship cannot be hit twice at same position
    for ( auto p : damage )
    {
        if ( p == pos )
        {
            return;
        }
    }
    damage.push_back( pos );

    // Check for logic error
    if ( shipPos.size() < damage.size() )
    {
        throw Error ( "Ships hits are smaller than zero in Ship::hit!" );
    }
}

std::vector<std::pair<int,int>> Ship::get_pos () const
{
    return shipPos;
}