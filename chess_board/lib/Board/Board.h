#include <String.h>
#ifndef BOARD_H
#define BOARD_H
#include <stdint.h> /// for special uint tyoes like int8_t
#define MAX_NO_MOVES_IN_EACH_BOARD 100
#define MAX_NO_PIECES_ON_BOARD 32
// TODO:
//  https://www.chessprogramming.org/Simplified_Evaluation_Function

const char symbol_encoding[13]{'e', 'p', 'n', 'b', 'r', 'q', 'k', 'P', 'N', 'B', 'R', 'Q', 'K'};
const int16_t weight_encoding[13]{0, 100, 320, 330, 500, 900, 20000, -100, -320, -350, -500, -900, -20000};
const int8_t white_pawn_placement_weight_matrix[64]{0, 0, 0, 0, 0, 0, 0, 0,
                                                    50, 50, 50, 50, 50, 50, 50, 50,
                                                    10, 10, 20, 30, 30, 20, 10, 10,
                                                    5, 5, 10, 25, 25, 10, 5, 5,
                                                    0, 0, 0, 20, 20, 0, 0, 0,
                                                    5, -5, -10, 0, 0, -10, -5, 5,
                                                    5, 10, 10, -20, -20, 10, 10, 5,
                                                    0, 0, 0, 0, 0, 0, 0, 0};

const int8_t knight_placement_weight_matrix[64]{-50, -40, -30, -30, -30, -30, -40, -50,
                                                -40, -20, 0, 0, 0, 0, -20, -40,
                                                -30, 0, 10, 15, 15, 10, 0, -30,
                                                -30, 5, 15, 20, 20, 15, 5, -30,
                                                -30, 0, 15, 20, 20, 15, 0, -30,
                                                -30, 5, 10, 15, 15, 10, 5, -30,
                                                -40, -20, 0, 5, 5, 0, -20, -40,
                                                -50, -40, -30, -30, -30, -30, -40, -50};

const int8_t bishop_placement_weight_matrix[64]{-20, -10, -10, -10, -10, -10, -10, -20,
                                                -10, 0, 0, 0, 0, 0, 0, -10,
                                                -10, 0, 5, 10, 10, 5, 0, -10,
                                                -10, 5, 5, 10, 10, 5, 5, -10,
                                                -10, 0, 10, 10, 10, 10, 0, -10,
                                                -10, 10, 10, 10, 10, 10, 10, -10,
                                                -10, 5, 0, 0, 0, 0, 5, -10,
                                                -20, -10, -10, -10, -10, -10, -10, -20};

const int8_t rook_placement_weight_matrix[64]{0, 0, 0, 0, 0, 0, 0, 0,
                                              5, 10, 10, 10, 10, 10, 10, 5,
                                              -5, 0, 0, 0, 0, 0, 0, -5,
                                              -5, 0, 0, 0, 0, 0, 0, -5,
                                              -5, 0, 0, 0, 0, 0, 0, -5,
                                              -5, 0, 0, 0, 0, 0, 0, -5,
                                              -5, 0, 0, 0, 0, 0, 0, -5,
                                              0, 0, 0, 5, 5, 0, 0, 0};

const int8_t queen_placement_weight_matrix[64]{-20, -10, -10, -5, -5, -10, -10, -20,
                                               -10, 0, 0, 0, 0, 0, 0, -10,
                                               -10, 0, 5, 5, 5, 5, 0, -10,
                                               -5, 0, 5, 5, 5, 5, 0, -5,
                                               0, 0, 5, 5, 5, 5, 0, -5,
                                               -10, 5, 5, 5, 5, 5, 0, -10,
                                               -10, 0, 5, 0, 0, 0, 0, -10,
                                               -20, -10, -10, -5, -5, -10, -10, -20};
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
inline bool is_white(Piece piece)
{
    if (piece >= w_pawn && piece <= w_king)
        return true;
    return false;
}
inline bool is_black(Piece piece)
{
    if (piece >= b_pawn && piece <= b_king)
        return true;
    return false;
}

enum Color : int8_t
{
    no_color,
    white,
    black,
};

inline Color get_color(Piece piece)
{
    if (piece >= w_pawn && piece <= w_king)
        return white;
    if (piece >= b_pawn && piece <= b_king)
        return black;
    return no_color;
}
Color reverse_color(const Color current_color)
{
    if (current_color == white)
        return black;
    if (current_color == black)
        return white;
    return current_color;
}
class Board
{

public:
    Piece data[64];
    const int8_t width = 8;
    const int8_t height = 8;

public:
    Board()
    {
        for (int8_t i = 0; i < 64; i++)
        {
            data[i] = empty;
        }
    }
    Board(const Board &copy)
    {
        for (int8_t i = 0; i < 64; i++)
        {
            data[i] = copy.data[i];
        }
    }
    Board(const char *string)
    {
        for (int8_t i = 0; i < 64; i++)
        {
            data[i] = Piece(string[i]);
        }
    }
    Board(bool from_starting_position)
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

    inline void set_piece(uint8_t x, uint8_t y, Piece piece)
    {
        data[x * 8 + y] = piece;
    }

    inline void from_string(const String &board_str)
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

    inline void to_string(char *board_str)
    {
        for (int8_t i = 0; i < 64; i++)
        {
            board_str[i] = symbol_encoding[data[i]];
        }
        board_str[64] = '\0';
    }
    inline void move(int8_t prev_pos, int8_t new_pos)
    {
        if (new_pos / width == 0 && data[prev_pos] == w_pawn)
            // white pawn piece upgrade to queen
            data[new_pos] = w_queen;
        else if (new_pos / width == 7 && data[prev_pos] == b_pawn)
            // white pawn piece upgrade to queen
            data[new_pos] = b_queen;
        else
            // just a normal move
            data[new_pos] = data[prev_pos];

        data[prev_pos] = empty;
    }

    inline int8_t construct_coord(int8_t x, int8_t y) const
    {
        return x * 8 + y;
    }
    inline int8_t deconstruct_coord_x(int8_t coord) const
    {
        return coord / 8;
    }
    inline int8_t deconstruct_coord_y(int8_t coord) const
    {
        return coord % 8;
    }

    /// @brief generates legal moveset for a pawn at position 'pos'
    /// @param pos defines for witch pawn moveset should be calculated
    /// @param moveset stores all legal possible move positions
    /// @param number_of_moves noumber of moves already present in moveset array
    /// @return Number of legal moves
    inline int8_t generate_legal_moveset_pawn(int8_t pos, int8_t *moveset, int8_t number_of_moves = 0) const
    {

        Color pawn_color = get_color(data[pos]);

        int8_t pos_x = pos / width;
        int8_t pos_y = pos % width;

        if (pawn_color == black)
        {
            // black is on top, and goes down

            if (pos_x == 1)
                if (data[construct_coord(pos_x + 2, pos_y)] == empty && data[construct_coord(pos_x + 1, pos_y)] == empty)
                    moveset[number_of_moves++] = construct_coord(pos_x + 2, pos_y);

            if (pos_x + 1 < 8)
            {
                if (data[construct_coord(pos_x + 1, pos_y)] == empty)
                    moveset[number_of_moves++] = construct_coord(pos_x + 1, pos_y);

                if (pos_y - 1 >= 0)
                    // if pawn is not on the left edge of the chessboard
                    if (is_white(data[construct_coord(pos_x + 1, pos_y - 1)]))
                        moveset[number_of_moves++] = construct_coord(pos_x + 1, pos_y - 1);

                if (pos_y + 1 < 8)
                    // if pawn is not on the right edge of the chessboard
                    if (is_white(data[construct_coord(pos_x + 1, pos_y + 1)]))
                        moveset[number_of_moves++] = construct_coord(pos_x + 1, pos_y + 1);
            }
        }
        else
        {
            // white is on the bottom, and goes up
            if (pos_x == 6)
                if (data[construct_coord(pos_x - 2, pos_y)] == empty && data[construct_coord(pos_x - 1, pos_y)] == empty)
                    moveset[number_of_moves++] = construct_coord(pos_x - 2, pos_y);

            if (pos_x - 1 >= 0)
            {
                if (data[construct_coord(pos_x - 1, pos_y)] == empty)
                    moveset[number_of_moves++] = construct_coord(pos_x - 1, pos_y);

                if (pos_y - 1 >= 0)
                    // if pawn is not on the left edge of the chessboard
                    if (is_black(data[construct_coord(pos_x - 1, pos_y - 1)]))
                        moveset[number_of_moves++] = construct_coord(pos_x - 1, pos_y - 1);

                if (pos_y + 1 < 8)
                    // if pawn is not on the right edge of the chessboard
                    if (is_black(data[construct_coord(pos_x - 1, pos_y + 1)]))
                        moveset[number_of_moves++] = construct_coord(pos_x - 1, pos_y + 1);
            }
        }

        return number_of_moves;
    }

    /// @brief generates noumber of legal moves for a pawn at position 'pos'
    /// @param pos defines for witch pawn moveset should be calculated
    /// @param number_of_moves noumber of moves already present in moveset array
    /// @return Number of legal moves
    inline int8_t generate_no_legal_moves_pawn(int8_t pos, uint8_t number_of_moves = 0) const
    {

        Color pawn_color = get_color(data[pos]);

        int8_t pos_x = pos / width;
        int8_t pos_y = pos % width;

        if (pawn_color == black)
        {
            // black is on top, and goes down

            if (pos_x == 1)
                if (data[construct_coord(pos_x + 2, pos_y)] == empty && data[construct_coord(pos_x + 1, pos_y)] == empty)
                    number_of_moves++;

            if (pos_x + 1 < 8)
            {
                if (data[construct_coord(pos_x + 1, pos_y)] == empty)
                    number_of_moves++;

                if (pos_y - 1 >= 0)
                    // if pawn is not on the left edge of the chessboard
                    if (is_white(data[construct_coord(pos_x + 1, pos_y - 1)]))
                        number_of_moves++;

                if (pos_y + 1 < 8)
                    // if pawn is not on the right edge of the chessboard
                    if (is_white(data[construct_coord(pos_x + 1, pos_y + 1)]))
                        number_of_moves++;
            }
        }
        else
        {
            // white is on the bottom, and goes up
            if (pos_x == 6)
                if (data[construct_coord(pos_x - 2, pos_y)] == empty && data[construct_coord(pos_x - 1, pos_y)] == empty)
                    number_of_moves++;

            if (pos_x - 1 >= 0)
            {
                if (data[construct_coord(pos_x - 1, pos_y)] == empty)
                    number_of_moves++;

                if (pos_y - 1 >= 0)
                    // if pawn is not on the left edge of the chessboard
                    if (is_black(data[construct_coord(pos_x - 1, pos_y - 1)]))
                        number_of_moves++;

                if (pos_y + 1 < 8)
                    // if pawn is not on the right edge of the chessboard
                    if (is_black(data[construct_coord(pos_x - 1, pos_y + 1)]))
                        number_of_moves++;
            }
        }

        return number_of_moves;
    }

    /// @brief generates legal moveset for a pawn at position 'pos'
    /// @param pos defines for witch pawn moveset should be calculated
    /// @param moveset stores all legal possible move positions
    /// @param number_of_moves noumber of moves already present in moveset array
    /// @return Number of legal moves
    inline int8_t generate_legal_moveset_knight(int8_t pos, int8_t *moveset, int8_t number_of_moves = 0) const
    {

        Color knight_color = get_color(data[pos]);

        int8_t pos_x = pos / width;
        int8_t pos_y = pos % width;

        int8_t new_pos;
        if (pos_x - 2 >= 0 && pos_y - 1 >= 0)
        {
            //  X O
            // O   O
            //   N
            // O   O
            //  O O
            new_pos = construct_coord(pos_x - 2, pos_y - 1);
            if (get_color(data[new_pos]) != knight_color)
                moveset[number_of_moves++] = new_pos;
        }

        if (pos_x - 2 >= 0 && pos_y + 1 < 8)
        {
            //  O X
            // O   O
            //   N
            // O   O
            //  O O
            new_pos = construct_coord(pos_x - 2, pos_y + 1);
            if (get_color(data[new_pos]) != knight_color)
                moveset[number_of_moves++] = new_pos;
        }
        if (pos_x - 1 >= 0 && pos_y + 2 < 8)
        {
            //  O O
            // O   X
            //   N
            // O   O
            //  O O
            new_pos = construct_coord(pos_x - 1, pos_y + 2);
            if (get_color(data[new_pos]) != knight_color)
                moveset[number_of_moves++] = new_pos;
        }
        if (pos_x + 1 < 8 && pos_y + 2 < 8)
        {
            //  O O
            // O   O
            //   N
            // O   X
            //  O O
            new_pos = construct_coord(pos_x + 1, pos_y + 2);
            if (get_color(data[new_pos]) != knight_color)
                moveset[number_of_moves++] = new_pos;
        }
        if (pos_x + 2 < 8 && pos_y + 1 < 8)
        {
            //  O O
            // O   O
            //   N
            // O   O
            //  O X
            new_pos = construct_coord(pos_x + 2, pos_y + 1);
            if (get_color(data[new_pos]) != knight_color)
                moveset[number_of_moves++] = new_pos;
        }
        if (pos_x + 2 < 8 && pos_y - 1 >= 0)
        {
            //  O O
            // O   O
            //   N
            // O   O
            //  X O
            new_pos = construct_coord(pos_x + 2, pos_y - 1);
            if (get_color(data[new_pos]) != knight_color)
                moveset[number_of_moves++] = new_pos;
        }
        if (pos_x + 1 < 8 && pos_y - 2 >= 0)
        {
            //  O O
            // O   O
            //   N
            // X   O
            //  O O
            new_pos = construct_coord(pos_x + 1, pos_y - 2);
            if (get_color(data[new_pos]) != knight_color)
                moveset[number_of_moves++] = new_pos;
        }
        if (pos_x - 1 >= 0 && pos_y - 2 >= 0)
        {
            //  O O
            // X   O
            //   N
            // O   O
            //  O O
            new_pos = construct_coord(pos_x - 1, pos_y - 2);
            if (get_color(data[new_pos]) != knight_color)
                moveset[number_of_moves++] = new_pos;
        }

        return number_of_moves;
    }

    /// @brief generates noumber of legal moves for a pawn at position 'pos'
    /// @param pos defines for witch pawn moveset should be calculated
    /// @param number_of_moves noumber of moves already present in moveset array
    /// @return Number of legal moves
    inline int8_t generate_no_legal_moves_knight(int8_t pos, int8_t number_of_moves = 0) const
    {

        Color knight_color = get_color(data[pos]);

        int8_t pos_x = pos / width;
        int8_t pos_y = pos % width;

        int8_t new_pos;
        if (pos_x - 2 >= 0 && pos_y - 1 >= 0)
        {
            //  X O
            // O   O
            //   N
            // O   O
            //  O O
            new_pos = construct_coord(pos_x - 2, pos_y - 1);
            if (get_color(data[new_pos]) != knight_color)
                number_of_moves++;
        }

        if (pos_x - 2 >= 0 && pos_y + 1 < 8)
        {
            //  O X
            // O   O
            //   N
            // O   O
            //  O O
            new_pos = construct_coord(pos_x - 2, pos_y + 1);
            if (get_color(data[new_pos]) != knight_color)
                number_of_moves++;
        }
        if (pos_x - 1 >= 0 && pos_y + 2 < 8)
        {
            //  O O
            // O   X
            //   N
            // O   O
            //  O O
            new_pos = construct_coord(pos_x - 1, pos_y + 2);
            if (get_color(data[new_pos]) != knight_color)
                number_of_moves++;
        }
        if (pos_x + 1 < 8 && pos_y + 2 < 8)
        {
            //  O O
            // O   O
            //   N
            // O   X
            //  O O
            new_pos = construct_coord(pos_x + 1, pos_y + 2);
            if (get_color(data[new_pos]) != knight_color)
                number_of_moves++;
        }
        if (pos_x + 2 < 8 && pos_y + 1 < 8)
        {
            //  O O
            // O   O
            //   N
            // O   O
            //  O X
            new_pos = construct_coord(pos_x + 2, pos_y + 1);
            if (get_color(data[new_pos]) != knight_color)
                number_of_moves++;
        }
        if (pos_x + 2 < 8 && pos_y - 1 >= 0)
        {
            //  O O
            // O   O
            //   N
            // O   O
            //  X O
            new_pos = construct_coord(pos_x + 2, pos_y - 1);
            if (get_color(data[new_pos]) != knight_color)
                number_of_moves++;
        }
        if (pos_x + 1 < 8 && pos_y - 2 >= 0)
        {
            //  O O
            // O   O
            //   N
            // X   O
            //  O O
            new_pos = construct_coord(pos_x + 1, pos_y - 2);
            if (get_color(data[new_pos]) != knight_color)
                number_of_moves++;
        }
        if (pos_x - 1 >= 0 && pos_y - 2 >= 0)
        {
            //  O O
            // X   O
            //   N
            // O   O
            //  O O
            new_pos = construct_coord(pos_x - 1, pos_y - 2);
            if (get_color(data[new_pos]) != knight_color)
                number_of_moves++;
        }

        return number_of_moves;
    }

    /// @brief generates legal moveset for a pawn at position 'pos'
    /// @param pos defines for witch pawn moveset should be calculated
    /// @param moveset stores all legal possible move positions
    /// @param number_of_moves noumber of moves already present in moveset array
    /// @return Number of legal moves
    inline int8_t generate_legal_moveset_king(const int8_t pos, int8_t *moveset, int8_t number_of_moves = 0) const
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

            new_pos = construct_coord(pos_x - 1, pos_y - 1);
            if (get_color(data[new_pos]) != king_color)
                moveset[number_of_moves++] = new_pos;
        }
        if (pos_x - 1 >= 0)
        {
            // OXO
            // OKO
            // OOO

            new_pos = construct_coord(pos_x - 1, pos_y);
            if (get_color(data[new_pos]) != king_color)
                moveset[number_of_moves++] = new_pos;
        }
        if (pos_x - 1 >= 0 && pos_y + 1 < 8)
        {
            // OOX
            // OKO
            // OOO

            new_pos = construct_coord(pos_x - 1, pos_y + 1);
            if (get_color(data[new_pos]) != king_color)
                moveset[number_of_moves++] = new_pos;
        }
        if (pos_y - 1 >= 0)
        {
            // OOO
            // XKO
            // OOO

            new_pos = construct_coord(pos_x, pos_y - 1);
            if (get_color(data[new_pos]) != king_color)
                moveset[number_of_moves++] = new_pos;
        }
        if (pos_y + 1 < 8)
        {
            // OOO
            // OKX
            // OOO

            new_pos = construct_coord(pos_x, pos_y + 1);
            if (get_color(data[new_pos]) != king_color)
                moveset[number_of_moves++] = new_pos;
        }
        if (pos_x + 1 < 8 && pos_y - 1 >= 0)
        {
            // OOO
            // OKO
            // XOO

            new_pos = construct_coord(pos_x + 1, pos_y - 1);
            if (get_color(data[new_pos]) != king_color)
                moveset[number_of_moves++] = new_pos;
        }
        if (pos_x + 1 < 8)
        {
            // OOO
            // OKO
            // OXO

            new_pos = construct_coord(pos_x + 1, pos_y);
            if (get_color(data[new_pos]) != king_color)
                moveset[number_of_moves++] = new_pos;
        }
        if (pos_x + 1 < 8 && pos_y + 1 < 8)
        {
            // OOO
            // OKO
            // OOX

            new_pos = construct_coord(pos_x + 1, pos_y + 1);
            if (get_color(data[new_pos]) != king_color)
                moveset[number_of_moves++] = new_pos;
        }
        return number_of_moves;
    }

    /// @brief generates noumber of legal moves for a pawn at position 'pos'
    /// @param pos defines for witch pawn moveset should be calculated
    /// @param number_of_moves noumber of moves already present in moveset array
    /// @return Number of legal moves
    inline int8_t generate_no_legal_moves_king(const int8_t pos, int8_t number_of_moves = 0) const
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

            new_pos = construct_coord(pos_x - 1, pos_y - 1);
            if (get_color(data[new_pos]) != king_color)
                number_of_moves++;
        }
        if (pos_x - 1 >= 0)
        {
            // OXO
            // OKO
            // OOO

            new_pos = construct_coord(pos_x - 1, pos_y);
            if (get_color(data[new_pos]) != king_color)
                number_of_moves++;
        }
        if (pos_x - 1 >= 0 && pos_y + 1 < 8)
        {
            // OOX
            // OKO
            // OOO

            new_pos = construct_coord(pos_x - 1, pos_y + 1);
            if (get_color(data[new_pos]) != king_color)
                number_of_moves++;
        }
        if (pos_y - 1 >= 0)
        {
            // OOO
            // XKO
            // OOO

            new_pos = construct_coord(pos_x, pos_y - 1);
            if (get_color(data[new_pos]) != king_color)
                number_of_moves++;
        }
        if (pos_y + 1 < 8)
        {
            // OOO
            // OKX
            // OOO

            new_pos = construct_coord(pos_x, pos_y + 1);
            if (get_color(data[new_pos]) != king_color)
                number_of_moves++;
        }
        if (pos_x + 1 < 8 && pos_y - 1 >= 0)
        {
            // OOO
            // OKO
            // XOO

            new_pos = construct_coord(pos_x + 1, pos_y - 1);
            if (get_color(data[new_pos]) != king_color)
                number_of_moves++;
        }
        if (pos_x + 1 < 8)
        {
            // OOO
            // OKO
            // OXO

            new_pos = construct_coord(pos_x + 1, pos_y);
            if (get_color(data[new_pos]) != king_color)
                number_of_moves++;
        }
        if (pos_x + 1 < 8 && pos_y + 1 < 8)
        {
            // OOO
            // OKO
            // OOX

            new_pos = construct_coord(pos_x + 1, pos_y + 1);
            if (get_color(data[new_pos]) != king_color)
                number_of_moves++;
        }
        return number_of_moves;
    }

    /// @brief generates legal moveset for a pawn at position 'pos'
    /// @param pos defines for witch pawn moveset should be calculated
    /// @param moveset stores all legal possible move positions
    /// @param number_of_moves noumber of moves already present in moveset array
    /// @return Number of legal moves
    inline uint8_t generate_legal_moveset_rook(const int8_t pos, int8_t *moveset, int8_t number_of_moves = 0) const
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
                moveset[number_of_moves++] = new_pos;
            else if (get_color(data[new_pos]) != rook_color)
            {
                moveset[number_of_moves++] = new_pos;
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
                moveset[number_of_moves++] = new_pos;
            else if (get_color(data[new_pos]) != rook_color)
            {
                moveset[number_of_moves++] = new_pos;
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
                moveset[number_of_moves++] = new_pos;
            else if (get_color(data[new_pos]) != rook_color)
            {
                moveset[number_of_moves++] = new_pos;
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
                moveset[number_of_moves++] = new_pos;
            else if (get_color(data[new_pos]) != rook_color)
            {
                moveset[number_of_moves++] = new_pos;
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
    inline uint8_t generate_no_legal_moves_rook(const int8_t pos, int8_t number_of_moves = 0) const
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
            new_pos = construct_coord(x, pos_y);
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
            new_pos = construct_coord(pos_x, y);
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
            new_pos = construct_coord(pos_x, y);
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

    /// @brief generates legal moveset for a pawn at position 'pos'
    /// @param pos defines for witch pawn moveset should be calculated
    /// @param moveset stores all legal possible move positions
    /// @param number_of_moves noumber of moves already present in moveset array
    /// @return Number of legal moves
    inline uint8_t generate_legal_moveset_bishop(const int8_t pos, int8_t *moveset, int8_t number_of_moves = 0) const
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
                moveset[number_of_moves++] = new_pos;
            else if (get_color(data[new_pos]) != bishop_color)
            {
                moveset[number_of_moves++] = new_pos;
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
                moveset[number_of_moves++] = new_pos;
            else if (get_color(data[new_pos]) != bishop_color)
            {
                moveset[number_of_moves++] = new_pos;
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
                moveset[number_of_moves++] = new_pos;
            else if (get_color(data[new_pos]) != bishop_color)
            {
                moveset[number_of_moves++] = new_pos;
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
                moveset[number_of_moves++] = new_pos;
            else if (get_color(data[new_pos]) != bishop_color)
            {
                moveset[number_of_moves++] = new_pos;
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
    inline uint8_t generate_no_legal_moves_bishop(const int8_t pos, int8_t number_of_moves = 0) const
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
            new_pos = construct_coord(x, y);
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
            new_pos = construct_coord(x, y);
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
            new_pos = construct_coord(x, y);
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

    /// @brief generates legal moveset for a pawn at position 'pos'
    /// @param pos defines for witch pawn moveset should be calculated
    /// @param moveset stores all legal possible move positions
    /// @param number_of_moves noumber of moves already present in moveset array
    /// @return Number of legal moves
    inline uint8_t generate_legal_moveset_queen(const int8_t pos, int8_t *moveset, int8_t number_of_moves = 0) const
    {
        // queen is basically rook & bishop at once, so why even bother?
        number_of_moves = generate_legal_moveset_rook(pos, moveset, number_of_moves);
        number_of_moves = generate_legal_moveset_bishop(pos, moveset, number_of_moves);

        return number_of_moves;
    }

    /// @brief generates noumber of legal moves for a pawn at position 'pos'
    /// @param pos defines for witch pawn moveset should be calculated
    /// @param number_of_moves noumber of moves already present in moveset array
    /// @return Number of legal moves
    inline uint8_t generate_no_legal_moves_queen(const int8_t pos, int8_t number_of_moves = 0) const
    {
        // queen is basically rook & bishop at once, so why even bother?
        number_of_moves = generate_no_legal_moves_rook(pos, number_of_moves);
        number_of_moves = generate_no_legal_moves_bishop(pos, number_of_moves);

        return number_of_moves;
    }

    /// @brief generates legal moveset for a given color
    /// @param color color for which all moves possible will be generated
    /// @param moveset stores all legal possible move positions
    /// @return Number of legal moves
    inline uint8_t generate_legal_moveset_for_color(Color color, int8_t *starting_positions, int8_t *moveset) const
    {

        int8_t queens_position = -1;

        int8_t rooks_positions[2];
        int8_t rooks_index = 0;

        int8_t bishops_positions[2];
        int8_t bishops_index = 0;

        int8_t knights_positions[2];
        int8_t knights_index = 0;

        int8_t pawns_positions[8];
        int8_t pawns_index = 0;

        int8_t kings_position = -1;

        for (int8_t i = 0; i < 64; i++)
        {
            if (get_color(data[i]) == color)
                switch (data[i])
                {
                case w_pawn:
                    pawns_positions[pawns_index++] = i;
                    break;
                case w_knight:
                    knights_positions[knights_index++] = i;
                    break;
                case w_bishop:
                    bishops_positions[bishops_index++] = i;
                    break;
                case w_rook:
                    rooks_positions[rooks_index++] = i;
                    break;
                case w_queen:
                    queens_position = i;
                    break;
                case w_king:
                    kings_position = i;
                    break;
                case b_pawn:
                    pawns_positions[pawns_index++] = i;
                    break;
                case b_knight:
                    knights_positions[knights_index++] = i;
                    break;
                case b_bishop:
                    bishops_positions[bishops_index++] = i;
                    break;
                case b_rook:
                    rooks_positions[rooks_index++] = i;
                    break;
                case b_queen:
                    queens_position = i;
                    break;
                case b_king:
                    kings_position = i;
                    break;
                default:
                    break;
                }
        }

        int number_of_moves = 0;
        int new_no_moves;

        for (int8_t p = 0; p < pawns_index; p++)
        {
            new_no_moves = generate_legal_moveset_pawn(pawns_positions[p], moveset, number_of_moves);
            for (int8_t j = number_of_moves; j < new_no_moves; j++)
                starting_positions[j] = pawns_positions[p];
            number_of_moves = new_no_moves;
        }
        for (int8_t k = 0; k < knights_index; k++)
        {
            new_no_moves = generate_legal_moveset_knight(knights_positions[k], moveset, number_of_moves);
            for (int8_t j = number_of_moves; j < new_no_moves; j++)
                starting_positions[j] = knights_positions[k];
            number_of_moves = new_no_moves;
        }
        if (queens_position != -1)
        {
            new_no_moves = generate_legal_moveset_queen(queens_position, moveset, number_of_moves);
            for (int8_t j = number_of_moves; j < new_no_moves; j++)
                starting_positions[j] = queens_position;
            number_of_moves = new_no_moves;
        }
        for (int8_t b = 0; b < bishops_index; b++)
        {
            new_no_moves = generate_legal_moveset_bishop(bishops_positions[b], moveset, number_of_moves);
            for (int8_t j = number_of_moves; j < new_no_moves; j++)
                starting_positions[j] = bishops_positions[b];
            number_of_moves = new_no_moves;
        }
        for (int8_t r = 0; r < rooks_index; r++)
        {
            new_no_moves = generate_legal_moveset_rook(rooks_positions[r], moveset, number_of_moves);
            for (int8_t j = number_of_moves; j < new_no_moves; j++)
                starting_positions[j] = rooks_positions[r];
            number_of_moves = new_no_moves;
        }
        if (kings_position != -1)
        {
            new_no_moves = generate_legal_moveset_king(kings_position, moveset, number_of_moves);
            for (int8_t j = number_of_moves; j < new_no_moves; j++)
                starting_positions[j] = kings_position;
            number_of_moves = new_no_moves;
        }

        return number_of_moves;
    }

    inline int16_t estimate_position() const
    {
        int16_t estimation = 0;
        for (int8_t i = 0; i < 64; i++)
        {
            if (data[i] != empty)
            {
                estimation += weight_encoding[data[i]];

                switch (data[i])
                {
                case b_pawn:
                    estimation -= 10 * generate_no_legal_moves_pawn(i);
                    estimation -= white_pawn_placement_weight_matrix[63 - i];
                    break;
                case w_pawn:
                    estimation += 10 * generate_no_legal_moves_pawn(i);
                    estimation += white_pawn_placement_weight_matrix[i];
                    break;
                case b_knight:
                    estimation -= 10 * generate_no_legal_moves_knight(i);
                    estimation -= knight_placement_weight_matrix[63 - i];
                    break;
                case w_knight:
                    estimation += 10 * generate_no_legal_moves_knight(i);
                    estimation += knight_placement_weight_matrix[i];
                    break;
                case b_king:
                    estimation -= 10 * generate_no_legal_moves_king(i);
                    break;
                case w_king:
                    estimation += 10 * generate_no_legal_moves_king(i);
                    break;
                case b_rook:
                    estimation -= 10 * generate_no_legal_moves_rook(i);
                    estimation -= rook_placement_weight_matrix[63 - i];
                    break;
                case w_rook:
                    estimation += 10 * generate_no_legal_moves_rook(i);
                    estimation += rook_placement_weight_matrix[i];
                    break;
                case b_bishop:
                    estimation -= 10 * generate_no_legal_moves_bishop(i);
                    estimation -= bishop_placement_weight_matrix[63 - i];
                    break;
                case w_bishop:
                    estimation += 10 * generate_no_legal_moves_bishop(i);
                    estimation += bishop_placement_weight_matrix[i];
                    break;
                case b_queen:
                    estimation -= 10 * generate_no_legal_moves_queen(i);
                    estimation -= queen_placement_weight_matrix[63 - i];
                    break;
                case w_queen:
                    estimation += 10 * generate_no_legal_moves_queen(i);
                    estimation += queen_placement_weight_matrix[i];
                    break;
                default:
                    break;
                }
            }
        }
        return estimation;
    }
    inline void estimate_all_moves_for_color(const int8_t depth, Color color, const uint8_t no_moves, int8_t *starting_positions, int8_t *moveset, int16_t *estimations)
    {
        if (color == white)
            color = black;
        else
            color = white;

        for (uint8_t i = 0; i < no_moves; i++)
        {

            auto from = data[starting_positions[i]];
            auto to = data[moveset[i]];

            move(starting_positions[i], moveset[i]);

            estimations[i] = alpha_beta(depth, -20000, 20000, color);

            data[starting_positions[i]] = from;
            data[moveset[i]] = to;
        }
    }

    int16_t alpha_beta(const int8_t depth, int16_t alpha, int16_t beta, const Color player_color)
    {

        int16_t current_estimation = estimate_position();
        if (depth <= 0 || current_estimation < -15000 || current_estimation > 15000)
            return current_estimation;

        int8_t starting_positions[MAX_NO_MOVES_IN_EACH_BOARD];
        int8_t moves[MAX_NO_MOVES_IN_EACH_BOARD];
        uint8_t no_moves = generate_legal_moveset_for_color(player_color, starting_positions, moves);

        Piece from;
        Piece to;
        if (player_color == white)
        {
            if (no_moves == 0)
                return -20000;
            int16_t result = -20000;
            for (int8_t i = 0; i < no_moves; i++)
            {
                from = data[starting_positions[i]];
                to = data[moves[i]];

                move(starting_positions[i], moves[i]);
                result = max(result, alpha_beta(depth - 1, alpha, beta, black));

                data[starting_positions[i]] = from;
                data[moves[i]] = to;

                if (result >= beta)
                    break;
                alpha = max(alpha, result);
            }
            return result;
        }
        else
        {
            if (no_moves == 0)
                return 20000;
            int16_t result = 20000;
            for (int8_t i = 0; i < no_moves; i++)
            {

                from = data[starting_positions[i]];
                to = data[moves[i]];

                move(starting_positions[i], moves[i]);
                result = min(result, alpha_beta(depth - 1, alpha, beta, white));

                data[starting_positions[i]] = from;
                data[moves[i]] = to;

                if (result <= alpha)
                    break;
                beta = min(beta, result);
            }
            return result;
        }
    }

    // float alpha_beta_but_linear(const int depth, float alpha, float beta, const Color player_color)
    // {

    //     int8_t **moves = new int8_t *[depth];
    //     int8_t **starting_positions = new int8_t *[depth];
    //     int *no_moves = new int[depth];
    //     for (int i = 0; i < depth; i++)
    //     {
    //         moves[i] = new int8_t[MAX_NO_MOVES_IN_EACH_BOARD];
    //         starting_positions[i] = new int8_t[MAX_NO_MOVES_IN_EACH_BOARD];
    //     }

    //     for (int iteration = 0; iteration < depth; iteration++)
    //     {
    //         float current_estimation = estimate_position();
    //         if (current_estimation < -900 || current_estimation > 900)
    //             return current_estimation;

    //         no_moves[iteration] = generate_legal_moveset_for_color(player_color, starting_positions[iteration], moves[iteration]);

    //         Piece from;
    //         Piece to;
    //         if (player_color == white)
    //         {
    //             if (no_moves == 0)
    //                 return -1000;
    //             float result = -1000;
    //             for (int i = 0; i < no_moves; i++)
    //             {
    //                 from = data[starting_positions[iteration][i]];
    //                 to = data[moves[iteration][i]];

    //                 move(starting_positions[iteration][i], moves[iteration][i]);
    //                 result = max(result, alpha_beta(depth - 1, alpha, beta, black));

    //                 data[starting_positions[iteration][i]] = from;
    //                 data[moves[iteration][i]] = to;

    //                 alpha = max(alpha, result);
    //                 if (result >= beta)
    //                     break;
    //             }
    //             return result;
    //         }
    //         else
    //         {
    //             if (no_moves == 0)
    //                 return 1000;
    //             float result = 1000;
    //             for (int i = 0; i < no_moves; i++)
    //             {

    //                 from = data[starting_positions[iteration][i]];
    //                 to = data[moves[iteration][i]];

    //                 move(starting_positions[iteration][i], moves[iteration][i]);
    //                 result = min(result, alpha_beta(depth - 1, alpha, beta, white));

    //                 data[starting_positions[iteration][i]] = from;
    //                 data[moves[iteration][i]] = to;

    //                 beta = min(beta, result);
    //                 if (result <= alpha)
    //                     break;
    //             }
    //             return result;
    //         }
    //     }
    // }
};

#endif