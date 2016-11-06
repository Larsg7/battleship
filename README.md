# Battleship

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/9796d845a1be402a88bb0666150ff641)](https://www.codacy.com/app/larsgroeber7/battleship?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Larsg7/battleship&amp;utm_campaign=Badge_Grade)
[![Issue Count](https://codeclimate.com/github/Larsg7/battleship/badges/issue_count.svg)](https://codeclimate.com/github/Larsg7/battleship)

Play Battleship inside your terminal.

## How to run

**Still in development!**

The project makes heavy use of the *ncurses* library. So you have to have *ncurses* installed.

Use cmake:

    mkdir build
    cd build
    cmake .. && make
    ./battleship
    
Use g++:

    g++ -o battleship -lncurses -std=c++11 inc/*.h src/*.cpp
    ./battleship
    
## How to play

Arrow keys  -   move the cursor

ENTER - shoot

F2 - quit

(F12 - debug mode)

## License

This program is released under the MIT-License.