/*
** titanfrigel, 2023
** snake
** File description:
** the_switch_case.cpp
*/

#include "snake.hpp"
#include <ncurses.h>
#include <unistd.h>

using namespace std;

void place_x(vector<string>& map, vector<size_t>& map_size)
{
    size_t x = 0, y = 0;

    while (map[y][x] != ' ') {
        x = rand() % (map_size[0] - 2) + 1;
        y = rand() % (map_size[1] - 2) + 1;
    }
    map[y][x] = 'X';
}

static int iterate_map(vector<string>& map, vector<size_t>& map_size, vector<vector<size_t>>& snake_pos, size_t *snake_size, void (*f)(vector<vector<size_t>>&))
{
    snake_pos.insert(snake_pos.begin(), snake_pos[0]);
    f(snake_pos);
    if (map[snake_pos[0][1]][snake_pos[0][0]] == 'O'   || map[snake_pos[0][1]][snake_pos[0][0]] == 'o')
        return (1);
    if (map[snake_pos[0][1]][snake_pos[0][0]] == 'X') {
        *snake_size += 1;
        map[snake_pos[0][1]][snake_pos[0][0]] = 'O';
        map[snake_pos[1][1]][snake_pos[1][0]] = 'o';
        place_x(map, map_size);
        return (0);
    }
    map[snake_pos[0][1]][snake_pos[0][0]] = 'O';
    map[snake_pos[1][1]][snake_pos[1][0]] = 'o';
    map[snake_pos[*snake_size][1]][snake_pos[*snake_size][0]] = ' ';
    snake_pos.pop_back();
    return (0);
}

int the_switch_case(int ch, vector<string>& map, vector<size_t>& map_size, vector<vector<size_t>>& snake_pos, size_t *snake_size)
{
    static int last_ch = KEY_RIGHT;
    int rvalue = 0;

    switch (ch) {
        case KEY_UP:
            if (snake_pos[0][1] <= 1)
                return (1);
            if (last_ch == KEY_DOWN)
                return (the_switch_case(last_ch, map, map_size, snake_pos, snake_size));
            rvalue = iterate_map(map, map_size, snake_pos, snake_size, [](vector<vector<size_t>>& snake_pos) { snake_pos[0][1] -= 1; });
            break;
        case KEY_DOWN:
            if (snake_pos[0][1] >= map_size[1] - 2)
                return (1);
            if (last_ch == KEY_UP)
                return (the_switch_case(last_ch, map, map_size, snake_pos, snake_size));
            rvalue = iterate_map(map, map_size, snake_pos, snake_size, [](vector<vector<size_t>>& snake_pos) { snake_pos[0][1] += 1; });
            break;
        case KEY_LEFT:
            if (snake_pos[0][0] <= 1)
                return (1);
            if (last_ch == KEY_RIGHT)
                return (the_switch_case(last_ch, map, map_size, snake_pos, snake_size));
            rvalue = iterate_map(map, map_size, snake_pos, snake_size, [](vector<vector<size_t>>& snake_pos) { snake_pos[0][0] -= 1; });
            break;
        case KEY_RIGHT:
            if (snake_pos[0][0] >= map_size[0] - 2)
                return (1);
            if (last_ch == KEY_LEFT)
                return (the_switch_case(last_ch, map, map_size, snake_pos, snake_size));
            rvalue = iterate_map(map, map_size, snake_pos, snake_size, [](vector<vector<size_t>>& snake_pos) { snake_pos[0][0] += 1; printw("aa\n");});
            break;
        default:
            return (the_switch_case(last_ch, map, map_size, snake_pos, snake_size));
    }
    last_ch = ch;
    return (rvalue);
}

