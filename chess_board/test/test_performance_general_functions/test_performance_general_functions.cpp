#include <Arduino.h>
#include <Board.h>
#include "unity.h"

void exec_time_description(float expected, float got, char *buffer)
{
    String description_str = String("execution time [microseconds]:") + String(got) + String("expected:") + String(expected);
    description_str.toCharArray(buffer, 70);
}

int performance_test_estimate_position(void)
{
    randomSeed(69);
    volatile uint16_t result;
    uint16_t no_test_cases = 300;
    unsigned long avg = 0;
    for (uint16_t i = 0; i < no_test_cases; i++)
    {
        Board board;
        for (int j = 0; j < 32; j++)
            board.data[random(0, 64)] = Piece(random(1, 13));

        auto timer = micros();
        result = board.estimate_position();
        avg += micros() - timer;
    }
    float f_avg = avg / no_test_cases;

    char timer_c_str[70];
    exec_time_description(689, f_avg, timer_c_str);
    UNITY_TEST_ASSERT(f_avg == 689, __LINE__, timer_c_str);

    return 0;
}

void all_moves_for_color(int8_t depth, Color color, float expected)
{

    MoveSet moves;
    int16_t estimations[MAX_NO_MOVES_IN_EACH_BOARD];

    volatile uint16_t result;

    Board board(true);
    auto timer = micros();

    board.generate_legal_moveset_for_color(color, moves);
    board.estimate_all_moves_for_color(depth, color, moves, estimations);
    timer = micros() - timer;

    result = estimations[0];

    char timer_c_str[70];
    exec_time_description(expected, timer, timer_c_str);
    UNITY_TEST_ASSERT(timer == expected, __LINE__, timer_c_str);
}

int performance_test_estimate_all_moves_for_color_white_depth_0_starting_pos(void)
{
    all_moves_for_color(0, white, 12052);
    return 0;
}
int performance_test_estimate_all_moves_for_color_black_depth_0_starting_pos(void)
{
    all_moves_for_color(0, black, 12052);
    return 0;
}

int performance_test_estimate_all_moves_for_color_white_depth_1_starting_pos(void)
{
    all_moves_for_color(1, white, 25783);
    return 0;
}
int performance_test_estimate_all_moves_for_color_black_depth_1_starting_pos(void)
{
    all_moves_for_color(1, black, 25783);
    return 0;
}

int runUnityTests(void)
{
    UNITY_BEGIN();

    // RUN_TEST(performance_test_estimate_all_moves_for_color_white_depth_0_starting_pos);
    RUN_TEST(performance_test_estimate_position);
    // RUN_TEST(performance_test_estimate_all_moves_for_color_black_depth_0_starting_pos);
    // RUN_TEST(performance_test_estimate_all_moves_for_color_white_depth_1_starting_pos);
    // RUN_TEST(performance_test_estimate_all_moves_for_color_black_depth_1_starting_pos);
    //
    return UNITY_END();
}

void setup()
{
    delay(2000);
    runUnityTests();
}
void loop() {}