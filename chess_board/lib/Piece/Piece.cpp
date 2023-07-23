#include <Piece.h>

Color get_color(Piece piece)
{
    if (piece >= b_pawn)
        return black;
    if (piece >= w_pawn)
        return white;
    return no_color;
}

bool is_opposite(const Piece piece, const Color opposite_to)
{
    auto color = get_color(piece);
    if (color == no_color)
        return false;
    return color != opposite_to;
}

Color reverse_color(const Color current_color)
{
    if (current_color == white)
        return black;
    if (current_color == black)
        return white;
    return current_color;
}

bool is_white(Piece piece)
{
    if (piece >= w_pawn && piece <= w_king)
        return true;
    return false;
}

bool is_black(Piece piece)
{
    if (piece >= b_pawn)
        return true;
    return false;
}