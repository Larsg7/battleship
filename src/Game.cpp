#include <iostream>
#include <stdlib.h>
#include <unistd.h>

#include "../inc/Game.h"
#include "../inc/Error.h"
#include "../inc/Ship.h"

#define MY_KEY_ENTER 10     // for some reason KEY_ENTER does not work

using namespace std;

//// PUBLIC METHODS ////

Game::Game ( Board* b )
    : mBoard ( b )
    , dim ( b->get_dim() )
    , shipSizes { 9, 9, 9 }        // each value corresponds to one ship
{
    shipsBoard = vector<vector<int>> ( dim.second );
    for ( int row = 0; row < shipsBoard.size(); ++row ) {
        shipsBoard[row] = vector<int> ( dim.first );
        for ( int col = 0; col < dim.first; ++col )
        {
            shipsBoard[row][col] = 0;
        }
    }

    // seed random number generator
    srand( time( NULL ) );
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
    // how many tries we have for each ship
    int maxTries ( 20 );

    ships.clear();

    // randomize ship positions
    for ( int size : shipSizes )
    {
        int tries ( 0 );

        bool shipPlaced ( false );

        Ship* newShip = new Ship ();

        // this vector will hold all ship positions
        vector<pair<int,int>> newPos;

        while ( ! shipPlaced )
        {
            if ( tries > maxTries )
            {
                throw Error ( "Was not able to set ship " + to_string(size) + ", maxTries exceeded in Game::randomize!" );
            }

            // should it be horizontal or vertical?
            bool vertical ( rand() % 2 == 0 );

            // starting position to try (+1 because rand()%dim. lies between 0 and dim.-1)
            // TODO: make searching algorithm starting at startPos until a valid field is found
            pair<int,int> startPos;
            if ( vertical )
            {
                startPos = make_pair( rand() % dim.first + 1, rand() % ( dim.second - size ) + size );
            }
            else
            {
                startPos = make_pair( rand() % ( dim.first - size ) + size, rand() % dim.second + 1 );
            }

            cout << "trying (" << startPos.first << "," << startPos.second << ")"
                 << " to " << "(" << startPos.first << "," << startPos.second - size << ")"<< endl;
            //sleep( 1);

            // now lets check every tile which belongs to the ship
            for ( int j = 0; j < size; ++j ) {
                // pair holding the pos to check
                pair<int,int> pos;

                // we always go left or up
                if ( vertical )
                {
                    pos = make_pair( startPos.first , startPos.second - j );
                    if ( ! check_placement( pos ) )
                    {
                        break;
                    }
                }
                else
                {
                    pos = make_pair( startPos.first - j, startPos.second );
                    if ( ! check_placement( pos ) )
                    {
                        break;
                    }
                }
                newPos.push_back( pos );
            }
            tries++;

            shipPlaced = newPos.size() == size;
        }

        newShip->set_pos( newPos );
        ships.push_back( newShip );
    } // end randomize

    // for now, TODO: really randomize pos
    //ships[0]->set_pos( { make_pair( 1,1 ), make_pair( 1,2 ) } ); // size 2 ship
    //ships[1]->set_pos( { make_pair( 3,1 ), make_pair( 3,2 ), make_pair( 3,3 ) } );

    // add ships to shipsBoard for easier access
    for ( auto s = ships.begin(); s != ships.end(); ++s )
    {
        for ( auto pos : (*s)->get_pos() )
        {
            // here we set the location of each ship to its corresponding index
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

/**
 * @brief checks placement of ship
 */
bool Game::check_placement ( std::pair<int, int> pos ) const
{
    // first check if pos is on board (its allowed to be on the edge)
    if ( pos.first  < 1 || pos.first  > dim.first
      || pos.second < 1 || pos.second > dim.second)
    {
        return false;
    }

    // ok, that was easy, now on to the hard part
    for ( auto s : ships )
    {
        for ( auto p : s->get_pos() )
        {
            if ( pos.first      == p.first
              //|| pos.first  + 1 == p.first
              //|| pos.first  - 1 == p.first
              || pos.second     == p.second)
              //|| pos.second + 1 == p.second
              //|| pos.second - 1 == p.second)
            {
                return false;
            }
        }
    }
    return true;
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