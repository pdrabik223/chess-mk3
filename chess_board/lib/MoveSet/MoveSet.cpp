#include <MoveSet.h>

void MoveSet::next(int8_t &from, int8_t &to)
{
    to = moves[current_index];
    if (current_index >= sum)
    {
        current_starting_positions_index += 2;
        sum += starting_positions[current_starting_positions_index];
        from = starting_positions[current_starting_positions_index + 1];
    }
    else
    {
        from = starting_positions[current_starting_positions_index + 1];
    }
    ++current_index;
}

void MoveSet::add_move(const int8_t new_move)
{
    moves[size++] = new_move;
}

void MoveSet::add_starting_position(const int8_t no_moves, const int8_t new_starting_position)
{
    if (no_moves > 0)
    {
        starting_positions[starting_positions_size++] = no_moves;
        starting_positions[starting_positions_size++] = new_starting_position;
    }
}

void MoveSet::clear()
{
    current_index = 0;
    current_starting_positions_index = -2;
    size = 0;
    starting_positions_size = 0;
    sum = 0;
}

void MoveSet::get(int8_t &from, int8_t &to, const uint8_t id)
{

    int8_t l_current_index = 0;
    int8_t l_current_starting_positions_index = -2;
    int8_t l_sum = 0;

    to = moves[id];
    for (int8_t i = 0; i <= id; i++)
    {
        if (l_current_index >= l_sum)
        {
            l_current_starting_positions_index += 2;
            l_sum += starting_positions[l_current_starting_positions_index];
            from = starting_positions[l_current_starting_positions_index + 1];
        }
        else
        {
            from = starting_positions[l_current_starting_positions_index + 1];
        }
        ++l_current_index;
    }
}