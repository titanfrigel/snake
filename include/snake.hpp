/*
** titanfrigel, 2023
** snake
** File description:
** snake.hpp
*/

#include <string>
#include <vector>

#ifndef _SNAKE_HPP_
    #define _SNAKE_HPP_
    int snake(int argc, char **argv);
    void place_x(std::vector<std::string>& map, std::vector<size_t>& map_size);
    int the_switch_case(int ch, std::vector<std::string>& map, std::vector<size_t>& map_size, std::vector<std::vector<size_t>>& snake_pos, size_t *snake_size);
#endif