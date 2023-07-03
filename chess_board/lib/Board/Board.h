#include <String.h>

const char symbol_encoding[13]{'e', 'p', 'n', 'b', 'r', 'q', 'k', 'P', 'N', 'B', 'R', 'Q', 'K'};
const int weight_encoding[13]{0, 1, 3, 3, 5, 9, 1000, -1, -3, -3, -5, -9, -1000};

enum Piece
{
    empty,
    w_pawn,
    w_knight,
    w_bishop,
    w_rook,
    w_queen,
    w_king,

    b_pawn,
    b_knight,
    b_bishop,
    b_rook,
    b_queen,
    b_king
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

enum Color
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
    const short width = 8;
    const short height = 8;

public:
    Board()
    {
        for (short i = 0; i < 64; i++)
        {
            data[i] = empty;
        }
    }
    Board(const Board &copy)
    {
        for (short i = 0; i < 64; i++)
        {
            data[i] = copy.data[i];
        }
    }
    Board(const char *string)
    {
        for (short i = 0; i < 64; i++)
        {
            data[i] = Piece(string[i]);
        }
    }
    Board(bool from_starting_position)
    {
        for (short i = 0; i < 64; i++)
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

    void to_string(char *board)
    {
        for (short i = 0; i < 64; i++)
        {
            board[i] = symbol_encoding[data[i]];
        }
    }
    void move(int prev_pos, int new_pos)
    {
        data[new_pos] = data[prev_pos];
        data[prev_pos] = empty;
    }

    int construct_coord(int x, int y)
    {
        return x * 8 + y;
    }
    int deconstruct_coord_x(int coord)
    {
        return coord / 8;
    }
    int deconstruct_coord_y(int coord)
    {
        return coord % 8;
    }

    /// @brief generates legal moveset for pawn at position pos
    /// @param pos defines for witch pawn moveset should be calculated
    /// @param moveset stores all possible move positions
    /// @return Number of legal moves
    int generate_legal_moveset_pawn(int pos, int *moveset)
    {
        if (data[pos] != b_pawn && data[pos] != w_pawn)
            return 0;

        int number_of_moves = 0;

        Color pawn_color = white;

        if (data[pos] == b_pawn)
            pawn_color = black;

        int pos_x = pos / width;
        int pos_y = pos % width;

        if (pawn_color == black)
        {
            // black is on top, and goes down

            if (data[construct_coord(pos_x + 1, pos_y)] == empty)
                moveset[number_of_moves++] = construct_coord(pos_x + 1, pos_y);

            if (pos_y > 0)
                // if pawn is not on the left edge of the chessboard
                if (is_white(data[construct_coord(pos_x + 1, pos_y - 1)]))
                    moveset[number_of_moves++] = construct_coord(pos_x + 1, pos_y - 1);

            if (pos_y < 8)
                // if pawn is not on the right edge of the chessboard
                if (is_white(data[construct_coord(pos_x + 1, pos_y + 1)]))
                    moveset[number_of_moves++] = construct_coord(pos_x + 1, pos_y + 1);
        }
        else
        {
            // white is on the bottom, and goes up

            if (data[construct_coord(pos_x - 1, pos_y)] == empty)
                moveset[number_of_moves++] = construct_coord(pos_x - 1, pos_y);

            if (pos_y > 0)
                // if pawn is not on the left edge of the chessboard
                if (is_black(data[construct_coord(pos_x - 1, pos_y - 1)]))
                    moveset[number_of_moves++] = construct_coord(pos_x - 1, pos_y - 1);

            if (pos_y < 8)
                // if pawn is not on the right edge of the chessboard
                if (is_black(data[construct_coord(pos_x - 1, pos_y + 1)]))
                    moveset[number_of_moves++] = construct_coord(pos_x - 1, pos_y + 1);
        }

        return number_of_moves;
    }

    /// @brief generates legal moveset for pawn at position pos
    /// @param pos defines for witch pawn moveset should be calculated
    /// @param moveset stores all possible move positions
    /// @return Number of legal moves
    int generate_legal_moveset_knight(int pos, int *moveset)
    {
        if (data[pos] != b_knight && data[pos] != w_knight)
            return 0;

        int number_of_moves = 0;

        Color knight_color = white;

        if (data[pos] == b_knight)
            knight_color = black;

        int pos_x = pos / width;
        int pos_y = pos % width;

        int new_pos;
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
        if (pos_x + 1 < 8 && pos_y - 1 >= 0)
        {
            //  O O
            // O   O
            //   N
            // X   O
            //  O O
            new_pos = construct_coord(pos_x + 1, pos_y - 1);
            if (get_color(data[new_pos]) != knight_color)
                moveset[number_of_moves++] = new_pos;
        }
        if (pos_x - 1 >= 0 && pos_y - 1 >= 0)
        {
            //  O O
            // X   O
            //   N
            // O   O
            //  O O
            new_pos = construct_coord(pos_x - 1, pos_y - 1);
            if (get_color(data[new_pos]) != knight_color)
                moveset[number_of_moves++] = new_pos;
        }

        return number_of_moves;
    }
    /// @brief generates legal moveset for pawn at position pos
    /// @param pos defines for witch pawn moveset should be calculated
    /// @param moveset stores all possible move positions
    /// @return Number of legal moves
    int generate_legal_moveset_king(int pos, int *moveset)
    {
        if (data[pos] != b_king && data[pos] != w_king)
            return 0;

        int number_of_moves = 0;

        Color king_color = white;

        if (data[pos] == b_king)
            king_color = black;

        int pos_x = pos / width;
        int pos_y = pos % width;

        int new_pos;
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
    /// @return Number of legal moves
    int generate_legal_moveset_rook(int pos, int *moveset)
    {
        if (data[pos] != b_rook && data[pos] != w_rook)
            return 0;

        int number_of_moves = 0;

        Color rook_color = white;

        if (data[pos] == b_rook)
            rook_color = black;

        int pos_x = pos / width;
        int pos_y = pos % width;

        int new_pos;

        for (int x = pos_x + 1; x < 8; x++)
        {
            // going down starting with position just under the rook
            new_pos = construct_coord(x, pos_y);
            if (get_color(data[new_pos]) != rook_color)
                moveset[number_of_moves++] = new_pos;
            else
                break;
        }
        for (int x = pos_x - 1; x >= 0; x--)
        {
            // going up starting with position just above the rook
            new_pos = construct_coord(x, pos_y);
            if (get_color(data[new_pos]) != rook_color)
                moveset[number_of_moves++] = new_pos;
            else
                break;
        }
        for (int y = pos_y + 1; y < 8; y++)
        {
            // going right starting with position just to the right from the rook
            new_pos = construct_coord(pos_x, y);
            if (get_color(data[new_pos]) != rook_color)
                moveset[number_of_moves++] = new_pos;
            else
                break;
        }
        for (int y = pos_y - 1; y >= 0; y--)
        {
            // going left starting with position just to the left from the rook
            new_pos = construct_coord(pos_x, y);
            if (get_color(data[new_pos]) != rook_color)
                moveset[number_of_moves++] = new_pos;
            else
                break;
        }
        return number_of_moves;
    }
    /// @brief generates legal moveset for a pawn at position 'pos'
    /// @param pos defines for witch pawn moveset should be calculated
    /// @param moveset stores all legal possible move positions
    /// @return Number of legal moves
    int generate_legal_moveset_bishop(int pos, int *moveset)
    {
        if (data[pos] != b_bishop && data[pos] != w_bishop)
            return 0;

        int number_of_moves = 0;

        Color bishop_color = white;

        if (data[pos] == b_bishop)
            bishop_color = black;

        int pos_x = pos / width;
        int pos_y = pos % width;

        int new_pos;
        for (int x = pos_x + 1, y = pos_y + 1; x < 8 && y < 8; x++, y++)
        {
            // going down and right starting with position just to the right and down from the bishop
            new_pos = construct_coord(x, y);
            if (get_color(data[new_pos]) != bishop_color)
                moveset[number_of_moves++] = new_pos;
            else
                break;
        }
        for (int x = pos_x + 1, y = pos_y - 1; x < 8 && y >= 0; x++, y--)
        {
            // going down and left starting with position just to the left and down from the bishop
            new_pos = construct_coord(x, y);
            if (get_color(data[new_pos]) != bishop_color)
                moveset[number_of_moves++] = new_pos;
            else
                break;
        }
        for (int x = pos_x - 1, y = pos_y - 1; x >= 0 && y >= 0; x--, y--)
        {
            // going up and left starting with position just to the left and up from the bishop
            new_pos = construct_coord(x, y);
            if (get_color(data[new_pos]) != bishop_color)
                moveset[number_of_moves++] = new_pos;
            else
                break;
        }
        for (int x = pos_x - 1, y = pos_y + 1; x >= 0 && y < 8; x--, y++)
        {
            // going up and right starting with position just to the right and up from the bishop
            new_pos = construct_coord(x, y);
            if (get_color(data[new_pos]) != bishop_color)
                moveset[number_of_moves++] = new_pos;
            else
                break;
        }

        return number_of_moves;
    }
    /// @brief generates legal moveset for a pawn at position 'pos'
    /// @param pos defines for witch pawn moveset should be calculated
    /// @param moveset stores all legal possible move positions
    /// @return Number of legal moves
    int generate_legal_moveset_queen(int pos, int *moveset)
    {
        if (data[pos] != b_queen && data[pos] != w_queen)
            return 0;

        int number_of_moves = 0;

        Color queen_color = white;

        if (data[pos] == b_queen)
            queen_color = black;

        int pos_x = pos / width;
        int pos_y = pos % width;

        int new_pos;
        for (int x = pos_x + 1, y = pos_y + 1; x < 8 && y < 8; x++, y++)
        {
            // going down and right starting with position just to the right and down from the queen
            new_pos = construct_coord(x, y);
            if (get_color(data[new_pos]) != queen_color)
                moveset[number_of_moves++] = new_pos;
            else
                break;
        }
        for (int x = pos_x + 1, y = pos_y - 1; x < 8 && y >= 0; x++, y--)
        {
            // going down and left starting with position just to the left and down from the queen
            new_pos = construct_coord(x, y);
            if (get_color(data[new_pos]) != queen_color)
                moveset[number_of_moves++] = new_pos;
            else
                break;
        }
        for (int x = pos_x - 1, y = pos_y - 1; x >= 0 && y >= 0; x--, y--)
        {
            // going up and left starting with position just to the left and up from the queen
            new_pos = construct_coord(x, y);
            if (get_color(data[new_pos]) != queen_color)
                moveset[number_of_moves++] = new_pos;
            else
                break;
        }
        for (int x = pos_x - 1, y = pos_y + 1; x >= 0 && y < 8; x--, y++)
        {
            // going up and right starting with position just to the right and up from the queen
            new_pos = construct_coord(x, y);
            if (get_color(data[new_pos]) != queen_color)
                moveset[number_of_moves++] = new_pos;
            else
                break;
        }
        for (int x = pos_x + 1; x < 8; x++)
        {
            // going down starting with position just under the queen
            new_pos = construct_coord(x, pos_y);
            if (get_color(data[new_pos]) != queen_color)
                moveset[number_of_moves++] = new_pos;
            else
                break;
        }
        for (int x = pos_x - 1; x >= 0; x--)
        {
            // going up starting with position just above the queen
            new_pos = construct_coord(x, pos_y);
            if (get_color(data[new_pos]) != queen_color)
                moveset[number_of_moves++] = new_pos;
            else
                break;
        }
        for (int y = pos_y + 1; y < 8; y++)
        {
            // going right starting with position just to the right from the queen
            new_pos = construct_coord(pos_x, y);
            if (get_color(data[new_pos]) != queen_color)
                moveset[number_of_moves++] = new_pos;
            else
                break;
        }
        for (int y = pos_y - 1; y >= 0; y--)
        {
            // going left starting with position just to the left from the queen
            new_pos = construct_coord(pos_x, y);
            if (get_color(data[new_pos]) != queen_color)
                moveset[number_of_moves++] = new_pos;
            else
                break;
        }
        return number_of_moves;
    }

    float estimate_position()
    {
        float estimation = 0;
        int pawn_moves[64];
        for (short i = 0; i < 64; i++)
        {
            estimation += weight_encoding[data[i]];
            // here add points based on no available moves
            float color_multiplier;

            if (is_black(data[i]))
                color_multiplier = -0.1;
            else
                color_multiplier = 0.1;

            if (data[i] == b_pawn || data[i] == w_pawn)

                estimation += color_multiplier * generate_legal_moveset_pawn(i, pawn_moves);

            else if (data[i] == b_knight || data[i] == w_knight)

                estimation += color_multiplier * generate_legal_moveset_knight(i, pawn_moves);

            else if (data[i] == b_king || data[i] == w_king)

                estimation += color_multiplier * generate_legal_moveset_king(i, pawn_moves);

            else if (data[i] == b_rook || data[i] == w_rook)

                estimation += color_multiplier * generate_legal_moveset_rook(i, pawn_moves);

            else if (data[i] == b_bishop || data[i] == b_bishop)

                estimation += color_multiplier * generate_legal_moveset_bishop(i, pawn_moves);

            else if (data[i] == b_queen || data[i] == b_queen)

                estimation += color_multiplier * generate_legal_moveset_queen(i, pawn_moves);
        }
        return estimation;
    }
};