cmake_minimum_required(VERSION 3.20)
project(RivalsAnalyzer)

set(CMAKE_CXX_STANDARD 17)

add_executable(RivalsAnalyzer
        include/main.cpp
        include/hash_table.cpp
        include/Player.cpp
        include/SplayTree.cpp
)