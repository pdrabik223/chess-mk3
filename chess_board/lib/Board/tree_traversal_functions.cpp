#include <Board.h>

void Board::estimate_all_moves_for_color(const int8_t depth, Color color, MoveSet &moves, int16_t *estimations)
{
    if (color == white)
        color = black;
    else
        color = white;

    int8_t starting_position;
    Piece from;

    int8_t target_position;
    Piece to;

    for (uint8_t i = 0; i < moves.size; i++)
    {
        moves.next(starting_position, target_position);

        from = data[starting_position];
        to = data[target_position];

        move(starting_position, target_position);

        estimations[i] = alpha_beta(depth, -20000, 20000, color);
        // estimations[i] = min_max(depth, color);
        // estimations[i] = pvs(depth, -20000, 20000, color);
        // estimations[i] = nega_scout(depth, -20000, 20000, color);
        data[starting_position] = from;
        data[target_position] = to;
    }
}

int16_t Board::min_max(const int8_t depth, const Color player_color)
{
    if (depth <= 0)
        return estimate_position();

    if (!check_for_white_king())
        return weight_encoding[b_king];

    if (!check_for_black_king())
        return weight_encoding[w_king];

    MoveSet moves;

    generate_legal_moveset_for_color(player_color, moves);

    int8_t starting_position;
    Piece from;

    int8_t target_position;
    Piece to;

    if (player_color == white)
    {
        if (moves.size == 0)
            return weight_encoding[b_king];

        int16_t result = weight_encoding[b_king];

        for (int8_t i = 0; i < moves.size; i++)
        {
            moves.next(starting_position, target_position);

            from = data[starting_position];
            to = data[target_position];

            move(starting_position, target_position);
            result = max(result, min_max(depth - 1, black));

            data[starting_position] = from;
            data[target_position] = to;
        }
        return result;
    }
    else
    {
        if (moves.size == 0)
            return weight_encoding[w_king];

        int16_t result = weight_encoding[w_king];

        for (int8_t i = 0; i < moves.size; i++)
        {

            moves.next(starting_position, target_position);

            from = data[starting_position];
            to = data[target_position];

            move(starting_position, target_position);
            result = min(result, min_max(depth - 1, white));

            data[starting_position] = from;
            data[target_position] = to;
        }
        return result;
    }
}

int16_t Board::alpha_beta(const int8_t depth, int16_t alpha, int16_t beta, const Color player_color)
{
    // int16_t current_estimation = estimate_position();
    // if (depth <= 0 || current_estimation < -15000 || current_estimation > 15000)
    //     return current_estimation;

    if (depth <= 0)
        return estimate_position();

    if (!check_for_white_king())
        return weight_encoding[b_king];

    if (!check_for_black_king())
        return weight_encoding[w_king];

    MoveSet moves;

    generate_legal_moveset_for_color(player_color, moves);

    int8_t starting_position;
    Piece from;

    int8_t target_position;
    Piece to;

    if (player_color == white)
    {
        if (moves.size == 0)
            return weight_encoding[b_king];

        int16_t result = weight_encoding[b_king];

        for (int8_t i = 0; i < moves.size; i++)
        {
            moves.next(starting_position, target_position);

            from = data[starting_position];
            to = data[target_position];

            move(starting_position, target_position);
            result = max(result, alpha_beta(depth - 1, alpha, beta, black));

            data[starting_position] = from;
            data[target_position] = to;

            if (result >= beta)
                break;
            alpha = max(alpha, result);
        }
        return result;
    }
    else
    {
        if (moves.size == 0)
            return weight_encoding[w_king];

        int16_t result = weight_encoding[w_king];

        for (int8_t i = 0; i < moves.size; i++)
        {

            moves.next(starting_position, target_position);

            from = data[starting_position];
            to = data[target_position];

            move(starting_position, target_position);
            result = min(result, alpha_beta(depth - 1, alpha, beta, white));

            data[starting_position] = from;
            data[target_position] = to;

            if (result <= alpha)
                break;
            beta = min(beta, result);
        }
        return result;
    }
}
int16_t Board::nega_scout(const int8_t depth, int16_t alpha, int16_t beta, const Color player_color)
{
    if (depth <= 0)
        return estimate_position();

    if (!check_for_white_king())
        return weight_encoding[b_king];

    if (!check_for_black_king())
        return weight_encoding[w_king];

    MoveSet moves;
    int8_t starting_position, target_position;
    Piece from, to;

    int16_t result;
    Color color;
    auto b = beta;
    auto a = alpha;
    generate_legal_moveset_for_color(player_color, moves);
    if (player_color == white)
    {
        color = black;
        result = weight_encoding[b_king];
    }
    else
    {
        color = white;
        result = weight_encoding[w_king];
    }

    if (moves.size == 0)
        return result;

    for (int8_t i = 0; i < moves.size; i++)
    {
        moves.next(starting_position, target_position);

        from = data[starting_position];
        to = data[target_position];

        move(starting_position, target_position);
        result = -nega_scout(depth - 1, -b, -a, color);
        data[starting_position] = from;
        data[target_position] = to;

        if (result > a && result < beta && i > 0)
        {
            from = data[starting_position];
            to = data[target_position];

            move(starting_position, target_position);
            a = -nega_scout(depth - 1, -beta, -result, color);
            data[starting_position] = from;
            data[target_position] = to;
        }
        a = max(a, result);
        if (a >= beta)
            return a;
        b = a + 1;
    }
    return a;
}

int16_t Board::pvs(const int8_t depth, int16_t alpha, int16_t beta, const Color player_color)
{
    if (depth <= 0)
        return estimate_position();

    if (!check_for_white_king())
        return weight_encoding[b_king];

    if (!check_for_black_king())
        return weight_encoding[w_king];

    MoveSet moves;

    generate_legal_moveset_for_color(player_color, moves);

    int8_t starting_position, target_position;
    Piece from, to;

    int16_t result;
    Color color;

    if (player_color == white)
    {
        color = black;
        result = weight_encoding[b_king];
    }
    else
    {
        color = white;
        result = weight_encoding[w_king];
    }

    if (moves.size == 0)
        return result;

    for (int8_t i = 0; i < moves.size; i++)
    {
        if (i == 0)
        {
            moves.next(starting_position, target_position);

            from = data[starting_position];
            to = data[target_position];

            move(starting_position, target_position);
            result = -pvs(depth - 1, -beta, -alpha, color);

            data[starting_position] = from;
            data[target_position] = to;
        }
        else
        {
            moves.next(starting_position, target_position);

            from = data[starting_position];
            to = data[target_position];

            move(starting_position, target_position);
            result = -pvs(depth - 1, -alpha - 1, -alpha, color);

            data[starting_position] = from;
            data[target_position] = to;

            if (alpha < result && result < beta)
            {
                from = data[starting_position];
                to = data[target_position];

                move(starting_position, target_position);
                result = -pvs(depth - 1, -beta, -result, color);
                data[starting_position] = from;
                data[target_position] = to;
            }
        }

        alpha = max(alpha, result);
        if (alpha >= beta)
            break;
    }
    return alpha;
}

// int16_t Board::quiesce(int16_t alpha, int16_t beta, const Color player_color)
// {

//     return estimate_position();
// }