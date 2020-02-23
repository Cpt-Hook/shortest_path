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
    friend std::ostream& operator<<(std::ostream &stream, const Cell &cell);
};

std::ostream& operator<<(std::ostream &stream, const Cell &cell);

std::ostream& operator<<(std::ostream &stream, const Coords &coords);

void print_grid(std::vector<std::vector<Cell>> &grid);

bool load_grid(std::vector<std::vector<Cell>> &grid, Coords &start, Coords &end, std::istream &stream=std::cin);

Cell* left_cell(std::vector<std::vector<Cell>> &grid, Cell *cell);
Cell *right_cell(std::vector<std::vector<Cell>> &grid, Cell *cell);
Cell *up_cell(std::vector<std::vector<Cell>> &grid, Cell *cell);
Cell *down_cell(std::vector<std::vector<Cell>> &grid, Cell *cell);

#define STATE_SPACE_SEARCH_GRID_H
#endif //STATE_SPACE_SEARCH_GRID_H
