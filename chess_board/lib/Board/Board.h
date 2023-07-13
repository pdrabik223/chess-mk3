#include <String.h>
#ifndef BOARD_H
#define BOARD_H
#include <stdint.h> /// for special uint tyoes like int8_t
#define MAX_NO_MOVES_IN_EACH_BOARD 128

const int8_t symbol_encoding[13]{'e', 'p', 'n', 'b', 'r', 'q', 'k', 'P', 'N', 'B', 'R', 'Q', 'K'};
const int weight_encoding[13]{0, 1, 3, 3, 5, 9, 1000, -1, -3, -3, -5, -9, -1000};

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
bool is_white(Piece piece)
{
    if (piece >= w_pawn && piece <= w_king)
        return true;
    return false;
}
bool is_black(Piece piece)
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

Color get_color(Piece piece)
{
    if (piece >= w_pawn && piece <= w_king)
        return white;
    if (piece >= b_pawn && piece <= b_king)
        return black;
    return no_color;
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

    void set_piece(uint8_t x, uint8_t y, Piece piece)
    {
        data[x * 8 + y] = piece;
    }

    Piece &get_piece(const int8_t position)
    {
        if (position < 0 || position > 64)
            Serial.println("error in get_piece position is:" + position);
        return data[position];
    }

    void from_string(const String &board_str)
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

    void to_string(char *board_str)
    {
        for (int8_t i = 0; i < 64; i++)
        {
            board_str[i] = symbol_encoding[data[i]];
        }
        board_str[64] = '\0';
    }
    void move(int8_t prev_pos, int8_t new_pos)
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

    int8_t construct_coord(int8_t x, int8_t y) const
    {
        return x * 8 + y;
    }
    int8_t deconstruct_coord_x(int8_t coord) const
    {
        return coord / 8;
    }
    int8_t deconstruct_coord_y(int8_t coord) const
    {
        return coord % 8;
    }

    /// @brief generates legal moveset for a pawn at position 'pos'
    /// @param pos defines for witch pawn moveset should be calculated
    /// @param moveset stores all legal possible move positions
    /// @param number_of_moves noumber of moves already present in moveset array
    /// @return Number of legal moves
    int generate_legal_moveset_pawn(int8_t pos, int8_t *moveset, int8_t number_of_moves = 0) const
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

    /// @brief generates legal moveset for a pawn at position 'pos'
    /// @param pos defines for witch pawn moveset should be calculated
    /// @param moveset stores all legal possible move positions
    /// @param number_of_moves noumber of moves already present in moveset array
    /// @return Number of legal moves
    int generate_legal_moveset_knight(int8_t pos, int8_t *moveset, int8_t number_of_moves = 0) const
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
    /// @brief generates legal moveset for a pawn at position 'pos'
    /// @param pos defines for witch pawn moveset should be calculated
    /// @param moveset stores all legal possible move positions
    /// @param number_of_moves noumber of moves already present in moveset array
    /// @return Number of legal moves
    int generate_legal_moveset_king(const int8_t pos, int8_t *moveset, int8_t number_of_moves = 0) const
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
    /// @brief generates legal moveset for a pawn at position 'pos'
    /// @param pos defines for witch pawn moveset should be calculated
    /// @param moveset stores all legal possible move positions
    /// @param number_of_moves noumber of moves already present in moveset array
    /// @return Number of legal moves
    int generate_legal_moveset_rook(const int8_t pos, int8_t *moveset, int8_t number_of_moves = 0) const
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
    /// @brief generates legal moveset for a pawn at position 'pos'
    /// @param pos defines for witch pawn moveset should be calculated
    /// @param moveset stores all legal possible move positions
    /// @param number_of_moves noumber of moves already present in moveset array
    /// @return Number of legal moves
    int generate_legal_moveset_bishop(const int8_t pos, int8_t *moveset, int8_t number_of_moves = 0) const
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
    /// @brief generates legal moveset for a pawn at position 'pos'
    /// @param pos defines for witch pawn moveset should be calculated
    /// @param moveset stores all legal possible move positions
    /// @param number_of_moves noumber of moves already present in moveset array
    /// @return Number of legal moves
    int generate_legal_moveset_queen(const int8_t pos, int8_t *moveset, int8_t number_of_moves = 0) const
    {
        // queen is basically rook & bishop at once, so why even bother?
        number_of_moves = generate_legal_moveset_rook(pos, moveset, number_of_moves);
        number_of_moves = generate_legal_moveset_bishop(pos, moveset, number_of_moves);

        return number_of_moves;
    }

    /// @brief generates legal moveset for a given color
    /// @param color color for which all moves possible will be generated
    /// @param moveset stores all legal possible move positions
    /// @return Number of legal moves
    int generate_legal_moveset_for_color(Color color, int8_t *starting_positions, int8_t *moveset) const
    {
        int number_of_moves = 0;
        int new_no_moves;
        for (int8_t i = 0; i < 64; i++)
        {
            if (get_color(data[i]) == color)
            {
                if (data[i] == b_pawn || data[i] == w_pawn)
                {

                    new_no_moves = generate_legal_moveset_pawn(i, moveset, number_of_moves);
                    for (int j = number_of_moves; j < new_no_moves; j++)
                        starting_positions[j] = i;
                    number_of_moves = new_no_moves;
                }
                else if (data[i] == b_knight || data[i] == w_knight)
                {

                    new_no_moves = generate_legal_moveset_knight(i, moveset, number_of_moves);
                    for (int j = number_of_moves; j < new_no_moves; j++)
                        starting_positions[j] = i;
                    number_of_moves = new_no_moves;
                }
                else if (data[i] == b_king || data[i] == w_king)
                {

                    new_no_moves = generate_legal_moveset_king(i, moveset, number_of_moves);
                    for (int j = number_of_moves; j < new_no_moves; j++)
                        starting_positions[j] = i;
                    number_of_moves = new_no_moves;
                }
                else if (data[i] == b_rook || data[i] == w_rook)
                {

                    new_no_moves = generate_legal_moveset_rook(i, moveset, number_of_moves);
                    for (int j = number_of_moves; j < new_no_moves; j++)
                        starting_positions[j] = i;
                    number_of_moves = new_no_moves;
                }
                else if (data[i] == b_bishop || data[i] == w_bishop)
                {

                    new_no_moves = generate_legal_moveset_bishop(i, moveset, number_of_moves);
                    for (int j = number_of_moves; j < new_no_moves; j++)
                        starting_positions[j] = i;
                    number_of_moves = new_no_moves;
                }
                else if (data[i] == b_queen || data[i] == w_queen)
                {

                    new_no_moves = generate_legal_moveset_queen(i, moveset, number_of_moves);
                    for (int j = number_of_moves; j < new_no_moves; j++)
                        starting_positions[j] = i;
                    number_of_moves = new_no_moves;
                }
            }
        }
        return number_of_moves;
    }

    float estimate_position() const
    {
        float estimation = 0;
        int8_t pawn_moves[MAX_NO_MOVES_IN_EACH_BOARD];
        for (int i = 0; i < 64; i++)
        {
            if (data[i] != empty)
            {
                estimation += weight_encoding[data[i]];

                switch (data[i])
                {
                case b_pawn:
                    estimation -= 0.1 * generate_legal_moveset_pawn(i, pawn_moves);
                    break;
                case w_pawn:
                    estimation += 0.1 * generate_legal_moveset_pawn(i, pawn_moves);
                    break;
                case b_knight:
                    estimation -= 0.1 * generate_legal_moveset_knight(i, pawn_moves);
                    break;
                case w_knight:
                    estimation += 0.1 * generate_legal_moveset_knight(i, pawn_moves);
                    break;
                case b_king:
                    estimation -= 0.1 * generate_legal_moveset_king(i, pawn_moves);
                    break;
                case w_king:
                    estimation += 0.1 * generate_legal_moveset_king(i, pawn_moves);
                    break;
                case b_rook:
                    estimation -= 0.1 * generate_legal_moveset_rook(i, pawn_moves);
                    break;
                case w_rook:
                    estimation += 0.1 * generate_legal_moveset_rook(i, pawn_moves);
                    break;
                case b_bishop:
                    estimation -= 0.1 * generate_legal_moveset_bishop(i, pawn_moves);
                    break;
                case w_bishop:
                    estimation += 0.1 * generate_legal_moveset_bishop(i, pawn_moves);
                    break;
                case b_queen:
                    estimation -= 0.1 * generate_legal_moveset_queen(i, pawn_moves);
                    break;
                case w_queen:
                    estimation += 0.1 * generate_legal_moveset_queen(i, pawn_moves);
                    break;
                default:
                    break;
                }
            }
        }
        return estimation;
    }
    void estimate_all_moves_for_color(int8_t depth, Color color, const int no_moves, int8_t *starting_positions, int8_t *moveset, float *estimations)
    {
        if (color == white)
            color = black;
        else
            color = white;

        for (int i = 0; i < no_moves; i++)
        {

            auto from = Piece(data[starting_positions[i]]);
            auto to = Piece(data[moveset[i]]);

            move(starting_positions[i], moveset[i]);

            estimations[i] = alpha_beta(depth, -2000, 2000, color);

            data[starting_positions[i]] = Piece(from);
            data[moveset[i]] = Piece(to);
        }
    }

    float alpha_beta(const int depth, float alpha, float beta, const Color player_color)
    {

        float current_estimation = estimate_position();
        if (depth <= 0 || current_estimation < -900 || current_estimation > 900)
            return current_estimation;

        int8_t starting_positions[MAX_NO_MOVES_IN_EACH_BOARD];
        int8_t moves[MAX_NO_MOVES_IN_EACH_BOARD];
        int no_moves = generate_legal_moveset_for_color(player_color, starting_positions, moves);

        Piece from;
        Piece to;
        if (player_color == white)
        {
            if (no_moves == 0)
                return -1000;
            float result = -1000;
            for (int i = 0; i < no_moves; i++)
            {
                from = data[starting_positions[i]];
                to = data[moves[i]];

                move(starting_positions[i], moves[i]);
                result = max(result, alpha_beta(depth - 1, alpha, beta, black));

                data[starting_positions[i]] = from;
                data[moves[i]] = to;

                alpha = max(alpha, result);
                if (result >= beta)
                    break;
            }
            return result;
        }
        else
        {
            if (no_moves == 0)
                return 1000;
            float result = 1000;
            for (int i = 0; i < no_moves; i++)
            {

                from = data[starting_positions[i]];
                to = data[moves[i]];

                move(starting_positions[i], moves[i]);
                result = min(result, alpha_beta(depth - 1, alpha, beta, white));

                data[starting_positions[i]] = from;
                data[moves[i]] = to;

                beta = min(beta, result);
                if (result <= alpha)
                    break;
            }
            return result;
        }
    }
};

#endif