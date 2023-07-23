
#include <MeasTime.h>
#include <Piece.h>
#ifndef MOVE_SET_H
#define MOVE_SET_H
#include <stdint.h> /// for special uint tyoes like int8_t
#define MAX_NO_MOVES_IN_EACH_BOARD 100
#define MAX_NO_PIECES_ON_BOARD 32

/// @brief Stores 'moves', a move is combination of two values:'from' and 'to'.
/// 'from' represents position on chessboard at which moved piece is placed
/// 'to' represents position on chessboard to which moved piece is moving
/// MoveSet enables quick sequencial access to data, but random access to moves is heavily restricted and slow
/// This is optimisation made for speed purposes.

/// Fields in class are by design public
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

    /// @brief get next move, 'from' and 'to' value pair
    /// @param from reference to which 'from' value will be assigned
    /// @param to reference to which 'to' value will be assigned
    void next(int8_t &from, int8_t &to);

    /// @brief retrieve specific 'move', but it's slow
    /// @param from reference to which 'from' value will be assigned
    /// @param to reference to which 'to' value will be assigned
    /// @param id id of retrievd move
    void get(int8_t &from, int8_t &to, const uint8_t id);

    void add_move(const int8_t new_move);

    void add_starting_position(const int8_t no_moves, const int8_t new_starting_position);

    /// @brief resets idex info about class, loosing information about stored data
    /// data is not deleted while clearing.
    void clear();
};

#endif