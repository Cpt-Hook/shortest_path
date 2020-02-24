//
// Created by standa on 2/23/20.
//
#ifndef STATE_SPACE_SEARCH_GRID_H

#include <vector>
#include <iostream>

enum class STATE {
    OPEN, CLOSED, UNDISCOVERED
};

struct Coords {
    int x, y;

    bool operator==(const Coords &other);
};

struct Cell {
    Cell *prev;
    Coords coords;
    STATE state;
    char print_char;

    explicit Cell(char print_char, Coords coords);
};

using Grid = std::vector<std::vector<Cell>>;

std::ostream& operator<<(std::ostream &stream, const Cell &cell);

std::ostream& operator<<(std::ostream &stream, const Coords &coords);

void print_grid(Grid &grid);

bool load_grid(Grid &grid, Coords &start, Coords &end, std::istream &stream=std::cin);

#define STATE_SPACE_SEARCH_GRID_H
#endif //STATE_SPACE_SEARCH_GRID_H
