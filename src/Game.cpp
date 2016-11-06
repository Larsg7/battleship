#include <iostream>
#include "../inc/Game.h"
#include "../inc/Error.h"
#include "../inc/Ship.h"

#define MY_KEY_ENTER 10     // for some reason KEY_ENTER does not work

using namespace std;

//// PUBLIC METHODS ////

Game::Game ( Board* b )
    : mBoard ( b )
    , shipsTotal ( 1 )
    , dim ( b->get_dim() )
{
    shipsBoard = vector<vector<int>> ( dim.second );
    for ( int row = 0; row < shipsBoard.size(); ++row ) {
        shipsBoard[row] = vector<int> ( dim.first );
        for ( int col = 0; col < dim.first; ++col )
        {
            shipsBoard[row][col] = 0;
        }
    }
}

void Game::run ()
{
    int ch;

    randomize();

    mBoard->draw();
    refresh();

    while ( ( ch = getch() ) != KEY_F(2) || has_user_won() )
    {
        switch ( ch )
        {
            case MY_KEY_ENTER:
            {
                pair<int, int> currentPos = mBoard->get_cursor_pos();
                mBoard->set_field( currentPos, shoot( currentPos ));
                update_score();
                mBoard->draw();
                refresh();
                break;
            }
            default:
                mBoard->user_move_cursor( ch );
        }
    }
}


void Game::update_score ()
{
    // use auto here since we do not know the exact type of board
    auto board = mBoard->get_board();


}


bool Game::has_user_won ()
{
    if ( mBoard->is_board_full() && activeShips.size() != 0 )
    {
        throw Error ( "Board is full but there are still ships left in Game::has_user_won!" );
    }
    return activeShips.size() == 0;
}


bool Game::randomize ()
{
    for ( int i = 0; i < shipsTotal; ++i ) {
        
    }
    //cout << shipsBoard.size() << endl;
    shipsBoard[3][3] = 1;
    return true;
}

//// PRIVATE METHODS ////

std::string Game::shoot ( const std::pair<int, int> pos ) const
{
    switch ( shipsBoard[pos.second - 1][pos.first - 1] )
    {
        case 0:
            return "FAIL";
            break;
        default:
            return "SUCCESS";
            break;
    }
}