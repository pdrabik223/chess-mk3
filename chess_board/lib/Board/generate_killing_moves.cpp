#include <Board.h>

#define TOP_LEFT 0
#define TOP_RIGHT 7
#define RIGHT 2
#define BOTTOM_LEFT 56
#define BOTTOM_RIGHT 63
#define AL_TOP_LEFT 9
#define AL_TOP_RIGHT 14
#define AL_BOTTOM_LEFT 49
#define AL_BOTTOM_RIGHT 54

// chess board ids

//  0  1  2  3  4  5  6  7
//  8  9 10 11 12 13 14 15
// 16 17 18 19 20 21 22 23
// 24 25 26 27 28 29 30 31
// 32 33 34 35 36 37 38 39
// 40 41 42 43 44 45 46 47
// 48 49 50 51 52 53 54 55
// 56 57 58 59 60 61 62 63

/// @brief generates killing moveset for a pawn at position 'pos'
/// @param pos defines for witch pawn moveset should be calculated
/// @param moveset stores all killing possible move positions
/// @param number_of_moves noumber of moves already present in moveset array
/// @return Number of killing moves
void Board::generate_killing_moveset_pawn(int8_t pos, MoveSet &moves) const
{

    Color pawn_color = get_color(data[pos]);

    int8_t pos_x = pos / width;
    int8_t pos_y = pos % width;

    if (pawn_color == white)
    {
        // black is on top, and goes down
        if (pos_x + 1 < 8)
        {
            if (pos_y - 1 >= 0)
                // if pawn is not on the left edge of the chessboard
                if (is_black(data[pos + 7]))
                    moves.add_move(pos + 7);

            if (pos_y + 1 < 8)
                // if pawn is not on the right edge of the chessboard
                if (is_black(data[pos + 9]))
                    moves.add_move(pos + 9);
        }
    }
    else
    {
        // white is on the bottom, and goes up

        if (pos_x - 1 >= 0)
        {
            if (pos_y - 1 >= 0)
                // if pawn is not on the left edge of the chessboard
                if (is_white(data[pos - 9]))
                    moves.add_move(pos - 9);

            if (pos_y + 1 < 8)
                // if pawn is not on the right edge of the chessboard
                if (is_white(data[pos - 7]))
                    moves.add_move(pos - 7);
        }
    }
}

/// @brief generates killing moveset for a pawn at position 'pos'
/// @param pos defines for witch pawn moveset should be calculated
/// @param moveset stores all killing possible move positions
/// @param number_of_moves noumber of moves already present in moveset array
/// @return Number of killing moves
void Board::generate_killing_moveset_knight(int8_t pos, MoveSet &moves) const
{
    Color knight_color = get_color(data[pos]);
    int8_t new_pos;
    switch (pos)
    {

    case 0:
        // 8 |N|#|_|#|_|#|_|#|
        // 7 |#|_|X|_|#|_|#|_|
        // 6 |_|X|_|#|_|#|_|#|
        // 5 |#|_|#|_|#|_|#|_|
        // 4 |_|#|_|#|_|#|_|#|
        // 3 |#|_|#|_|#|_|#|_|
        // 2 |_|#|_|#|_|#|_|#|
        // 1 |#|_|#|_|#|_|#|_|
        //    a b c d e f g h

        //  O O
        // O   O
        //   N
        // O   X
        //  O X
        new_pos = pos + 10;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);

        new_pos = pos + 17;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        return;
    case 1:
        //  O O
        // O   O
        //   N
        // O   X
        //  X X
        new_pos = pos + 10;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos + 15;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos + 17;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        return;
    case 2:
    case 3:
    case 4:
    case 5:
        //  O O
        // O   O
        //   N
        // X   X
        //  X X
        new_pos = pos + 6;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos + 10;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos + 15;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos + 17;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        return;
    case 6:
        //  O O
        // O   O
        //   N
        // X   O
        //  X X
        new_pos = pos + 6;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos + 15;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos + 17;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);

        return;
    case TOP_RIGHT:
        //  O O
        // O   O
        //   N
        // X   O
        //  X O
        new_pos = pos + 6;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos + 15;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        return;

    case 8:
        //  O O
        // O   X
        //   N
        // O   X
        //  O X
        new_pos = pos - 6;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos + 10;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos + 17;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);

        return;
    case 16:
    case 24:
    case 32:
    case 40:
        //  O X
        // O   X
        //   N
        // O   X
        //  O X
        new_pos = pos - 15;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos - 6;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos + 10;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos + 17;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        return;
    case 48:
        //  O X
        // O   X
        //   N
        // O   X
        //  O O
        new_pos = pos - 15;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos - 6;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos + 10;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        return;
    case 15:
        //  O O
        // X   O
        //   N
        // X   O
        //  X O

        new_pos = pos - 10;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);

        new_pos = pos + 6;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);

        new_pos = pos + 15;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        return;

    case 23:
    case 31:
    case 39:
    case 47:
        //  X O
        // X   O
        //   N
        // X   O
        //  X O

        new_pos = pos - 17;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);

        new_pos = pos - 10;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);

        new_pos = pos + 6;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);

        new_pos = pos + 15;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        return;
    case 55:
        //  X O
        // X   O
        //   N
        // X   O
        //  O O

        new_pos = pos - 17;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);

        new_pos = pos - 10;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);

        new_pos = pos + 6;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);

        return;
    case BOTTOM_LEFT:
        //  O X
        // O   X
        //   N
        // O   O
        //  O O
        new_pos = pos - 15;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos - 6;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        return;
    case 57:
        //  X X
        // O   X
        //   N
        // O   O
        //  O O
        new_pos = pos - 17;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos - 15;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos - 6;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        return;
    case 58:
    case 59:
    case 60:
    case 61:
        //  X X
        // X   X
        //   N
        // O   O
        //  O O
        new_pos = pos - 17;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos - 15;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos - 10;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos - 6;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        return;
    case 62:
        //  X X
        // X   O
        //   N
        // O   O
        //  O O
        new_pos = pos - 17;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos - 15;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos - 10;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        return;
    case BOTTOM_RIGHT:
        //  X O
        // X   O
        //   N
        // O   O
        //  O O
        new_pos = pos - 17;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);

        new_pos = pos - 10;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);

        return;

    case AL_TOP_LEFT:

        //  O O
        // O   X
        //   N
        // O   X
        //  X X
        new_pos = pos - 6;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos + 10;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos + 17;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos + 15;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        return;
    case 10:
    case 11:
    case 12:
    case 13:
        //  O O
        // X   X
        //   N
        // X   X
        //  X X
        new_pos = pos - 10;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos - 6;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos + 6;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos + 10;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos + 15;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos + 17;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        return;
    case AL_TOP_RIGHT:
        //  O O
        // X   O
        //   N
        // X   O
        //  X X
        new_pos = pos - 10;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos + 6;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos + 15;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos + 17;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        return;
    case 22:
    case 30:
    case 38:
    case 46:
        //  X X
        // X   O
        //   N
        // X   O
        //  X X

        new_pos = pos - 17;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos - 15;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos - 10;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos + 6;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos + 15;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos + 17;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        return;

    case 17:
    case 25:
    case 33:
    case 41:
        //  X X
        // O   X
        //   N
        // O   X
        //  X X
        new_pos = pos - 17;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos - 15;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos - 6;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos + 10;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos + 15;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos + 17;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);

        return;
    case AL_BOTTOM_LEFT:
        //  X X
        // O   X
        //   N
        // O   X
        //  O O
        new_pos = pos - 17;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos - 15;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos - 6;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos + 10;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        return;
    case 50:
    case 51:
    case 52:
    case 53:
        //  X X
        // X   X
        //   N
        // X   X
        //  O O
        new_pos = pos - 17;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos - 15;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos - 10;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos - 6;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos + 6;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos + 10;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        return;
    case AL_BOTTOM_RIGHT:
        //  X X
        // X   O
        //   N
        // X   O
        //  O O
        new_pos = pos - 17;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos - 15;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos - 10;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        new_pos = pos + 6;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);

        return;
    default:
        //  X X
        // X   X
        //   N
        // X   X
        //  X X

        new_pos = pos - 17;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);

        new_pos = pos - 15;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);

        new_pos = pos - 6;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);

        new_pos = pos + 10;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);

        new_pos = pos + 17;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);

        new_pos = pos + 15;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);

        new_pos = pos + 6;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);

        new_pos = pos - 10;
        if (is_opposite(data[new_pos], knight_color))
            moves.add_move(new_pos);
        return;
    }
}

/// @brief generates killing moveset for a pawn at position 'pos'
/// @param pos defines for witch pawn moveset should be calculated
/// @param moveset stores all killing possible move positions
/// @param number_of_moves noumber of moves already present in moveset array
/// @return Number of killing moves
void Board::generate_killing_moveset_king(const int8_t pos, MoveSet &moves) const
{

    Color king_color = get_color(data[pos]);
    int8_t new_pos;
    switch (pos)
    {
    case 0:
        // OOO
        // OKX
        // OXX
        new_pos = pos + 1;
        if (is_opposite(data[new_pos], king_color))
            moves.add_move(new_pos);
        new_pos = pos + 8;
        if (is_opposite(data[new_pos], king_color))
            moves.add_move(new_pos);
        new_pos = pos + 9;
        if (is_opposite(data[new_pos], king_color))
            moves.add_move(new_pos);
        return;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        // OOO
        // XKX
        // XXX
        new_pos = pos - 1;
        if (is_opposite(data[new_pos], king_color))
            moves.add_move(new_pos);
        new_pos = pos + 1;
        if (is_opposite(data[new_pos], king_color))
            moves.add_move(new_pos);
        new_pos = pos + 7;
        if (is_opposite(data[new_pos], king_color))
            moves.add_move(new_pos);
        new_pos = pos + 8;
        if (is_opposite(data[new_pos], king_color))
            moves.add_move(new_pos);
        new_pos = pos + 9;
        if (is_opposite(data[new_pos], king_color))
            moves.add_move(new_pos);
        return;
    case 7:
        // OOO
        // XKO
        // XXO
        new_pos = pos - 1;
        if (is_opposite(data[new_pos], king_color))
            moves.add_move(new_pos);

        new_pos = pos + 7;
        if (is_opposite(data[new_pos], king_color))
            moves.add_move(new_pos);
        new_pos = pos + 8;
        if (is_opposite(data[new_pos], king_color))
            moves.add_move(new_pos);
        return;

    case 8:
    case 16:
    case 24:
    case 32:
    case 40:
    case 48:
        // OXX
        // OKX
        // OXX

        new_pos = pos - 8;
        if (is_opposite(data[new_pos], king_color))
            moves.add_move(new_pos);
        new_pos = pos - 7;
        if (is_opposite(data[new_pos], king_color))
            moves.add_move(new_pos);
        new_pos = pos + 1;
        if (is_opposite(data[new_pos], king_color))
            moves.add_move(new_pos);
        new_pos = pos + 8;
        if (is_opposite(data[new_pos], king_color))
            moves.add_move(new_pos);
        new_pos = pos + 9;
        if (is_opposite(data[new_pos], king_color))
            moves.add_move(new_pos);
        return;
    case 15:
    case 23:
    case 31:
    case 39:
    case 47:
    case 55:
        // XXO
        // XKO
        // XXO
        new_pos = pos - 9;
        if (is_opposite(data[new_pos], king_color))
            moves.add_move(new_pos);
        new_pos = pos - 8;
        if (is_opposite(data[new_pos], king_color))
            moves.add_move(new_pos);
        new_pos = pos - 1;
        if (is_opposite(data[new_pos], king_color))
            moves.add_move(new_pos);
        new_pos = pos + 7;
        if (is_opposite(data[new_pos], king_color))
            moves.add_move(new_pos);
        new_pos = pos + 8;
        if (is_opposite(data[new_pos], king_color))
            moves.add_move(new_pos);

    case 56:
        // OXX
        // OKX
        // OOO
        new_pos = pos - 8;
        if (is_opposite(data[new_pos], king_color))
            moves.add_move(new_pos);
        new_pos = pos - 7;
        if (is_opposite(data[new_pos], king_color))
            moves.add_move(new_pos);
        new_pos = pos + 1;
        if (is_opposite(data[new_pos], king_color))
            moves.add_move(new_pos);
        return;

    case 57:
    case 58:
    case 59:
    case 60:
    case 61:
    case 62:
        // XXX
        // XKX
        // OOO
        new_pos = pos - 9;
        if (is_opposite(data[new_pos], king_color))
            moves.add_move(new_pos);
        new_pos = pos - 8;
        if (is_opposite(data[new_pos], king_color))
            moves.add_move(new_pos);
        new_pos = pos - 7;
        if (is_opposite(data[new_pos], king_color))
            moves.add_move(new_pos);
        new_pos = pos - 1;
        if (is_opposite(data[new_pos], king_color))
            moves.add_move(new_pos);
        new_pos = pos + 1;
        if (is_opposite(data[new_pos], king_color))
            moves.add_move(new_pos);
        return;

    case 63:
        // XXO
        // XKO
        // OOO
        new_pos = pos - 9;
        if (is_opposite(data[new_pos], king_color))
            moves.add_move(new_pos);
        new_pos = pos - 8;
        if (is_opposite(data[new_pos], king_color))
            moves.add_move(new_pos);
        new_pos = pos - 1;
        if (is_opposite(data[new_pos], king_color))
            moves.add_move(new_pos);
        return;
    default:
        // XXX
        // XKX
        // XXX

        new_pos = pos - 9;
        if (is_opposite(data[new_pos], king_color))
            moves.add_move(new_pos);
        new_pos = pos - 8;
        if (is_opposite(data[new_pos], king_color))
            moves.add_move(new_pos);
        new_pos = pos - 7;
        if (is_opposite(data[new_pos], king_color))
            moves.add_move(new_pos);
        new_pos = pos - 1;
        if (is_opposite(data[new_pos], king_color))
            moves.add_move(new_pos);
        new_pos = pos + 1;
        if (is_opposite(data[new_pos], king_color))
            moves.add_move(new_pos);
        new_pos = pos + 7;
        if (is_opposite(data[new_pos], king_color))
            moves.add_move(new_pos);
        new_pos = pos + 8;
        if (is_opposite(data[new_pos], king_color))
            moves.add_move(new_pos);
        new_pos = pos + 9;
        if (is_opposite(data[new_pos], king_color))
            moves.add_move(new_pos);
        return;
    }
}

/// @brief generates killing moveset for a pawn at position 'pos'
/// @param pos defines for witch pawn moveset should be calculated
/// @param moveset stores all killing possible move positions
/// @param number_of_moves noumber of moves already present in moveset array
/// @return Number of killing moves
void Board::generate_killing_moveset_rook(const int8_t pos, MoveSet &moves) const
{

    Color rook_color = get_color(data[pos]);

    int8_t pos_x = pos / width;
    int8_t pos_y = pos % width;

    int8_t new_pos;

    for (int8_t x = pos_x + 1; x < 8; x++)
    {
        // going down starting with position just under the rook
        new_pos = construct_coord(x, pos_y);
        if (data[new_pos] == empty)
            continue;
        else if (is_opposite(data[new_pos], rook_color))
        {
            moves.add_move(new_pos);
            break;
        }
        else
            break;
    }
    for (int8_t x = pos_x - 1; x >= 0; x--)
    {
        // going up starting with position just above the rook
        new_pos = construct_coord(x, pos_y);
        if (data[new_pos] == empty)
            continue;
        else if (is_opposite(data[new_pos], rook_color))
        {
            moves.add_move(new_pos);
            break;
        }
        else
            break;
    }
    for (int8_t y = pos_y + 1; y < 8; y++)
    {
        // going right starting with position just to the right from the rook
        new_pos = construct_coord(pos_x, y);
        if (data[new_pos] == empty)
            continue;
        else if (is_opposite(data[new_pos], rook_color))
        {
            moves.add_move(new_pos);
            break;
        }
        else
            break;
    }
    for (int8_t y = pos_y - 1; y >= 0; y--)
    {
        // going left starting with position just to the left from the rook
        new_pos = construct_coord(pos_x, y);
        if (data[new_pos] == empty)
            continue;
        else if (is_opposite(data[new_pos], rook_color))
        {
            moves.add_move(new_pos);
            break;
        }
        else
            break;
    }
}

/// @brief generates killing moveset for a pawn at position 'pos'
/// @param pos defines for witch pawn moveset should be calculated
/// @param moveset stores all killing possible move positions
/// @param number_of_moves noumber of moves already present in moveset array
/// @return Number of killing moves
void Board::generate_killing_moveset_bishop(const int8_t pos, MoveSet &moves) const
{

    Color bishop_color = get_color(data[pos]);

    int8_t pos_x = pos / width;
    int8_t pos_y = pos % width;

    int8_t new_pos;
    for (int8_t x = pos_x + 1, y = pos_y + 1; x < 8 && y < 8; x++, y++)
    {
        // going down and right starting with position just to the right and down from the bishop
        new_pos = construct_coord(x, y);
        if (data[new_pos] == empty)
            continue;
        else if (is_opposite(data[new_pos], bishop_color))
        {
            moves.add_move(new_pos);
            break;
        }
        else
            break;
    }
    for (int8_t x = pos_x + 1, y = pos_y - 1; x < 8 && y >= 0; x++, y--)
    {
        // going down and left starting with position just to the left and down from the bishop
        new_pos = construct_coord(x, y);
        if (data[new_pos] == empty)
            continue;
        else if (is_opposite(data[new_pos], bishop_color))
        {
            moves.add_move(new_pos);
            break;
        }
        else
            break;
    }
    for (int8_t x = pos_x - 1, y = pos_y - 1; x >= 0 && y >= 0; x--, y--)
    {
        // going up and left starting with position just to the left and up from the bishop
        new_pos = construct_coord(x, y);
        if (data[new_pos] == empty)
            continue;
        else if (is_opposite(data[new_pos], bishop_color))
        {
            moves.add_move(new_pos);
            break;
        }
        else
            break;
    }
    for (int8_t x = pos_x - 1, y = pos_y + 1; x >= 0 && y < 8; x--, y++)
    {
        // going up and right starting with position just to the right and up from the bishop
        new_pos = construct_coord(x, y);
        if (data[new_pos] == empty)
            continue;
        else if (is_opposite(data[new_pos], bishop_color))
        {
            moves.add_move(new_pos);
            break;
        }
        else
            break;
    }
}

/// @brief generates killing moveset for a pawn at position 'pos'
/// @param pos defines for witch pawn moveset should be calculated
/// @param moveset stores all killing possible move positions
/// @param number_of_moves noumber of moves already present in moveset array
/// @return Number of killing moves
void Board::generate_killing_moveset_queen(const int8_t pos, MoveSet &moves) const
{

    //  queen is basically rook & bishop at once, so why even bother?
    generate_killing_moveset_rook(pos, moves);
    generate_killing_moveset_bishop(pos, moves);
}

/// @brief generates killing moveset for a given color
/// @param color color for which all moves possible will be generated
/// @param moveset stores all killing possible move positions
/// @return Number of killing moves
void Board::generate_killing_moveset_for_color(Color color, MoveSet &moves) const
{

    int8_t queens_position[1];

    int8_t rooks_positions[2];

    int8_t bishops_positions[2];

    int8_t knights_positions[2];

    int8_t pawns_positions[8];

    int8_t kings_position[1];

    // jump table
    // instead of implementing logic with a lot of comparions
    // jump table can be created, that can be indexed with pawn type
    int8_t *table[6]{pawns_positions, knights_positions, bishops_positions, rooks_positions, queens_position, kings_position};
    int8_t index_table[6]{0, 0, 0, 0, 0, 0};

    for (int8_t i = 0; i < 64; i++)
    {
        if (get_color(data[i]) == color)
        {
            int8_t index = data[i] - 1;

            if (color == black)
                index -= 6;

            table[index][index_table[index]] = i;
            index_table[index] += 1;
        }
    }

    int number_of_moves;
    for (int8_t p = 0; p < index_table[w_pawn - 1]; p++)
    {
        number_of_moves = moves.size;
        generate_killing_moveset_pawn(pawns_positions[p], moves);
        moves.add_starting_position(moves.size - number_of_moves, pawns_positions[p]);
    }
    for (int8_t k = 0; k < index_table[w_knight - 1]; k++)
    {
        number_of_moves = moves.size;
        generate_killing_moveset_knight(knights_positions[k], moves);
        moves.add_starting_position(moves.size - number_of_moves, knights_positions[k]);
    }
    if (index_table[w_queen - 1] > 0)
    {
        number_of_moves = moves.size;
        generate_killing_moveset_queen(queens_position[0], moves);
        moves.add_starting_position(moves.size - number_of_moves, queens_position[0]);
    }
    for (int8_t b = 0; b < index_table[w_bishop - 1]; b++)
    {
        number_of_moves = moves.size;
        generate_killing_moveset_bishop(bishops_positions[b], moves);
        moves.add_starting_position(moves.size - number_of_moves, bishops_positions[b]);
    }
    for (int8_t r = 0; r < index_table[w_rook - 1]; r++)
    {
        number_of_moves = moves.size;
        generate_killing_moveset_rook(rooks_positions[r], moves);
        moves.add_starting_position(moves.size - number_of_moves, rooks_positions[r]);
    }
    if (index_table[w_king - 1] > 0)
    {
        number_of_moves = moves.size;
        generate_killing_moveset_king(kings_position[0], moves);
        moves.add_starting_position(moves.size - number_of_moves, kings_position[0]);
    }
}
