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

/// @brief generates noumber of legal moves for a pawn at position 'pos'
/// @param pos defines for witch pawn moveset should be calculated
/// @param number_of_moves noumber of moves already present in moveset array
/// @return Number of legal moves
uint16_t generate_no_legal_moves_rook(const Piece *data, const int8_t pos)
{

    uint16_t number_of_moves = 0;
    Color rook_color = get_color(data[pos]);
    int8_t pos_x = pos / 8;
    int8_t pos_y = pos % 8;

    int8_t new_pos;

    for (int8_t x = pos_x + 1; x < 8; x++)
    {
        // going down starting with position just under the rook
        new_pos = Board::construct_coord(x, pos_y);
        if (data[new_pos] == empty)
            number_of_moves++;
        else if (get_color(data[new_pos]) != rook_color)
        {
            number_of_moves++;
            break;
        }
        else
            break;
    }
    for (int8_t x = pos_x - 1; x >= 0; x--)
    {
        // going up starting with position just above the rook
        new_pos = Board::construct_coord(x, pos_y);
        if (data[new_pos] == empty)
            number_of_moves++;
        else if (get_color(data[new_pos]) != rook_color)
        {
            number_of_moves++;
            break;
        }
        else
            break;
    }
    for (int8_t y = pos_y + 1; y < 8; y++)
    {
        // going right starting with position just to the right from the rook
        new_pos = Board::construct_coord(pos_x, y);
        if (data[new_pos] == empty)
            number_of_moves++;
        else if (get_color(data[new_pos]) != rook_color)
        {
            number_of_moves++;
            break;
        }
        else
            break;
    }
    for (int8_t y = pos_y - 1; y >= 0; y--)
    {
        // going left starting with position just to the left from the rook
        new_pos = Board::construct_coord(pos_x, y);
        if (data[new_pos] == empty)
            number_of_moves++;
        else if (get_color(data[new_pos]) != rook_color)
        {
            number_of_moves++;
            break;
        }
        else
            break;
    }

    return number_of_moves;
}

/// @brief generates noumber of legal moves for a pawn at position 'pos'
/// @param pos defines for witch pawn moveset should be calculated
/// @param number_of_moves noumber of moves already present in moveset array
/// @return Number of legal moves
uint16_t generate_no_legal_moves_pawn(const Piece *data, const int8_t pos)
{
    uint16_t number_of_moves = 0;
    Color pawn_color = get_color(data[pos]);

    int8_t pos_x = pos / 8;
    int8_t pos_y = pos % 8;

    if (pawn_color == black)
    {
        // black is on top, and goes down

        if (pos_x == 1)
            if (data[pos + 16] == empty && data[pos + 8] == empty)
                number_of_moves++;

        if (pos_x + 1 < 8)
        {
            if (data[pos + 8] == empty)
                number_of_moves++;

            if (pos_y - 1 >= 0)
                // if pawn is not on the left edge of the chessboard
                if (is_white(data[pos + 7]))
                    number_of_moves++;

            if (pos_y + 1 < 8)
                // if pawn is not on the right edge of the chessboard
                if (is_white(data[pos + 9]))
                    number_of_moves++;
        }
    }
    else
    {
        // white is on the bottom, and goes up
        if (pos_x == 6)
            if (data[pos - 16] == empty && data[pos - 8] == empty)
                number_of_moves++;

        if (pos_x - 1 >= 0)
        {
            if (data[pos - 8] == empty)
                number_of_moves++;

            if (pos_y - 1 >= 0)
                // if pawn is not on the left edge of the chessboard
                if (is_black(data[pos - 9]))
                    number_of_moves++;

            if (pos_y + 1 < 8)
                // if pawn is not on the right edge of the chessboard
                if (is_black(data[pos - 7]))
                    number_of_moves++;
        }
    }

    return number_of_moves;
}

/// @brief generates noumber of legal moves for a pawn at position 'pos'
/// @param pos defines for witch pawn moveset should be calculated
/// @param number_of_moves noumber of moves already present in moveset array
/// @return Number of legal moves
uint16_t generate_no_legal_moves_knight(const Piece *data, int8_t pos)
{

    uint16_t number_of_moves = 0;
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
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos + 17;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        break;
    case 1:
        //  O O
        // O   O
        //   N
        // O   X
        //  X X
        new_pos = pos + 10;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos + 15;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos + 17;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        break;
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
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos + 10;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos + 15;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos + 17;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        break;
    case 6:
        //  O O
        // O   O
        //   N
        // X   O
        //  X X
        new_pos = pos + 6;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos + 10;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos + 15;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;

        break;
    case TOP_RIGHT:
        //  O O
        // O   O
        //   N
        // X   O
        //  X O
        new_pos = pos + 6;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos + 15;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        break;

    case 8:
        //  O O
        // O   X
        //   N
        // O   X
        //  O X
        new_pos = pos - 6;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos + 10;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos + 17;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;

        break;
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
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos - 6;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos + 10;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos + 17;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        break;
    case 48:
        //  O X
        // O   X
        //   N
        // O   X
        //  O O
        new_pos = pos - 15;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos - 6;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos + 10;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        break;
    case 15:
        //  O O
        // X   O
        //   N
        // X   O
        //  X O

        new_pos = pos - 10;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;

        new_pos = pos + 6;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;

        new_pos = pos + 15;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        break;

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
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;

        new_pos = pos - 10;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;

        new_pos = pos + 6;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;

        new_pos = pos + 15;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        break;
    case 55:
        //  X O
        // X   O
        //   N
        // X   O
        //  O O

        new_pos = pos - 17;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;

        new_pos = pos - 10;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;

        new_pos = pos + 6;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;

        break;
    case BOTTOM_LEFT:
        //  O X
        // O   X
        //   N
        // O   O
        //  O O
        new_pos = pos - 15;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos - 6;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        break;
    case 57:
        //  X X
        // O   X
        //   N
        // O   O
        //  O O
        new_pos = pos - 17;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos - 15;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos - 6;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        break;
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
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos - 15;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos - 10;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos - 6;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        break;
    case 62:
        //  X X
        // X   O
        //   N
        // O   O
        //  O O
        new_pos = pos - 17;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos - 15;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos - 10;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        break;
    case BOTTOM_RIGHT:
        //  X O
        // X   O
        //   N
        // O   O
        //  O O
        new_pos = pos - 17;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;

        new_pos = pos - 10;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;

        break;

    case AL_TOP_LEFT:

        //  O O
        // O   X
        //   N
        // O   X
        //  X X
        new_pos = pos - 6;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos + 10;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos + 17;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos + 15;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        break;
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
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos - 6;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos + 6;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos + 10;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos + 15;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos + 17;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        break;
    case AL_TOP_RIGHT:
        //  O O
        // X   O
        //   N
        // X   O
        //  X X
        new_pos = pos - 10;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos + 6;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos + 15;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos + 17;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        break;
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
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos - 15;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos - 10;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos + 6;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos + 15;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos + 17;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        break;

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
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos - 15;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos - 6;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos + 10;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos + 15;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos + 17;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;

        break;
    case AL_BOTTOM_LEFT:
        //  X X
        // O   X
        //   N
        // O   X
        //  O O
        new_pos = pos - 17;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos - 15;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos - 6;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos + 10;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        break;
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
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos - 15;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos - 10;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos - 6;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos + 6;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos + 10;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        break;
    case AL_BOTTOM_RIGHT:
        //  X X
        // X   O
        //   N
        // X   O
        //  O O
        new_pos = pos - 17;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos - 15;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos - 10;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        new_pos = pos + 6;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;

        break;
    default:
        //  X X
        // X   X
        //   N
        // X   X
        //  X X

        new_pos = pos - 17;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;

        new_pos = pos - 15;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;

        new_pos = pos - 6;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;

        new_pos = pos + 10;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;

        new_pos = pos + 17;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;

        new_pos = pos + 15;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;

        new_pos = pos + 6;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;

        new_pos = pos - 10;
        if (get_color(data[new_pos]) != knight_color)
            ++number_of_moves;
        break;
    }
    return number_of_moves;
}

/// @brief generates noumber of legal moves for a pawn at position 'pos'
/// @param pos defines for witch pawn moveset should be calculated
/// @param number_of_moves noumber of moves already present in moveset array
/// @return Number of legal moves
uint16_t generate_no_legal_moves_king(const Piece *data, const int8_t pos)
{
    uint16_t number_of_moves = 0;
    Color king_color = get_color(data[pos]);

    // int8_t pos_x = pos / 8;
    // int8_t pos_y = pos % 8;

    int8_t new_pos;
    switch (pos)
    {
    case 0:
        // OOO
        // OKX
        // OXX
        new_pos = pos + 1;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
        new_pos = pos + 8;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
        new_pos = pos + 9;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
        return number_of_moves;
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
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
        new_pos = pos + 1;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
        new_pos = pos + 7;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
        new_pos = pos + 8;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
        new_pos = pos + 9;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
        return number_of_moves;
    case 7:
        // OOO
        // XKO
        // XXO
        new_pos = pos - 1;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;

        new_pos = pos + 7;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
        new_pos = pos + 8;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
        return number_of_moves;

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
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
        new_pos = pos - 7;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
        new_pos = pos + 1;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
        new_pos = pos + 8;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
        new_pos = pos + 9;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
        return number_of_moves;
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
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
        new_pos = pos - 8;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
        new_pos = pos - 1;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
        new_pos = pos + 7;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
        new_pos = pos + 8;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;

    case 56:
        // OXX
        // OKX
        // OOO
        new_pos = pos - 8;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
        new_pos = pos - 7;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
        new_pos = pos + 1;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
        return number_of_moves;

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
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
        new_pos = pos - 8;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
        new_pos = pos - 7;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
        new_pos = pos - 1;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
        new_pos = pos + 1;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
        return number_of_moves;

    case 63:
        // XXO
        // XKO
        // OOO
        new_pos = pos - 9;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
        new_pos = pos - 8;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
        new_pos = pos - 1;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
        return number_of_moves;
    default:
        // XXX
        // XKX
        // XXX

        new_pos = pos - 9;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
        new_pos = pos - 8;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
        new_pos = pos - 7;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
        new_pos = pos - 1;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
        new_pos = pos + 1;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
        new_pos = pos + 7;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
        new_pos = pos + 8;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
        new_pos = pos + 9;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
        return number_of_moves;
    }
}

/// @brief generates noumber of legal moves for a pawn at position 'pos'
/// @param pos defines for witch pawn moveset should be calculated
/// @param number_of_moves noumber of moves already present in moveset array
/// @return Number of legal moves
uint16_t generate_no_legal_moves_bishop(const Piece *data, const int8_t pos)
{
    uint16_t number_of_moves = 0;
    Color bishop_color = get_color(data[pos]);

    int8_t pos_x = pos / 8;
    int8_t pos_y = pos % 8;

    int8_t new_pos;
    for (int8_t x = pos_x + 1, y = pos_y + 1; x < 8 && y < 8; x++, y++)
    {
        // going down and right starting with position just to the right and down from the bishop
        new_pos = Board::construct_coord(x, y);
        if (data[new_pos] == empty)
            number_of_moves++;
        else if (get_color(data[new_pos]) != bishop_color)
        {
            number_of_moves++;
            break;
        }
        else
            break;
    }
    for (int8_t x = pos_x + 1, y = pos_y - 1; x < 8 && y >= 0; x++, y--)
    {
        // going down and left starting with position just to the left and down from the bishop
        new_pos = Board::construct_coord(x, y);
        if (data[new_pos] == empty)
            number_of_moves++;
        else if (get_color(data[new_pos]) != bishop_color)
        {
            number_of_moves++;
            break;
        }
        else
            break;
    }
    for (int8_t x = pos_x - 1, y = pos_y - 1; x >= 0 && y >= 0; x--, y--)
    {
        // going up and left starting with position just to the left and up from the bishop
        new_pos = Board::construct_coord(x, y);
        if (data[new_pos] == empty)
            number_of_moves++;
        else if (get_color(data[new_pos]) != bishop_color)
        {
            number_of_moves++;
            break;
        }
        else
            break;
    }
    for (int8_t x = pos_x - 1, y = pos_y + 1; x >= 0 && y < 8; x--, y++)
    {
        // going up and right starting with position just to the right and up from the bishop
        new_pos = Board::construct_coord(x, y);
        if (data[new_pos] == empty)
            number_of_moves++;
        else if (get_color(data[new_pos]) != bishop_color)
        {
            number_of_moves++;
            break;
        }
        else
            break;
    }

    return number_of_moves;
}

/// @brief generates noumber of legal moves for a pawn at position 'pos'
/// @param pos defines for witch pawn moveset should be calculated
/// @param number_of_moves noumber of moves already present in moveset array
/// @return Number of legal moves
uint16_t generate_no_legal_moves_queen(const Piece *data, const int8_t pos)
{
    uint16_t number_of_moves = 0;
    //  queen is basically rook & bishop at once, so why even bother?
    number_of_moves = generate_no_legal_moves_rook(data, pos);
    number_of_moves += generate_no_legal_moves_bishop(data, pos);

    return number_of_moves;
}


