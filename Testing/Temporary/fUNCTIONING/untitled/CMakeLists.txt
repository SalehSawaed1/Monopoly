cmake_minimum_required(VERSION 3.19)
project(untitled)

set(CMAKE_CXX_STANDARD 11)



set(CMAKE_CXX_STANDARD 11)

# Add the source files to be compiled
add_executable(MonopolyGameTest
        gamehandler.cpp
        gamemanager.cpp
        player.cpp
        freeparkinggrid.cpp
        specialgrid.cpp
        taxgrid.cpp
        surprisegrid.cpp
        propertygrid.cpp
        gotojailgrid.cpp
        railroadgrid.cpp
        utilitygrid.cpp
        jailgrid.cpp
        Grid.cpp
        monopolyboard.cpp
        test_grid.cpp
        )
