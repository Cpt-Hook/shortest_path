//
// Created by standa on 2/23/20.
//
#ifndef STATE_SPACE_SEARCH_GRID_H

#include <vector>
#include <iostream>

const char WALL_CHAR = 'X';
const char PATH_CHAR = 'o';
const char CLOSED_CHAR = '-';
const char OPEN_CHAR = '#';
const char START_CHAR = 'S';
const char END_CHAR = 'E';
const char BLANK_CHAR = ' ';

enum class STATE {
    OPEN, CLOSED, UNDISCOVERED, PATH
};

enum COLOR_PAIR {
    RED_PAIR = 1, BLUE_PAIR, YELLOW_PAIR, GREEN_PAIR
};

struct Coords {
    int x, y;

    bool operator==(const Coords &other) const;
};

std::ostream& operator<<(std::ostream &stream, const Coords &coords);

struct Cell {
    Cell *prev;
    Coords coords;
    STATE state;
    bool blank;

    explicit Cell(Coords coords, bool blank);
    char get_print_char() const;
    void addchar() const;

    static void addchar_start();
    static void addchar_end();
};

std::ostream& operator<<(std::ostream &stream, const Cell &cell);

using Grid = std::vector<std::vector<Cell>>;

bool load_grid(Grid &grid, Coords &start, Coords &end, std::istream &stream=std::cin);

class Maze {
public:
    Grid grid;
    Coords start = {0, 0}, end = {0, 0};

    bool load_maze(std::istream &stream=std::cin);
    void print_maze() const;

    Cell& get_cell(Coords coords);
    Cell& get_start_cell();
    Cell& get_end_cell();
};

std::ostream& operator<<(std::ostream &stream, const Maze &maze);

#define STATE_SPACE_SEARCH_GRID_H
#endif //STATE_SPACE_SEARCH_GRID_H
