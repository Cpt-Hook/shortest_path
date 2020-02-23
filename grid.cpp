//
// Created by standa on 2/23/20.
//
#include "grid.h"
#include <iostream>
#include <vector>
#include <sstream>

Cell::Cell(char print_char, Coords coords) :
    prev(nullptr), coords(coords), state(STATE::UNDISCOVERED), print_char(print_char) {}

std::ostream &operator<<(std::ostream &stream, const Cell &cell) {
    stream << cell.print_char;
    return stream;
}

std::ostream &operator<<(std::ostream &stream, const Coords &coords) {
    stream << coords.x << ", " << coords.y;
    return stream;
}

bool Coords::operator==(const Coords &other) {
    return x == other.x && y == other.y;
}

void print_grid(std::vector<std::vector<Cell>> &grid) {
    for(const std::vector<Cell> &row : grid) {
       for(const Cell &cell : row) {
          std::cout << cell;
       }
       std::cout << std::endl;
    }
}


bool load_grid(std::vector<std::vector<Cell>> &grid, Coords &start, Coords &end, std::istream &istream) {
    std::string line;
    Coords current = {0, 0};

    while(std::getline(istream, line)) {
        if(line.empty()) {
            continue;
        }
        if(line[0] == 's') {
            auto stream = std::istringstream(line);
            std::string temp;
            if(!(stream >> temp) || temp != "start" || !(stream >> start.x)
               || !(stream >> temp) || temp != "," || !(stream >> start.y)) {
                return false;
            }
        }else if(line[0] == 'e') {
            auto stream = std::istringstream(line);
            std::string temp;
            if(!(stream >> temp) || temp != "end" || !(stream >> end.x)
               || !(stream >> temp) || temp != "," || !(stream >> end.y)) {
                return false;
            }
        }else {
            grid.emplace_back();
            for(char cell_char : line) {
                grid.back().emplace_back(cell_char, current);
                ++current.x;
            }
            current.x = 0;
            ++current.y;
        }
    }
    return true;
}

Cell *right_cell(std::vector<std::vector<Cell>> &grid, Cell *cell) {
    if(grid[0].size() > cell->coords.x + 1 && grid[cell->coords.y][cell->coords.x + 1].print_char == ' ') {
        return &grid[cell->coords.y][cell->coords.x + 1];
    }
    return nullptr;
}


Cell *left_cell(std::vector<std::vector<Cell>> &grid, Cell *cell) {
    if(cell->coords.x > 0 && grid[cell->coords.y][cell->coords.x - 1].print_char == ' ') {
        return &grid[cell->coords.y][cell->coords.x - 1];
    }
    return nullptr;
}


Cell *up_cell(std::vector<std::vector<Cell>> &grid, Cell *cell) {
    if(cell->coords.y > 0 && grid[cell->coords.y - 1][cell->coords.x].print_char == ' ') {
        return &grid[cell->coords.y - 1][cell->coords.x];
    }
    return nullptr;
}

Cell *down_cell(std::vector<std::vector<Cell>> &grid, Cell *cell) {
    if(grid.size() > cell->coords.y + 1 && grid[cell->coords.y + 1][cell->coords.x].print_char == ' ') {
        return &grid[cell->coords.y + 1][cell->coords.x];
    }
    return nullptr;
}
