//
// Created by standa on 2/23/20.
//
#include "grid.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <ncurses.h>

Cell::Cell(char print_char, Coords coords, bool blank) :
    prev(nullptr), coords(coords), state(STATE::UNDISCOVERED), print_char(print_char), blank(blank) {}

void Cell::print() const {
    switch(print_char) {
        case '#':
            addch(print_char | COLOR_PAIR(GREEN_PAIR));
            break;
        case '*':
            addch(print_char | COLOR_PAIR(YELLOW_PAIR));
            break;
        case '-':
            addch(print_char | COLOR_PAIR(RED_PAIR));
            break;
        case 'S':
        case 'E':
            addch(print_char | COLOR_PAIR(BLUE_PAIR));
            break;
        default:
            addch(print_char);
            break;
    }
}

std::ostream &operator<<(std::ostream &stream, const Coords &coords) {
    stream << coords.x << ", " << coords.y;
    return stream;
}

bool Coords::operator==(const Coords &other) {
    return x == other.x && y == other.y;
}

void print_grid(const Grid &grid) {
    for(const std::vector<Cell> &row : grid) {
       for(const Cell &cell : row) {
           cell.print();
       }
       addch('\n');
    }
    refresh();
}


bool load_grid(Grid &grid, Coords &start, Coords &end, std::istream &istream) {
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
                grid.back().emplace_back(cell_char, current, cell_char == ' ');
                ++current.x;
            }
            current.x = 0;
            ++current.y;
        }
    }
    grid[start.y][start.x].print_char = 'S';
    grid[end.y][end.x].print_char = 'E';
    return true;
}
