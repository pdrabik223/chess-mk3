#include <String.h>
#include <MeasTime.h>
#include <Piece.h>
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

const int8_t king_placement_weight_matrix[64]{0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0};

/// @brief generates noumber of legal moves for a pawn at position 'pos'
/// @param pos defines for witch pawn moveset should be calculated
/// @param number_of_moves noumber of moves already present in moveset array
/// @return Number of legal moves
uint16_t generate_no_legal_moves_rook(const Piece *data, const int8_t pos);

/// @brief generates noumber of legal moves for a pawn at position 'pos'
/// @param pos defines for witch pawn moveset should be calculated
/// @param number_of_moves noumber of moves already present in moveset array
/// @return Number of legal moves
uint16_t generate_no_legal_moves_pawn(const Piece *data, const int8_t pos);

/// @brief generates noumber of legal moves for a pawn at position 'pos'
/// @param pos defines for witch pawn moveset should be calculated
/// @param number_of_moves noumber of moves already present in moveset array
/// @return Number of legal moves
uint16_t generate_no_legal_moves_knight(const Piece *data, int8_t pos);

/// @brief generates noumber of legal moves for a pawn at position 'pos'
/// @param pos defines for witch pawn moveset should be calculated
/// @param number_of_moves noumber of moves already present in moveset array
/// @return Number of legal moves
uint16_t generate_no_legal_moves_king(const Piece *data, const int8_t pos);

/// @brief generates noumber of legal moves for a pawn at position 'pos'
/// @param pos defines for witch pawn moveset should be calculated
/// @param number_of_moves noumber of moves already present in moveset array
/// @return Number of legal moves
uint16_t generate_no_legal_moves_bishop(const Piece *data, const int8_t pos);

/// @brief generates noumber of legal moves for a pawn at position 'pos'
/// @param pos defines for witch pawn moveset should be calculated
/// @param number_of_moves noumber of moves already present in moveset array
/// @return Number of legal moves
uint16_t generate_no_legal_moves_queen(const Piece *data, const int8_t pos);

class Board
{

public:
    Board();
    Board(const Board &other);
    Board &operator=(const Board &other);

    Board(const char *string);
    friend bool operator==(const Board &lhs, const Board &rhs);
    friend bool operator!=(const Board &lhs, const Board &rhs);
    Board(bool from_starting_position);

    void set_piece(uint8_t x, uint8_t y, Piece piece);

    void from_string(const String &board_str);

    void to_string(char *board_str);

    void move(int8_t prev_pos, int8_t new_pos);

    static int8_t construct_coord(int8_t x, int8_t y);

    /// @brief generates legal moveset for a pawn at position 'pos'
    /// @param pos defines for witch pawn moveset should be calculated
    /// @param moveset stores all legal possible move positions
    /// @param number_of_moves noumber of moves already present in moveset array
    /// @return Number of legal moves
    int8_t generate_legal_moveset_pawn(int8_t pos, int8_t *moveset, int8_t number_of_moves = 0) const;

    /// @brief generates legal moveset for a pawn at position 'pos'
    /// @param pos defines for witch pawn moveset should be calculated
    /// @param moveset stores all legal possible move positions
    /// @param number_of_moves noumber of moves already present in moveset array
    /// @return Number of legal moves
    int8_t generate_legal_moveset_knight(int8_t pos, int8_t *moveset, int8_t number_of_moves = 0) const;

    /// @brief generates legal moveset for a pawn at position 'pos'
    /// @param pos defines for witch pawn moveset should be calculated
    /// @param moveset stores all legal possible move positions
    /// @param number_of_moves noumber of moves already present in moveset array
    /// @return Number of legal moves
    int8_t generate_legal_moveset_king(const int8_t pos, int8_t *moveset, int8_t number_of_moves = 0) const;

    /// @brief generates legal moveset for a pawn at position 'pos'
    /// @param pos defines for witch pawn moveset should be calculated
    /// @param moveset stores all legal possible move positions
    /// @param number_of_moves noumber of moves already present in moveset array
    /// @return Number of legal moves
    uint8_t generate_legal_moveset_rook(const int8_t pos, int8_t *moveset, int8_t number_of_moves = 0) const;

    /// @brief generates legal moveset for a pawn at position 'pos'
    /// @param pos defines for witch pawn moveset should be calculated
    /// @param moveset stores all legal possible move positions
    /// @param number_of_moves noumber of moves already present in moveset array
    /// @return Number of legal moves
    uint8_t generate_legal_moveset_bishop(const int8_t pos, int8_t *moveset, int8_t number_of_moves = 0) const;

    /// @brief generates legal moveset for a pawn at position 'pos'
    /// @param pos defines for witch pawn moveset should be calculated
    /// @param moveset stores all legal possible move positions
    /// @param number_of_moves noumber of moves already present in moveset array
    /// @return Number of legal moves
    uint8_t generate_legal_moveset_queen(const int8_t pos, int8_t *moveset, int8_t number_of_moves = 0) const;

    /// @brief generates legal moveset for a given color
    /// @param color color for which all moves possible will be generated
    /// @param moveset stores all legal possible move positions
    /// @return Number of legal moves
    uint8_t generate_legal_moveset_for_color(Color color, int8_t *starting_positions, int8_t *moveset) const;

    int16_t estimate_position() const;

    void estimate_all_moves_for_color(const int8_t depth, Color color, const uint8_t no_moves, int8_t *starting_positions, int8_t *moveset, int16_t *estimations);

    int16_t alpha_beta(const int8_t depth, int16_t alpha, int16_t beta, const Color player_color);

    int16_t pvs(const int8_t depth, int16_t alpha, int16_t beta, const Color player_color);

private:
    Piece data[64];
    const int8_t width = 8;
    const int8_t height = 8;
};

#endif