#include <iostream>
#include "Board.h"
#include <stdint.h> /// for special uint tyoes like int8_t

char str_representation_of_a_board[65];
int16_t estimations[MAX_NO_MOVES_IN_EACH_BOARD];

bool simulate_game_for_color(const int no_iteration, const Color color, Board &board, const int8_t recursion_depth)
{

    std::cout << ":iteration:" << std::endl;
    std::cout << no_iteration << std::endl;

    MoveSet moves;
    board.generate_legal_moveset_for_color(color, moves);
    if (moves.size == 0)
    {
        if (color == white)
            std::cout << ":iteration_end game ended white lost:" << std::endl;
        else
            std::cout << ":iteration_end game ended black lost:" << std::endl;

        return true;
    }
    if (color == white)
        board.estimate_all_moves_for_color(recursion_depth, color, moves, estimations);
    else
        board.estimate_all_moves_for_color_b(recursion_depth, color, moves, estimations);

    int16_t best_move_estimation = estimations[0];
    uint8_t best_move_id = 0;

    for (uint8_t i = 1; i < moves.size; i++)
    {

        bool better_move = (color == white) ? estimations[i] > best_move_estimation : estimations[i] < best_move_estimation;

        if (better_move)
        {
            best_move_estimation = estimations[i];
            best_move_id = i;
        }
    }
    bool end_game;
    if (color == white)
        end_game = best_move_estimation > 15000;
    else
        end_game = best_move_estimation < -15000;

    if (end_game)
    {
        if (color == white)
            std::cout << ":iteration_end game ended white won:" << std::endl;
        else
            std::cout << ":iteration_end game ended black lost:" << std::endl;

        return true;
    }
    int8_t from, to;
    moves.get(from, to, best_move_id);
    board.move(from, to);

    std::cout << ":color:" << std::endl;

    if (color == white)
        std::cout << "white" << std::endl;
    else
        std::cout << "black" << std::endl;

    std::cout << ":board:" << std::endl;

    board.to_string(str_representation_of_a_board);

    std::cout << str_representation_of_a_board << std::endl;
    std::cout << ":from:" << std::endl;
    std::cout << (int)from << std::endl;
    std::cout << ":to:" << std::endl;
    std::cout << (int)to << std::endl;
    std::cout << ":position_estimation:" << std::endl;
    std::cout << board.estimate_position() << std::endl;
    std::cout << ":no_moves:" << std::endl;
    std::cout << (int)moves.size << std::endl;
    std::cout << ":starting_positions_str:" << std::endl;

    for (int i = 0; i < moves.size; i++)
    {

        int8_t l_from, l_to;
        moves.get(l_from, l_to, i);
        std::cout << (int)l_from << std::endl;
    }

    std::cout << ":moves_str:" << std::endl;
    for (int i = 0; i < moves.size; i++)
    {

        int8_t l_from, l_to;
        moves.get(l_from, l_to, i);
        std::cout << (int)l_to << std::endl;
    }
    std::cout << ":moves_estimation:" << std::endl;

    for (int i = 0; i < moves.size; i++)
        std::cout << (int)estimations[i] << std::endl;

    std::cout << ":best_move_estimation:" << std::endl;
    std::cout << best_move_estimation << std::endl;

    std::cout << ":killer moves:" << std::endl;
    MoveSet killer_moves;
    board.generate_killing_moveset_for_color(color, killer_moves);
    for (int i = 0; i < killer_moves.size; i++)
    {

        int8_t l_from, l_to;
        killer_moves.get(l_from, l_to, i);
        std::cout << (int)l_to << std::endl;
    }

    std::cout << ":iteration_end:" << std::endl;

    return false;
}

void simulate_game()
{
    int no_iteration = 0;
    Board board(true);
    while (true)
    {

        if (simulate_game_for_color(no_iteration, white, board, 4))
            return;

        if (simulate_game_for_color(no_iteration, black, board, 4))
            return;

        no_iteration++;
    }
}

void check_for_mat_in_2()
{
    int no_iteration = 0;
    Board board;
    board.set_piece(0, 0, b_king);
    board.set_piece(7, 7, w_rook);
    board.set_piece(7, 6, w_rook);
    board.set_piece(7, 5, w_king);
    while (true)
    {

        if (simulate_game_for_color(no_iteration, white, board, 3))
            return;

        if (simulate_game_for_color(no_iteration, black, board, 3))
            return;

        no_iteration++;
    }
}

int main()
{

    while (true)
    {
        simulate_game();
    }
    return 0;
}