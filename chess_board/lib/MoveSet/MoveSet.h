#include <String.h>
#include <MeasTime.h>
#include <Piece.h>
#ifndef MOVE_SET_H
#define MOVE_SET_H
#include <stdint.h> /// for special uint tyoes like int8_t
#define MAX_NO_MOVES_IN_EACH_BOARD 100
#define MAX_NO_PIECES_ON_BOARD 32

class MoveSet
{

public:
    int8_t moves[MAX_NO_MOVES_IN_EACH_BOARD];
    int8_t starting_positions[MAX_NO_PIECES_ON_BOARD * 2];

    uint8_t current_index = 0;
    int8_t current_starting_positions_index = -2;
    uint8_t size = 0;

    uint8_t starting_positions_size = 0;
    uint8_t sum = 0;

    void next(int8_t &from, int8_t &to);
    void get(int8_t &from, int8_t &to, const uint8_t id);
    void add_move(const int8_t new_move);
    void add_starting_position(const int8_t no_moves, const int8_t new_starting_position);

    void clear();
};

#endif