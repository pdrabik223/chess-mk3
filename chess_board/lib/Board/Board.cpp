#include <Board.h>

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

int16_t Board::estimate_position() const
{
    int16_t estimation = 0;
    // jump table
    // instead of implementing logic with a lot of comparions
    // jump table can be created, that can be indexed with pawn type

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
