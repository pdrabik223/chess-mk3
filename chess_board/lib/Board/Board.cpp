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

    int8_t pos_x = pos / 8;
    int8_t pos_y = pos % 8;

    int8_t new_pos;
    if (pos_x - 1 >= 0 && pos_y - 1 >= 0)
    {
        // XOO
        // OKO
        // OOO

        new_pos = pos - 9;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
    }
    if (pos_x - 1 >= 0)
    {
        // OXO
        // OKO
        // OOO

        new_pos = pos - 8;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
    }
    if (pos_x - 1 >= 0 && pos_y + 1 < 8)
    {
        // OOX
        // OKO
        // OOO

        new_pos = pos - 7;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
    }
    if (pos_y - 1 >= 0)
    {
        // OOO
        // XKO
        // OOO

        new_pos = pos - 1;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
    }
    if (pos_y + 1 < 8)
    {
        // OOO
        // OKX
        // OOO

        new_pos = pos + 1;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
    }
    if (pos_x + 1 < 8 && pos_y - 1 >= 0)
    {
        // OOO
        // OKO
        // XOO

        new_pos = pos + 7;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
    }
    if (pos_x + 1 < 8)
    {
        // OOO
        // OKO
        // OXO

        new_pos = pos + 8;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
    }
    if (pos_x + 1 < 8 && pos_y + 1 < 8)
    {
        // OOO
        // OKO
        // OOX

        new_pos = pos + 9;
        if (get_color(data[new_pos]) != king_color)
            number_of_moves++;
    }

    return number_of_moves;
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

bool operator==(const Board &lhs, const Board &rhs)
{

    for (int8_t i = 0; i < 64; i++)
    {
        if (lhs.data[i] != rhs.data[i])
            return false;
    }
    return true;
}

bool operator!=(const Board &lhs, const Board &rhs)
{
    return !operator==(lhs, rhs);
}
Board::Board()
{
    for (int8_t i = 0; i < 64; i++)
    {
        data[i] = empty;
    }
}

Board::Board(const Board &other)
{

    for (int8_t i = 0; i < 64; i++)
    {
        data[i] = other.data[i];
    }
}

Board &Board::operator=(const Board &other)
{
    if (this == &other)
        return *this;

    for (int8_t i = 0; i < 64; i++)
    {
        data[i] = other.data[i];
    }
    return *this;
}

Board::Board(const char *string)
{
    for (int8_t i = 0; i < 64; i++)
    {
        data[i] = Piece(string[i]);
    }
}

Board::Board(bool from_starting_position)
{
    for (int8_t i = 0; i < 64; i++)
    {
        data[i] = empty;
    }
    data[0] = b_rook;
    data[1] = b_knight;
    data[2] = b_bishop;
    data[3] = b_queen;
    data[4] = b_king;
    data[5] = b_bishop;
    data[6] = b_knight;
    data[7] = b_rook;

    data[8] = b_pawn;
    data[9] = b_pawn;
    data[10] = b_pawn;
    data[11] = b_pawn;
    data[12] = b_pawn;
    data[13] = b_pawn;
    data[14] = b_pawn;
    data[15] = b_pawn;

    data[56] = w_rook;
    data[57] = w_knight;
    data[58] = w_bishop;
    data[59] = w_queen;
    data[60] = w_king;
    data[61] = w_bishop;
    data[62] = w_knight;
    data[63] = w_rook;

    data[48] = w_pawn;
    data[49] = w_pawn;
    data[50] = w_pawn;
    data[51] = w_pawn;
    data[52] = w_pawn;
    data[53] = w_pawn;
    data[54] = w_pawn;
    data[55] = w_pawn;
}
void Board::set_piece(uint8_t x, uint8_t y, Piece piece)
{
    data[x * 8 + y] = piece;
}
void Board::from_string(const String &board_str)
{

    for (int8_t i = 0; i < 64; i++)
    {
        switch (board_str[i])
        {
        case 'e':
            data[i] = empty;
            break;
        case 'p':
            data[i] = w_pawn;
            break;
        case 'n':
            data[i] = w_knight;
            break;
        case 'b':
            data[i] = w_bishop;
            break;
        case 'r':
            data[i] = w_rook;
            break;
        case 'q':
            data[i] = w_queen;
            break;
        case 'k':
            data[i] = w_king;
            break;
        case 'P':
            data[i] = b_pawn;
            break;
        case 'N':
            data[i] = b_knight;
            break;
        case 'B':
            data[i] = b_bishop;
            break;
        case 'R':
            data[i] = b_rook;
            break;
        case 'Q':
            data[i] = b_queen;
            break;
        case 'K':
            data[i] = b_king;
            break;
        }
    }
}

void Board::to_string(char *board_str)
{
    for (int8_t i = 0; i < 64; i++)
    {
        board_str[i] = symbol_encoding[data[i]];
    }
    board_str[64] = '\0';
}

void Board::move(int8_t prev_pos, int8_t new_pos)
{

    auto pos_x = new_pos / width;

    // MeasTime timer("move");
    if (pos_x == 0 && data[prev_pos] == w_pawn)
        // white pawn piece upgrade to queen
        data[new_pos] = w_queen;
    else if (pos_x == 7 && data[prev_pos] == b_pawn)
        // white pawn piece upgrade to queen
        data[new_pos] = b_queen;
    else
        // just a normal move
        data[new_pos] = data[prev_pos];

    data[prev_pos] = empty;
}

int8_t Board::construct_coord(int8_t x, int8_t y)
{
    return x * 8 + y;
}

/// @brief generates legal moveset for a pawn at position 'pos'
/// @param pos defines for witch pawn moveset should be calculated
/// @param moveset stores all legal possible move positions
/// @param number_of_moves noumber of moves already present in moveset array
/// @return Number of legal moves
void Board::generate_legal_moveset_pawn(int8_t pos, MoveSet &moves) const
{

    Color pawn_color = get_color(data[pos]);

    int8_t pos_x = pos / width;
    int8_t pos_y = pos % width;

    if (pawn_color == black)
    {
        // black is on top, and goes down

        if (pos_x == 1)
            if (data[pos + 16] == empty && data[pos + 8] == empty)
                moves.add_move(pos + 16);

        if (pos_x + 1 < 8)
        {
            if (data[pos + 8] == empty)
                moves.add_move(pos + 8);

            if (pos_y - 1 >= 0)
                // if pawn is not on the left edge of the chessboard
                if (is_white(data[pos + 7]))
                    moves.add_move(pos + 7);

            if (pos_y + 1 < 8)
                // if pawn is not on the right edge of the chessboard
                if (is_white(data[pos + 9]))
                    moves.add_move(pos + 9);
        }
    }
    else
    {
        // white is on the bottom, and goes up
        if (pos_x == 6)
            if (data[pos - 16] == empty && data[pos - 8] == empty)
                moves.add_move(pos - 16);

        if (pos_x - 1 >= 0)
        {
            if (data[pos - 8] == empty)
                moves.add_move(pos - 8);

            if (pos_y - 1 >= 0)
                // if pawn is not on the left edge of the chessboard
                if (is_black(data[pos - 9]))
                    moves.add_move(pos - 9);

            if (pos_y + 1 < 8)
                // if pawn is not on the right edge of the chessboard
                if (is_black(data[pos - 7]))
                    moves.add_move(pos - 7);
        }
    }
}

/// @brief generates legal moveset for a pawn at position 'pos'
/// @param pos defines for witch pawn moveset should be calculated
/// @param moveset stores all legal possible move positions
/// @param number_of_moves noumber of moves already present in moveset array
/// @return Number of legal moves
void Board::generate_legal_moveset_knight(int8_t pos, MoveSet &moves) const
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
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos + 17;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        return;
    case 1:
        //  O O
        // O   O
        //   N
        // O   X
        //  X X
        new_pos = pos + 10;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos + 15;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos + 17;
        if (get_color(data[new_pos]) != knight_color)
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
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos + 10;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos + 15;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos + 17;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        return;
    case 6:
        //  O O
        // O   O
        //   N
        // X   O
        //  X X
        new_pos = pos + 6;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos + 10;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos + 15;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);

        return;
    case TOP_RIGHT:
        //  O O
        // O   O
        //   N
        // X   O
        //  X O
        new_pos = pos + 6;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos + 15;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        return;

    case 8:
        //  O O
        // O   X
        //   N
        // O   X
        //  O X
        new_pos = pos - 6;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos + 10;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos + 17;
        if (get_color(data[new_pos]) != knight_color)
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
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos - 6;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos + 10;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos + 17;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        return;
    case 48:
        //  O X
        // O   X
        //   N
        // O   X
        //  O O
        new_pos = pos - 15;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos - 6;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos + 10;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        return;
    case 15:
        //  O O
        // X   O
        //   N
        // X   O
        //  X O

        new_pos = pos - 10;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);

        new_pos = pos + 6;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);

        new_pos = pos + 15;
        if (get_color(data[new_pos]) != knight_color)
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
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);

        new_pos = pos - 10;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);

        new_pos = pos + 6;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);

        new_pos = pos + 15;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        return;
    case 55:
        //  X O
        // X   O
        //   N
        // X   O
        //  O O

        new_pos = pos - 17;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);

        new_pos = pos - 10;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);

        new_pos = pos + 6;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);

        return;
    case BOTTOM_LEFT:
        //  O X
        // O   X
        //   N
        // O   O
        //  O O
        new_pos = pos - 15;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos - 6;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        return;
    case 57:
        //  X X
        // O   X
        //   N
        // O   O
        //  O O
        new_pos = pos - 17;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos - 15;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos - 6;
        if (get_color(data[new_pos]) != knight_color)
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
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos - 15;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos - 10;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos - 6;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        return;
    case 62:
        //  X X
        // X   O
        //   N
        // O   O
        //  O O
        new_pos = pos - 17;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos - 15;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos - 10;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        return;
    case BOTTOM_RIGHT:
        //  X O
        // X   O
        //   N
        // O   O
        //  O O
        new_pos = pos - 17;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);

        new_pos = pos - 10;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);

        return;

    case AL_TOP_LEFT:

        //  O O
        // O   X
        //   N
        // O   X
        //  X X
        new_pos = pos - 6;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos + 10;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos + 17;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos + 15;
        if (get_color(data[new_pos]) != knight_color)
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
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos - 6;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos + 6;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos + 10;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos + 15;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos + 17;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        return;
    case AL_TOP_RIGHT:
        //  O O
        // X   O
        //   N
        // X   O
        //  X X
        new_pos = pos - 10;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos + 6;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos + 15;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos + 17;
        if (get_color(data[new_pos]) != knight_color)
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
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos - 15;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos - 10;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos + 6;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos + 15;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos + 17;
        if (get_color(data[new_pos]) != knight_color)
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
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos - 15;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos - 6;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos + 10;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos + 15;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos + 17;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);

        return;
    case AL_BOTTOM_LEFT:
        //  X X
        // O   X
        //   N
        // O   X
        //  O O
        new_pos = pos - 17;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos - 15;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos - 6;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos + 10;
        if (get_color(data[new_pos]) != knight_color)
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
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos - 15;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos - 10;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos - 6;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos + 6;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos + 10;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        return;
    case AL_BOTTOM_RIGHT:
        //  X X
        // X   O
        //   N
        // X   O
        //  O O
        new_pos = pos - 17;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos - 15;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos - 10;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        new_pos = pos + 6;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);

        return;
    default:
        //  X X
        // X   X
        //   N
        // X   X
        //  X X

        new_pos = pos - 17;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);

        new_pos = pos - 15;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);

        new_pos = pos - 6;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);

        new_pos = pos + 10;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);

        new_pos = pos + 17;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);

        new_pos = pos + 15;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);

        new_pos = pos + 6;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);

        new_pos = pos - 10;
        if (get_color(data[new_pos]) != knight_color)
            moves.add_move(new_pos);
        return;
    }
}

/// @brief generates legal moveset for a pawn at position 'pos'
/// @param pos defines for witch pawn moveset should be calculated
/// @param moveset stores all legal possible move positions
/// @param number_of_moves noumber of moves already present in moveset array
/// @return Number of legal moves
void Board::generate_legal_moveset_king(const int8_t pos, MoveSet &moves) const
{

    Color king_color = get_color(data[pos]);

    int8_t pos_x = pos / width;
    int8_t pos_y = pos % width;

    int8_t new_pos;
    if (pos_x - 1 >= 0 && pos_y - 1 >= 0)
    {
        // XOO
        // OKO
        // OOO

        new_pos = pos - 9;
        if (get_color(data[new_pos]) != king_color)
            moves.add_move(new_pos);
    }
    if (pos_x - 1 >= 0)
    {
        // OXO
        // OKO
        // OOO

        new_pos = pos - 8;
        if (get_color(data[new_pos]) != king_color)
            moves.add_move(new_pos);
    }
    if (pos_x - 1 >= 0 && pos_y + 1 < 8)
    {
        // OOX
        // OKO
        // OOO

        new_pos = pos - 7;
        if (get_color(data[new_pos]) != king_color)
            moves.add_move(new_pos);
    }
    if (pos_y - 1 >= 0)
    {
        // OOO
        // XKO
        // OOO

        new_pos = pos - 1;
        if (get_color(data[new_pos]) != king_color)
            moves.add_move(new_pos);
    }
    if (pos_y + 1 < 8)
    {
        // OOO
        // OKX
        // OOO

        new_pos = pos + 1;
        if (get_color(data[new_pos]) != king_color)
            moves.add_move(new_pos);
    }
    if (pos_x + 1 < 8 && pos_y - 1 >= 0)
    {
        // OOO
        // OKO
        // XOO

        new_pos = pos + 7;
        if (get_color(data[new_pos]) != king_color)
            moves.add_move(new_pos);
    }
    if (pos_x + 1 < 8)
    {
        // OOO
        // OKO
        // OXO

        new_pos = pos + 8;
        if (get_color(data[new_pos]) != king_color)
            moves.add_move(new_pos);
    }
    if (pos_x + 1 < 8 && pos_y + 1 < 8)
    {
        // OOO
        // OKO
        // OOX

        new_pos = pos + 9;
        if (get_color(data[new_pos]) != king_color)
            moves.add_move(new_pos);
    }
}

/// @brief generates legal moveset for a pawn at position 'pos'
/// @param pos defines for witch pawn moveset should be calculated
/// @param moveset stores all legal possible move positions
/// @param number_of_moves noumber of moves already present in moveset array
/// @return Number of legal moves
void Board::generate_legal_moveset_rook(const int8_t pos, MoveSet &moves) const
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
            moves.add_move(new_pos);
        else if (get_color(data[new_pos]) != rook_color)
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
            moves.add_move(new_pos);
        else if (get_color(data[new_pos]) != rook_color)
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
            moves.add_move(new_pos);
        else if (get_color(data[new_pos]) != rook_color)
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
            moves.add_move(new_pos);
        else if (get_color(data[new_pos]) != rook_color)
        {
            moves.add_move(new_pos);
            break;
        }
        else
            break;
    }
}

/// @brief generates legal moveset for a pawn at position 'pos'
/// @param pos defines for witch pawn moveset should be calculated
/// @param moveset stores all legal possible move positions
/// @param number_of_moves noumber of moves already present in moveset array
/// @return Number of legal moves
void Board::generate_legal_moveset_bishop(const int8_t pos, MoveSet &moves) const
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
            moves.add_move(new_pos);
        else if (get_color(data[new_pos]) != bishop_color)
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
            moves.add_move(new_pos);
        else if (get_color(data[new_pos]) != bishop_color)
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
            moves.add_move(new_pos);
        else if (get_color(data[new_pos]) != bishop_color)
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
            moves.add_move(new_pos);
        else if (get_color(data[new_pos]) != bishop_color)
        {
            moves.add_move(new_pos);
            break;
        }
        else
            break;
    }
}

/// @brief generates legal moveset for a pawn at position 'pos'
/// @param pos defines for witch pawn moveset should be calculated
/// @param moveset stores all legal possible move positions
/// @param number_of_moves noumber of moves already present in moveset array
/// @return Number of legal moves
void Board::generate_legal_moveset_queen(const int8_t pos, MoveSet &moves) const
{

    //  queen is basically rook & bishop at once, so why even bother?
    generate_legal_moveset_rook(pos, moves);
    generate_legal_moveset_bishop(pos, moves);
}

/// @brief generates legal moveset for a given color
/// @param color color for which all moves possible will be generated
/// @param moveset stores all legal possible move positions
/// @return Number of legal moves
void Board::generate_legal_moveset_for_color(Color color, MoveSet &moves) const
{

    int8_t queens_position[1];

    int8_t rooks_positions[2];

    int8_t bishops_positions[2];

    int8_t knights_positions[2];

    int8_t pawns_positions[8];

    int8_t kings_position[1];

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
        generate_legal_moveset_pawn(pawns_positions[p], moves);
        moves.add_starting_position(moves.size - number_of_moves, pawns_positions[p]);
    }
    for (int8_t k = 0; k < index_table[w_knight - 1]; k++)
    {
        number_of_moves = moves.size;
        generate_legal_moveset_knight(knights_positions[k], moves);
        moves.add_starting_position(moves.size - number_of_moves, knights_positions[k]);
    }
    if (index_table[w_queen - 1] > 0)
    {
        number_of_moves = moves.size;
        generate_legal_moveset_queen(queens_position[0], moves);
        moves.add_starting_position(moves.size - number_of_moves, queens_position[0]);
    }
    for (int8_t b = 0; b < index_table[w_bishop - 1]; b++)
    {
        number_of_moves = moves.size;
        generate_legal_moveset_bishop(bishops_positions[b], moves);
        moves.add_starting_position(moves.size - number_of_moves, bishops_positions[b]);
    }
    for (int8_t r = 0; r < index_table[w_rook - 1]; r++)
    {
        number_of_moves = moves.size;
        generate_legal_moveset_rook(rooks_positions[r], moves);
        moves.add_starting_position(moves.size - number_of_moves, rooks_positions[r]);
    }
    if (index_table[w_king - 1] > 0)
    {
        number_of_moves = moves.size;
        generate_legal_moveset_king(kings_position[0], moves);
        moves.add_starting_position(moves.size - number_of_moves, kings_position[0]);
    }
}

int16_t Board::estimate_position() const
{
    int16_t estimation = 0;
    uint16_t (*table[])(const Piece *, const int8_t){
        generate_no_legal_moves_pawn,
        generate_no_legal_moves_knight,
        generate_no_legal_moves_bishop,
        generate_no_legal_moves_rook,
        generate_no_legal_moves_queen,
        generate_no_legal_moves_king,
    };

    const int8_t *placement_weight[6]{
        white_pawn_placement_weight_matrix,
        knight_placement_weight_matrix,
        bishop_placement_weight_matrix,
        rook_placement_weight_matrix,
        queen_placement_weight_matrix,
        king_placement_weight_matrix,
    };

    for (int8_t i = 0; i < 64; i++)
    {
        if (data[i] != empty)
        {
            estimation += weight_encoding[data[i]];

            int8_t index = data[i] - 1;
            if (get_color(data[i]) == black)
            {
                index -= 6;
                estimation -= 10 * table[index](data, i) - placement_weight[index][63 - i];
            }
            else
            {
                estimation += 10 * table[index](data, i) + placement_weight[index][i];
            }
        }
    }

    return estimation;
}
void Board::estimate_all_moves_for_color(const int8_t depth, Color color, MoveSet &moves, int16_t *estimations)
{
    if (color == white)
        color = black;
    else
        color = white;

    int8_t starting_position;
    Piece from;

    int8_t target_position;
    Piece to;

    for (uint8_t i = 0; i < moves.size; i++)
    {
        moves.next(starting_position, target_position);

        from = data[starting_position];
        to = data[target_position];

        move(starting_position, target_position);

        estimations[i] = alpha_beta(depth, -20000, 20000, color);

        data[starting_position] = from;
        data[target_position] = to;
    }
}

int16_t Board::alpha_beta(const int8_t depth, int16_t alpha, int16_t beta, const Color player_color)
{
    // int16_t current_estimation = estimate_position();
    // if (depth <= 0 || current_estimation < -15000 || current_estimation > 15000)
    //     return current_estimation;

    if (depth <= 0)
        return estimate_position();

    if (!check_for_white_king())
        return weight_encoding[b_king];

    if (!check_for_black_king())
        return weight_encoding[w_king];

    MoveSet moves;

    generate_legal_moveset_for_color(player_color, moves);

    int8_t starting_position;
    Piece from;

    int8_t target_position;
    Piece to;

    if (player_color == white)
    {
        if (moves.size == 0)
            return weight_encoding[b_king];

        int16_t result = weight_encoding[b_king];

        for (int8_t i = 0; i < moves.size; i++)
        {
            moves.next(starting_position, target_position);

            from = data[starting_position];
            to = data[target_position];

            move(starting_position, target_position);
            result = max(result, alpha_beta(depth - 1, alpha, beta, black));

            data[starting_position] = from;
            data[target_position] = to;

            if (result >= beta)
                break;
            alpha = max(alpha, result);
        }
        return result;
    }
    else
    {
        if (moves.size == 0)
            return weight_encoding[w_king];

        int16_t result = weight_encoding[w_king];

        for (int8_t i = 0; i < moves.size; i++)
        {

            moves.next(starting_position, target_position);

            from = data[starting_position];
            to = data[target_position];

            move(starting_position, target_position);
            result = min(result, alpha_beta(depth - 1, alpha, beta, white));

            data[starting_position] = from;
            data[target_position] = to;

            if (result <= alpha)
                break;
            beta = min(beta, result);
        }
        return result;
    }
}

// int16_t Board::pvs(const int8_t depth, int16_t alpha, int16_t beta, const Color player_color)
// {
//     int16_t current_estimation = estimate_position();
//     if (depth <= 0 || current_estimation < -15000 || current_estimation > 15000)
//         return current_estimation;

//     int8_t starting_positions[MAX_NO_MOVES_IN_EACH_BOARD];
//     int8_t moves[MAX_NO_MOVES_IN_EACH_BOARD];
//     uint8_t no_moves = generate_legal_moveset_for_color(player_color, starting_positions, moves);
//     int16_t result;
//     Piece from;
//     Piece to;

//     Color color;
//     if (player_color == white)
//         color = black;
//     else
//         color = white;

//     for (int8_t i = 0; i < no_moves; i++)
//     {
//         if (i == 0)
//         {
//             from = data[starting_positions[i]];
//             to = data[moves[i]];

//             move(starting_positions[i], moves[i]);
//             result = -pvs(depth - 1, -beta, -alpha, color);

//             data[starting_positions[i]] = from;
//             data[moves[i]] = to;
//         }
//         else
//         {
//             from = data[starting_positions[i]];
//             to = data[moves[i]];

//             move(starting_positions[i], moves[i]);
//             result = -pvs(depth - 1, -alpha - 1, -alpha, color);

//             data[starting_positions[i]] = from;
//             data[moves[i]] = to;

//             if (alpha < result && result < beta)
//             {
//                 from = data[starting_positions[i]];
//                 to = data[moves[i]];

//                 move(starting_positions[i], moves[i]);
//                 result = -pvs(depth - 1, -beta, -result, color);

//                 data[starting_positions[i]] = from;
//                 data[moves[i]] = to;
//             }
//         }
//         alpha = max(alpha, result);
//         if (alpha >= beta)
//             break;
//     }
//     return alpha;
// }

bool Board::check_for_white_king()
{
    for (int i = 63; i >= 0; i--)
        if (data[i] == w_king)
            return true;

    return false;
}
bool Board::check_for_black_king()
{
    for (int i = 0; i < 64; i++)
        if (data[i] == b_king)
            return true;
    return false;
}
