#include <iostream>
#include <stdlib.h>
#include <unistd.h>

#include "../inc/Game.h"
#include "../inc/Error.h"

#define MY_KEY_ENTER 10     // for some reason KEY_ENTER does not work

using namespace std;

//// PUBLIC METHODS ////

Game::Game ( Board* b )
    : mBoard ( b )
    , dim ( b->get_dim() )
    , shipSizes { 5, 4, 3, 2, 2, 1, 1 }        // each value corresponds to one ship
{
    // initialize shipsBoard to 0
    shipsBoard = vector<vector<int>> ( dim.second );
    for ( int row = 0; row < shipsBoard.size(); ++row ) {
        shipsBoard[row] = vector<int> ( dim.first );
        for ( int col = 0; col < dim.first; ++col )
        {
            shipsBoard[row][col] = 0;
        }
    }

    int maxShips = (int)shipSizes.size();
    mBoard->set_score( 0, maxShips );

    // seed random number generator
    srand( time( NULL ) );
}

/**
 * Main game loop
 */
void Game::run ()
{
    int ch;

    // randomize ships positions
    randomize();

    // draw board for the first time
    mBoard->draw();
    refresh();

    // main game loop
    while ( ( ch = getch() ) != KEY_F(2) )
    {
        switch ( ch )
        {
            case MY_KEY_ENTER:
            {
                pair<int, int> currentPos = mBoard->get_cursor_pos();
                // set position on board accordingly
                mBoard->set_field( currentPos, shoot( currentPos ));
                // redraw board
                mBoard->draw();
                refresh();
                break;
            }
            case KEY_F(12):
                show_debug();
                break;
            default:
                // move cursor
                mBoard->user_move_cursor( ch );
        }

        if ( has_user_won() )
        {
            // show confirmation for player
            mBoard->print_message( "  You have won!  " );
            getch();
            break;
        }
    }
}

/**
 * simple implemention: just check if there are ships left alive
 */
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

/**
 * This function follows this pattern:
 * 1) choose a random position on the board (startPos)
 * 2) check if ship can be placed there (using check_placement())
 *      A) if not: move one field to the right (or down if at end of row)
 *      - goto 2) -
 *      B) otherwise set ships positions and add to ships
 * 4) repeat at 1) for all ships in shipSizes
 * done
 */
bool Game::randomize ()
{
    ships.clear();

    // see step 4)
    for ( int size : shipSizes )
    {
        int tries ( 0 );

        bool shipPlaced ( false );

        Ship* newShip = new Ship ();

        // this vector will hold all positions for newShip
        vector<pair<int,int>> newPos;

        // random starting position - see step 1)
        // (+1 because rand()%dim.x lies between 0 and dim.x-1)
        pair<int,int> startPos { rand() % dim.first + 1, rand() % dim.second + 1 };
        pair<int,int> testPos = startPos;

        while ( ! shipPlaced )
        {
            // throw an Error if we could be in an endless loop
            if ( testPos == startPos && tries != 0 )
            {
                throw Error ( "Was not able to set ship with size" + to_string(size)
                              + ", got back to startPos in Game::randomize!" );
            }

            // see step 2)
            newPos = check_placement( testPos, size );

            // move one pos - see 2.A)
            if ( testPos.first == dim.first )
            {
                testPos.first = 1;
                testPos.second = testPos.second % dim.second + 1;
            }
            else
            {
                testPos.first++;
            }

            // were we successful placing ship?
            shipPlaced = ( newPos.size() == size );
            tries++;
        }

        // see step 2.B)
        newShip->set_pos( newPos );
        ships.push_back( newShip );
    } // end randomize

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

/**
 * check if at position pos is a ship
 */
std::string Game::shoot ( const std::pair<int, int> pos ) const
{
    int id = shipsBoard[pos.second - 1][pos.first - 1];
    switch ( id )
    {
        case 0:
            mBoard->print_message( "You missed!     " ); // quick fix to overwrite old message
            return "FAIL";
        default:
            // the number corresponds to the index + 1 in ships
            if ( ! ships[id - 1]->is_dead() )
            {
                ships[id - 1]->hit( pos );

                if ( ships[id - 1]->is_dead() )
                {
                    mBoard->print_message( "You sunk a ship!" );
                    mBoard->advance_score();
                }
                else
                {
                    mBoard->print_message( "You hit a ship! " );
                }
            }
            return "SUCCESS";
    }
}

/**
 * Check if a ship of size *size* can be placed at position *startPos*
 */
vector<pair<int,int>> Game::check_placement ( pair<int, int> startPos, int size ) const
{
    vector<pair<int,int>> newPos;
    // 2 rounds for vertical and horizontal placement
    for ( int i = 0; i < 2; ++i )
    {
        // if it's the first round, vertical should be set randomly
        // otherwise set vertical to the opposite
        bool vertical = ( i == 0 ) ? rand() % 2 : ! vertical;

        newPos.clear();
        for ( int j = 0; j < size; ++j )
        {
            // pair holding the pos to check
            pair<int, int> pos;

            // we always go left or up
            if ( vertical )
            {
                pos = make_pair( startPos.first, startPos.second - j );
            }
            else
            {
                pos = make_pair( startPos.first - j, startPos.second );
            }
            if ( ! check_position( pos ) ) { break; }

            newPos.push_back( pos );
        }
    }

    // if ship can be placed return new positions, otherwise return empty vector
    return ( newPos.size() == size ) ? newPos : vector<pair<int,int>> ( 0 );
}

/**
 * Here we loop through all existing ships and check if one of their position
 * lies too close or on the given position.
 */
bool Game::check_position ( std::pair<int, int> pos ) const
{
    // first check if pos is on board (its allowed to be on the edge)
    if ( pos.first  < 1 || pos.first  > dim.first
      || pos.second < 1 || pos.second > dim.second)
    {
        return false;
    }

    // loop through all ships
    for ( auto s : ships )
    {
        // now loop through all positions of that ship
        for ( auto p : s->get_pos() )
        {
            // not nice, but it works
            if ( ( pos.first     == p.first && pos.second     == p.second )
              || ( pos.first + 1 == p.first && pos.second + 1 == p.second )
              || ( pos.first - 1 == p.first && pos.second - 1 == p.second )
              || ( pos.first + 1 == p.first && pos.second - 1 == p.second )
              || ( pos.first - 1 == p.first && pos.second + 1 == p.second )
              || ( pos.first + 1 == p.first && pos.second     == p.second )
              || ( pos.first     == p.first && pos.second + 1 == p.second )
              || ( pos.first - 1 == p.first && pos.second     == p.second )
              || ( pos.first     == p.first && pos.second - 1 == p.second ) )
            {
                return false;
            }
        }
    }
    return true;
}

/**
 * Shows user a new board only consisting of the ships positions
 */
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