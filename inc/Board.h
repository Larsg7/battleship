#ifndef BATTLESHIP_BOARD_H
#define BATTLESHIP_BOARD_H

#include <ncurses.h>
#include <vector>
#include <string>

/**
 * class which is responsible for drawing the board and keeping
 * track of the cursor position
 */
class Board
{
public:
    /**
     * @brief constructor
     * @param x x dimension of board
     * @param y y dimension of board
     * @param win window to draw on
     */
    Board ( unsigned int x, unsigned int y, WINDOW* win );

    /**
     * @brief function to draw the actual board onto window
     */
    void draw () const;

    /**
     * @brief check if board is full (no empty field)
     * @return boolean
     */
    bool is_board_full ();

    /**
     * @brief move the cursor on the board (to allow the user to choose a field)
     * @param key the value of the key pressed (see ncurses' docs)
     * @return if cursor was moved (if not at the edge)
     */
    bool user_move_cursor ( const int key ) const;

    /**
    * @brief resets cursor to posCursor (especially after drawing)
    */
    void reset_cursor () const;

    //// SETTERS ////

    /**
     * @brief function which sets a field on the board
     * @param pos the position to set the field (local coords)
     * @param type string stating of which type the field should be
     * @return if the field was free
     */
    bool set_field ( const std::pair<int,int> pos, const std::string& type );

    void set_board ( std::vector<std::vector<std::string>>& b );

    //// GETTERS ////

    /**
     * @brief function which returns the board vector
     * @return board
     */
    std::vector<std::vector<std::string>> get_board () const;

    /**
     * @brief function which returns the current position of the cursor
     * @return posCursor
     */
    std::pair<int,int> get_cursor_pos () const;

    /**
     * @brief functions which returns the dimensions of the board
     * @return dim
     */
    std::pair<int,int> get_dim () const;

    WINDOW* get_window () const;

private:
    /** dimensions of the board (x,y) */
    const std::pair<unsigned int, unsigned int> dim;
    /** starting pos of the board in global coords */
    mutable std::pair<int, int> bStartGlobal;

    /** window to draw on */
    WINDOW* window;

    /** vector holding all information about the board */
    std::vector<std::vector<std::string>> board;

    /** variables which define the look of the board */
    std::string fieldSeparate;
    std::string fieldFree;
    std::string fieldFail;
    std::string fieldSuccess;
    unsigned int vSpace;

    /** starting position of the cursor in local coords (x,y) */
    const std::pair<int,int> posCursorStart;

    /** positon of the cursor in local coords (x,y) */
    mutable std::pair<int,int> posCursor;

    /**
     * @brief helper function to move the cursor to a position in local coords
     *        (has all logic for different values of fieldSeparate)
     * @return if movement was successful (if pos is on the board)
     */
    bool move_local ( std::pair<int,int> pos ) const;

    /**
     * @brief this function does all updating which needs to be done between drawings
     *        like set boardStart according to terminal size
     */
    void update () const;

    /**
     * @brief template helper function to print a vector to a string
     * @param vector the vector of type T to be printed
     * @param separate the separation string
     */
    template <typename T>
    std::string vector_to_string ( const std::vector<T>& vector, const std::string& separate ) const;
};


#endif //BATTLESHIP_BOARD_H
