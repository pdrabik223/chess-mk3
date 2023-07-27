cmake_minimum_required(VERSION 3.9.1)
project(ChessEngineMk3v LANGUAGES CXX)
include_directories(lib/Board lib/MoveSet lib/Piece)

# set(CMAKE_BUILD_TYPE Release)ninja
set(SOURCES
    src/x64_main.cpp
    lib/Board/Board.h
    lib/Board/Board.cpp
    lib/Board/generate_killing_moves.cpp lib/Board/generrate_no_legal_moves.cpp lib/Board/generate_legal_moves.cpp
    lib/Board/tree_traversal_functions.cpp
    lib/MoveSet/MoveSet.h
    lib/MoveSet/MoveSet.cpp
    lib/Piece/Piece.h
    lib/Piece/Piece.cpp
)

# STRING(REPLACE "/RTC" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
# add_compile_options(/O2)
set(CMAKE_CXX_FLAGS "/O2")
add_executable(ChessEngineMk3 ${SOURCES})

# target_compile_options(ChessEngineMk3 "/O2")