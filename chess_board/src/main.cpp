#include <Arduino.h>
#include <Board.h>
#include <stdint.h> /// for special uint tyoes like int8_t

char str_representation_of_a_board[65];
int16_t estimations[MAX_NO_MOVES_IN_EACH_BOARD];

MoveSet moves;
bool simulate_game_for_color_w_time_measure(const int no_iteration, const Color color, Board &board, const int8_t recursion_depth)
{
    Serial.println(":iteration:");
    Serial.println(no_iteration);
    auto t_1 = millis();
    moves.clear();
    board.generate_legal_moveset_for_color(color, moves);
    board.estimate_all_moves_for_color(recursion_depth, color, moves, estimations);

    if (moves.size == 0)
    {
        if (color == white)
            Serial.println(":iteration_end game ended white lost:");
        else
            Serial.println(":iteration_end game ended black lost:");

        return true;
    }
    int16_t best_move_estimation = estimations[0];
    int best_move_id = 0;

    for (int i = 1; i < moves.size; i++)
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
            Serial.println(":iteration_end game ended white won:");
        else
            Serial.println(":iteration_end game ended black lost:");

        return true;
    }

    auto time = millis() - t_1;

    int8_t from, to;
    moves.get(from, to, best_move_id);
    board.move(from, to);

    Serial.println(":color:");
    if (color == white)
        Serial.println("white");
    else
        Serial.println("black");
    Serial.println(":no_moves:");
    Serial.println(moves.size);
    Serial.println(":position_estimation:");
    Serial.println(board.estimate_position());
    Serial.println(":best_move_estimation:");
    Serial.println(best_move_estimation);
    Serial.println(":moved_piece:");
    Serial.println(symbol_encoding[board.data[to]]);
    Serial.println(":elapsed time:");
    Serial.println(time);
    Serial.println(":board:");
    board.to_string(str_representation_of_a_board);
    Serial.println(str_representation_of_a_board);
    Serial.println(from);
    Serial.println(to);
    Serial.println(":iteration_end:");

    return false;
}

bool simulate_game_for_color(const int no_iteration, const Color color, Board &board, const int8_t recursion_depth)
{

    Serial.println(":iteration:");
    Serial.println(no_iteration);

    Serial.println(":color:");

    if (color == white)
        Serial.println("white");
    else
        Serial.println("black");

    moves.clear();
    board.generate_legal_moveset_for_color(color, moves);
    int16_t position_estimation = board.estimate_position();

    Serial.println(":board:");
    board.to_string(str_representation_of_a_board);
    Serial.println(str_representation_of_a_board);

    Serial.println(":position_estimation:");
    Serial.println(position_estimation);

    Serial.println(":no_moves:");
    Serial.println(moves.size);

    Serial.println(":starting_positions_str:");

    for (int i = 0; i < moves.size; i++)
    {

        int8_t from, to;
        moves.get(from, to, i);
        Serial.println(from);
    }

    Serial.println(":moves_str:");
    for (int i = 0; i < moves.size; i++)
    {

        int8_t from, to;
        moves.get(from, to, i);
        Serial.println(to);
    }
    Serial.println(":moves_estimation:");

    Serial.flush();
    board.estimate_all_moves_for_color(recursion_depth, color, moves, estimations);

    for (int i = 0; i < moves.size; i++)
        Serial.println(estimations[i]);

    if (moves.size == 0)
    {
        Serial.println(":STOP NO_MOVES iteration_end:");
        Serial.flush();
        return true;
    }
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
    Serial.println(":best_move_estimation:");
    Serial.println(best_move_estimation);
    bool end_game;
    if (color == white)
        end_game = best_move_estimation > 15000;
    else
        end_game = best_move_estimation < -15000;

    if (end_game)
    {
        Serial.println(":STOP WHITE WINS iteration_end:");
        Serial.flush();
        return true;
    }
    int8_t from, to;
    moves.get(from, to, best_move_id);
    board.move(from, to);
    Serial.println(":iteration_end:");
    Serial.flush();
    return false;
}

void simulate_game()
{
    int no_iteration = 0;
    Board board(true);
    while (true)
    {

        if (simulate_game_for_color(no_iteration, white, board, 2))
            return;

        delay(1000);

        if (simulate_game_for_color(no_iteration, black, board, 2))
            return;

        delay(1000);

        no_iteration++;
    }
}

void simulate_game_w_time()
{
    int no_iteration = 0;
    Board board(true);
    while (true)
    {
        if (simulate_game_for_color_w_time_measure(no_iteration, white, board, 2))
            return;

        delay(1000);

        if (simulate_game_for_color_w_time_measure(no_iteration, black, board, 2))
            return;

        delay(1000);

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

        delay(1000);

        if (simulate_game_for_color(no_iteration, black, board, 3))
            return;

        delay(1000);

        no_iteration++;
    }
}
void setup()
{
    Serial.begin(115200);
    delay(1000);
}

void loop()
{
    simulate_game_w_time();
}
