#include <iostream>
#include "../inc/Game.h"
#include "../inc/Error.h"
#include "../inc/Ship.h"

#define MY_KEY_ENTER 10     // for some reason KEY_ENTER does not work

using namespace std;

//// PUBLIC METHODS ////

Game::Game ( Board* b )
    : mBoard ( b )
    , dim ( b->get_dim() )
    , shipSizes { 2, 3 }        // each value correspond to one ship
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

    while ( ( ch = getch() ) != KEY_F(2) )
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
            case KEY_F(12):
                show_debug();
                break;
            default:
                mBoard->user_move_cursor( ch );
        }

        if ( has_user_won() )
        {
            cout << "You have won!" << endl;
            getch();
            break;
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
    if ( mBoard->is_board_full() && ships.size() != 0 )
    {
        throw Error ( "Board is full but there are still ships left in Game::has_user_won!" );
    }
    for ( auto s : ships )
    {
        if ( ! s->is_dead() )
            return false;
    }
    return true;
}


bool Game::randomize ()
{
    ships.clear();
    for ( auto i : shipSizes )
    {
        ships.push_back( new Ship () );
    }

    // for now, TODO: really randomize pos
    ships[0]->set_pos( { make_pair( 1,1 ), make_pair( 1,2 ) } ); // size 2 ship
    ships[1]->set_pos( { make_pair( 3,1 ), make_pair( 3,2 ), make_pair( 3,3 ) } );

    for ( auto s = ships.begin(); s != ships.end(); ++s )
    {
        for ( auto pos : (*s)->get_pos() )
        {
            // +1 because otherwise first ship would be lost
            shipsBoard[pos.second - 1][pos.first - 1] = (int)distance( ships.begin(), s ) + 1;
        }
    }

    return true;
}

//// PRIVATE METHODS ////

std::string Game::shoot ( const std::pair<int, int> pos ) const
{
    int id = shipsBoard[pos.second - 1][pos.first - 1];
    switch ( id )
    {
        case 0:
            return "FAIL";
            break;
        default:
            // the number corresponds to the index + 1 in ships
            ships[id - 1]->hit( pos );
            return "SUCCESS";
            break;
    }
}

void Game::show_debug () const
{
    Board debug = *mBoard;
    vector<vector<string>> newBoard ( dim.second );
    // we need to convert int to string for each element
    for ( int row = 0; row < shipsBoard.size(); ++row ) {
        newBoard[row] = vector<string> ( dim.first );
        for ( int col = 0; col < shipsBoard[row].size(); ++col ) {
            // important to use same string "." as in Board here
            newBoard[row][col] = (shipsBoard[row][col] == 0) ? "." : "o";
        }
    }

    debug.set_board( newBoard );
    debug.draw();
    refresh();
}