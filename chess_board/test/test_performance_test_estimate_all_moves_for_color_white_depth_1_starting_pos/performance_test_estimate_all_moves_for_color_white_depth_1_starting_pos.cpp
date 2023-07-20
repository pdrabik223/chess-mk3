#include <Arduino.h>
#include <Board.h>
#include "unity.h"

void exec_time_description(float expected, float got, char *buffer)
{
    String description_str = String("execution time [microseconds]:") + String(got) + String("expected:") + String(expected);
    description_str.toCharArray(buffer, 70);
}

void performance_test_estimate_all_moves_for_color(int8_t depth, Color color, float expected)
{

    MoveSet moves;
    int16_t estimations[MAX_NO_MOVES_IN_EACH_BOARD];

    volatile uint16_t result;

    Board board(true);
    auto timer = micros();

    board.generate_legal_moveset_for_color(color, moves);
    board.estimate_all_moves_for_color(depth, color, moves, estimations);
    result = estimations[0];
    timer = micros() - timer;

    char timer_c_str[70];
    exec_time_description(expected, timer, timer_c_str);
    UNITY_TEST_ASSERT(timer == expected, __LINE__, timer_c_str);
}

int performance_test_estimate_all_moves_for_color_white_depth_1_starting_pos(void)
{
    performance_test_estimate_all_moves_for_color(1, white, 25783.0);
    return 0;
}
int performance_test_estimate_all_moves_for_color_black_depth_1_starting_pos(void)
{
    performance_test_estimate_all_moves_for_color(1, black, 288512.0);
    return 0;
}

int runUnityTests(void)
{
    UNITY_BEGIN();

    RUN_TEST(performance_test_estimate_all_moves_for_color_black_depth_1_starting_pos);

    return UNITY_END();
}

void setup()
{
    delay(2000);
    runUnityTests();
}
void loop() {}