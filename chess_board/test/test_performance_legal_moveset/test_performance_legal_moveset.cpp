#include <Arduino.h>
#include <Board.h>
#include "unity.h"

void exec_time_description(float expected, float got, char *buffer)
{
    String description_str = String("execution time [microseconds]:") + String(got) + String("expected:") + String(expected);
    description_str.toCharArray(buffer, 70);
}

#define PERFORMANCE_TEST(function, expected, pawn)                   \
    do                                                               \
    {                                                                \
        randomSeed(69);                                              \
        MoveSet moves;                                               \
        uint16_t no_test_cases = 100;                                \
        unsigned long avg = 0;                                       \
        for (uint16_t i = 0; i < no_test_cases; i++)                 \
        {                                                            \
            Board board;                                             \
            moves.clear();                                           \
            for (int j = 0; j < 16; j++)                             \
                board.data[random(0, 64)] = b_pawn;                  \
                                                                     \
            for (int j = 0; j < 16; j++)                             \
                board.data[random(0, 64)] = w_pawn;                  \
                                                                     \
            int pawn_pos = random(0, 64);                            \
            board.data[pawn_pos] = pawn;                             \
                                                                     \
            auto timer = micros();                                   \
            board.function(pawn_pos, moves);                         \
            avg += micros() - timer;                                 \
        }                                                            \
        float f_avg = avg / no_test_cases;                           \
        char timer_c_str[70];                                        \
        exec_time_description(expected, f_avg, timer_c_str);         \
        UNITY_TEST_ASSERT(f_avg == expected, __LINE__, timer_c_str); \
    } while (0)

int performance_test_generate_legal_moveset_w_pawn(void)
{
    PERFORMANCE_TEST(generate_legal_moveset_pawn, 25.00, w_pawn);
    return 0;
}
int performance_test_generate_legal_moveset_b_pawn(void)
{
    PERFORMANCE_TEST(generate_legal_moveset_pawn, 24.00, b_pawn);
    return 0;
}
int performance_test_generate_legal_moveset_w_knight(void)
{
    PERFORMANCE_TEST(generate_legal_moveset_knight, 20.00, w_knight);
    return 0;
}
int performance_test_generate_legal_moveset_b_knight(void)
{
    PERFORMANCE_TEST(generate_legal_moveset_knight, 20.00, b_knight);
    return 0;
}

int performance_test_generate_legal_moveset_w_bishop(void)
{
    PERFORMANCE_TEST(generate_legal_moveset_bishop, 39.00, w_bishop);
    return 0;
}
int performance_test_generate_legal_moveset_b_bishop(void)
{
    PERFORMANCE_TEST(generate_legal_moveset_bishop, 39.00, b_bishop);
    return 0;
}

int performance_test_generate_legal_moveset_w_queen(void)
{
    PERFORMANCE_TEST(generate_legal_moveset_queen, 75.00, w_queen);

    return 0;
}
int performance_test_generate_legal_moveset_b_queen(void)
{
    PERFORMANCE_TEST(generate_legal_moveset_queen, 74.00, b_queen);
    return 0;
}

int performance_test_generate_legal_moveset_w_king(void)
{
    PERFORMANCE_TEST(generate_legal_moveset_king, 24.00, w_king);
    return 0;
}

int performance_test_generate_legal_moveset_b_king(void)
{
    PERFORMANCE_TEST(generate_legal_moveset_king, 24.00, b_king);
    return 0;
}

int runUnityTests(void)
{
    UNITY_BEGIN();

    RUN_TEST(performance_test_generate_legal_moveset_w_pawn);
    RUN_TEST(performance_test_generate_legal_moveset_b_pawn);

    RUN_TEST(performance_test_generate_legal_moveset_w_knight);
    RUN_TEST(performance_test_generate_legal_moveset_b_knight);

    RUN_TEST(performance_test_generate_legal_moveset_w_bishop);
    RUN_TEST(performance_test_generate_legal_moveset_b_bishop);

    RUN_TEST(performance_test_generate_legal_moveset_w_queen);
    RUN_TEST(performance_test_generate_legal_moveset_b_queen);

    RUN_TEST(performance_test_generate_legal_moveset_w_king);
    RUN_TEST(performance_test_generate_legal_moveset_b_king);

    return UNITY_END();
}

void setup()
{
    delay(2000);
    runUnityTests();
}
void loop() {}