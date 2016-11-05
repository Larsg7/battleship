//
// Created by lars on 11/4/16.
//

#include "../inc/Game.h"

using namespace std;

Game::Game ( Board* b )
    : mBoard ( b ), shipsTotal ( 1 ), shipsLeft ( shipsTotal )
    , dim ( b->get_dim() ), ships ( dim.second )
{
    for ( int row = 0; row < ships.size(); ++row ) {
        ships[row] = vector<int> ( dim.first );
        for ( int col = 0; col < dim.first; ++col )
        {
            ships[row][col] = 0;
        }
    }
}

void Game::run ()
{
    if ( has_user_won() ) return;

    int ch ( 0 );

    do
    {
        mBoard->update();
        mBoard->draw();
        refresh();
        while ( ( ch = getch() ) != KEY_F(2) )
        {
            mBoard->user_move_cursor( ch );
        }

    } while ( ( ch = getch() ) != KEY_F(2) );
}


bool Game::has_user_won ()
{
    return shipsLeft == 0;
}


bool Game::randomize ()
{
    ships[3][3] = 1;
    return true;
}