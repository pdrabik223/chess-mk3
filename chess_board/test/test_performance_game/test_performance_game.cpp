#include <Arduino.h>
#include <Board.h>
#include "unity.h"

void exec_time_description(long unsigned expected, long unsigned got, char *buffer)
{
    String description_str = String("execution time [microseconds]:") + String(got) + String("expected:") + String(expected);
    description_str.toCharArray(buffer, 70);
}

Board board(true);
const int8_t recursion_depth = 1;
int16_t estimations[MAX_NO_MOVES_IN_EACH_BOARD];
void simulate_game_for_color_white()
{
    MoveSet moves;
    auto timer = micros();

    board.generate_legal_moveset_for_color(white, moves);

    board.estimate_all_moves_for_color(recursion_depth, white, moves, estimations);

    if (moves.size == 0)
        UNITY_TEST_ASSERT(false, __LINE__, "END GAME");

    int16_t best_move_estimation = estimations[0];
    uint8_t best_move_id = 0;
    auto color = white;
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
        UNITY_TEST_ASSERT(false, __LINE__, "END GAME");
    }

    int8_t from, to;
    moves.get(from, to, best_move_id);
    board.move(from, to);

    timer = micros() - timer;

    char timer_c_str[70];
    exec_time_description(333652, timer, timer_c_str);
    UNITY_TEST_ASSERT(timer == 333652, __LINE__, timer_c_str);
}

void simulate_game_for_color_black()
{
    auto timer = micros();

    auto color = black;
    MoveSet moves;
    board.generate_legal_moveset_for_color(color, moves);

    board.estimate_all_moves_for_color(recursion_depth, color, moves, estimations);

    if (moves.size == 0)

        UNITY_TEST_ASSERT(false, __LINE__, "END GAME");

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
        UNITY_TEST_ASSERT(false, __LINE__, "END GAME");
    }

    int8_t from, to;
    moves.get(from, to, best_move_id);
    board.move(from, to);

    board.move(from, to);

    timer = micros() - timer;
    char timer_c_str[70];
    exec_time_description(391948, timer, timer_c_str);
    UNITY_TEST_ASSERT(timer == 391948, __LINE__, timer_c_str);
}

// void simulate_game()
// {
//     int no_iteration = 0;
//     Board board(true);

// auto timer = micros();
//     for (int i = 0; i < 10; i++)
//     {

//         simulate_game_for_color(white, board, 2);
//         simulate_game_for_color(black, board, 2);
//     }
// timer = micros() - timer;
// String timer_str(timer);
// String description_str("execution time [microseconds]:");
// timer_str = description_str + timer_str;
// char timer_c_str[31 + 12];
// timer_str.toCharArray(timer_c_str, 12 + 31);
// UNITY_TEST_ASSERT(timer == 12, __LINE__, timer_c_str);
// }

int runUnityTests(void)
{
    UNITY_BEGIN();

    RUN_TEST(simulate_game_for_color_white);
    RUN_TEST(simulate_game_for_color_black);

    // RUN_TEST(simulate_game_for_color_white);
    // RUN_TEST(simulate_game_for_color_black);

    // const int8_t recursion_depth = 0;
    // RUN_TEST(simulate_game_for_color_white);
    // RUN_TEST(simulate_game_for_color_black);

    return UNITY_END();
}

void setup()
{
    delay(2000);
    runUnityTests();
}
void loop() {}