cmake_minimum_required(VERSION 3.6)
project(battleship)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(battleship ${SOURCE_FILES})