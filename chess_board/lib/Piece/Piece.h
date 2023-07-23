#include <stdint.h> /// for special uint tyoes like int8_t
#ifndef PIECE_H
#define PIECE_H
enum Piece : int8_t
{
    empty = 0,
    w_pawn = 1,
    w_knight = 2,
    w_bishop = 3,
    w_rook = 4,
    w_queen = 5,
    w_king = 6,

    b_pawn = 7,
    b_knight = 8,
    b_bishop = 9,
    b_rook = 10,
    b_queen = 11,
    b_king = 12
};

enum Color : int8_t
{
    no_color,
    white,
    black,
};
bool is_white(Piece piece);

bool is_black(Piece piece);

Color get_color(Piece piece);

Color reverse_color(const Color current_color);
bool is_opposite(const Piece piece, const Color opposite_to);
#endif