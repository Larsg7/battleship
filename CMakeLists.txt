cmake_minimum_required(VERSION 2.8)
project(battleship)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lncurses")

set(SOURCE_FILES src/main.cpp src/Game.cpp inc/Game.h src/Board.cpp inc/Board.h src/Screen.cpp inc/Screen.h inc/Error.h src/Ship.cpp inc/Ship.h)
add_executable(battleship ${SOURCE_FILES})