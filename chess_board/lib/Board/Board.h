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
enum Color
{
    white = 0,
    black = 1
};

class Board
{

protected:
    Piece data[64];
    const short width = 8;
    const short length = 8;

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

    int estimate_position()
    {
        int estimation = 0;
        for (short i = 0; i < 64; i++)
        {
            estimation += weight_encoding[data[i]];
            // here add points based on no available moves
        }
        return estimation;
    }

    void to_string(char *board)
    {
        for (short i = 0; i < 64; i++)
        {
            board[i] = symbol_encoding[data[i]];
        }
    }
};