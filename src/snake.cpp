/*
** titanfrigel, 2023
** snake
** File description:
** snake.cpp
*/

#include "snake.hpp"
#include <iostream>
#include <ncurses.h>
#include <unistd.h>

using namespace std;

static void print_map(vector<string>& map)
{
    clear();
    for (size_t i = 0; i < map.size(); i++)
        for (size_t j = 0; j < map[i].size(); j++)
            mvprintw(i, j * 2, "%c ", map[i][j]);
    refresh();
}

static int args_handling(int argc, char **argv, vector<size_t>& map_size, vector<vector<size_t>>& snake_pos, size_t *nb_apple)
{
    if (argc > 4) {
        cerr << "Usage: ./snake [width height] [nb_apple]" << endl;
        return (84);
    }
    if (argc >= 3) {
        map_size.push_back(stoi(argv[1]));
        map_size.push_back(stoi(argv[2]));
        if (map_size[0] < 3 || map_size[1] < 3) {
            cerr << "Error: Map size must be at least 3x3" << endl;
            return (84);
        }
    } else {
        map_size.push_back(20);
        map_size.push_back(20);
    }
    if (argc == 4 || argc == 2) {
        *nb_apple = stoi(argv[(argc == 4) ? 3 : 1]);
        if (*nb_apple == 0) {
            cerr << "Error: You must have at least one apple" << endl;
            return (84);
        }
    } else
        *nb_apple = 1;
    snake_pos.push_back(vector<size_t>());
    snake_pos[0].push_back(map_size[0] / 2);
    snake_pos[0].push_back(map_size[1] / 2);
    return (0);
}

static void fill_map(vector<string>& map, vector<size_t>& map_size, vector<vector<size_t>>& snake_pos)
{
    for (size_t i = 0; i < map_size[1]; i++) {
        string line;
        for (size_t j = 0; j < map_size[0]; j++) {
            if (i == 0 || i == map_size[1] - 1) {
                line += "#";
            } else if (j == 0 || j == map_size[0] - 1) {
                line += "#";
            } else if (j == snake_pos[0][0] && i == snake_pos[0][1]) {
                line += "O";
            } else {
                line += " ";
            }
        }
        map.push_back(line);
    }
}

static int game_loop(vector<string>& map, vector<size_t>& map_size, vector<vector<size_t>>& snake_pos, size_t *snake_size, size_t nb_apple)
{
    int ch;
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    srand(time(NULL));
    for (size_t i = 0; i < nb_apple; i++)
        place_x(map, map_size);

    print_map(map);
    ch = getch();
    nodelay(stdscr, TRUE);

    while (11) {
        if (the_switch_case(ch, map, map_size, snake_pos, snake_size) == 1) {
            endwin();
            cout << "You lose!" << endl << "Score: " << *snake_size - 1 << endl;
            return (0);
        }
        print_map(map);
        usleep(250000);
        for (int tempch = 0; tempch != ERR; tempch = getch())
            ch = tempch;
    }
    return (0);
}

int snake(int argc, char **argv)
{
    vector<size_t> map_size;
    vector<vector<size_t>> snake_pos;
    size_t snake_size = 1;
    size_t nb_apple;
    vector<string> map;

    if (args_handling(argc, argv, map_size, snake_pos, &nb_apple) == 84)
        return (84);
    fill_map(map, map_size, snake_pos);
    if (game_loop(map, map_size, snake_pos, &snake_size, nb_apple) < 0)
        return (84);
    return (0);
}
