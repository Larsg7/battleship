cmake_minimum_required(VERSION 3.6)
project(battleship)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/Game.cpp inc/Game.h src/Board.cpp inc/Board.h src/Screen.cpp inc/Screen.h)
add_executable(battleship ${SOURCE_FILES})