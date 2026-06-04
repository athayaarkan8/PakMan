cmake_minimum_required(VERSION 3.10)

project(PakMan)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(pakman
    main.cpp
    game/stack.cpp
    game/rewind.cpp
    player/player.cpp
    ghost/ghost.cpp
    ghost/bfs.cpp
    maze/graph.cpp
)