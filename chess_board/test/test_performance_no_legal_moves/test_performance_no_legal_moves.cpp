#include <Arduino.h>
#include <Board.h>
#include "unity.h"

#define PERFORMANCE_TEST(function, expected, pawn)                   \
    do                                                               \
    {                                                                \
        randomSeed(69);                                              \
        uint16_t no_test_cases = 100;                                \
        volatile uint16_t result;                                    \
        unsigned long avg = 0;                                       \
        for (uint16_t i = 0; i < no_test_cases; i++)                 \
        \ 
{                                                          \
            Board board;                                             \
            for (int j = 0; j < 16; j++)                             \
                board.data[random(0, 64)] = w_pawn;                  \
                                                                     \
            for (int j = 0; j < 16; j++)                             \
                board.data[random(0, 64)] = b_pawn;                  \
                                                                     \
            int pawn_pos = random(0, 64);                            \
            board.data[pawn_pos] = pawn;                             \
                                                                     \
            auto timer = micros();                                   \
            result = function(board.data, pawn_pos);                 \
            avg += micros() - timer;                                 \
        }                                                            \
        float f_avg = avg / no_test_cases;                           \
        String timer_str(f_avg);                                     \
        String description_str("execution time [microseconds]:");    \
        timer_str = description_str + timer_str;                     \
        char timer_c_str[31 + 12];                                   \
        timer_str.toCharArray(timer_c_str, 12 + 31);                 \
        UNITY_TEST_ASSERT(f_avg <= expected, __LINE__, timer_c_str); \
    } while (0)

int performance_test_generate_no_legal_moves_w_pawn(void)
{

    PERFORMANCE_TEST(generate_no_legal_moves_pawn, 10.00, w_pawn);
    return 0;
}
int performance_test_generate_no_legal_moves_b_pawn(void)
{

    PERFORMANCE_TEST(generate_no_legal_moves_pawn, 9.00, b_pawn);
    return 0;
}
int performance_test_generate_no_legal_moves_w_knight(void)
{
    PERFORMANCE_TEST(generate_no_legal_moves_knight, 19.00, w_knight);

    return 0;
}
int performance_test_generate_no_legal_moves_b_knight(void)
{
    PERFORMANCE_TEST(generate_no_legal_moves_knight, 19.00, b_knight);
    return 0;
}

int performance_test_generate_no_legal_moves_w_bishop(void)
{

    PERFORMANCE_TEST(generate_no_legal_moves_bishop, 19.00, w_bishop);

    return 0;
}
int performance_test_generate_no_legal_moves_b_bishop(void)
{
    PERFORMANCE_TEST(generate_no_legal_moves_bishop, 20.00, b_bishop);

    return 0;
}
int performance_test_generate_no_legal_moves_w_rook(void)
{
    PERFORMANCE_TEST(generate_no_legal_moves_rook, 19.00, w_rook);

    return 0;
}
int performance_test_generate_no_legal_moves_b_rook(void)
{
    PERFORMANCE_TEST(generate_no_legal_moves_rook, 19.00, b_rook);

    return 0;
}

int performance_test_generate_no_legal_moves_w_queen(void)
{
    PERFORMANCE_TEST(generate_no_legal_moves_queen, 36.00, w_queen);

    return 0;
}
int performance_test_generate_no_legal_moves_b_queen(void)
{
    PERFORMANCE_TEST(generate_no_legal_moves_queen, 35.00, b_queen);

    return 0;
}

int performance_test_generate_no_legal_moves_w_king(void)
{
    PERFORMANCE_TEST(generate_no_legal_moves_king, 20.00, w_king);

    return 0;
}

int performance_test_generate_no_legal_moves_b_king(void)
{

    PERFORMANCE_TEST(generate_no_legal_moves_king, 20.00, b_king);

    return 0;
}
int runPerformanceTests(void)
{
    UNITY_BEGIN();

    RUN_TEST(performance_test_generate_no_legal_moves_w_pawn);
    RUN_TEST(performance_test_generate_no_legal_moves_b_pawn);

    RUN_TEST(performance_test_generate_no_legal_moves_w_knight);
    RUN_TEST(performance_test_generate_no_legal_moves_b_knight);

    RUN_TEST(performance_test_generate_no_legal_moves_w_bishop);
    RUN_TEST(performance_test_generate_no_legal_moves_b_bishop);

    RUN_TEST(performance_test_generate_no_legal_moves_w_queen);
    RUN_TEST(performance_test_generate_no_legal_moves_b_queen);

    RUN_TEST(performance_test_generate_no_legal_moves_w_king);
    RUN_TEST(performance_test_generate_no_legal_moves_b_king);

    return UNITY_END();
}

void setup()
{
    delay(2000);
    runPerformanceTests();
}
void loop() {}