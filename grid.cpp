//
// Created by standa on 2/23/20.
//
#include "grid.h"
#include <iostream>
#include <vector>
#include <sstream>

const char *RED_ESCAPE = "\u001b[31m";
const char *GREEN_ESCAPE = "\u001b[32m";
const char *YELLOW_ESCAPE = "\u001b[33m";
const char *BLUE_ESCAPE = "\u001b[34m";
const char *RESET_ESCAPE = "\u001b[0m";

Cell::Cell(char print_char, Coords coords) :
    prev(nullptr), coords(coords), state(STATE::UNDISCOVERED), print_char(print_char) {}

std::ostream &operator<<(std::ostream &stream, const Cell &cell) {
    switch(cell.print_char) {
        case '#':
            stream << GREEN_ESCAPE;
            break;
        case '*':
            stream << YELLOW_ESCAPE;
            break;
        case '-':
            stream << RED_ESCAPE;
            break;
        case 'S':
        case 'E':
            stream << BLUE_ESCAPE;
            break;
        default:
            break;
    }
    stream << cell.print_char << RESET_ESCAPE;
    return stream;
}

std::ostream &operator<<(std::ostream &stream, const Coords &coords) {
    stream << coords.x << ", " << coords.y;
    return stream;
}

bool Coords::operator==(const Coords &other) {
    return x == other.x && y == other.y;
}

void print_grid(Grid &grid) {
    for(const std::vector<Cell> &row : grid) {
       for(const Cell &cell : row) {
          std::cout << cell;
       }
       std::cout << std::endl;
    }
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
                grid.back().emplace_back(cell_char, current);
                ++current.x;
            }
            current.x = 0;
            ++current.y;
        }
    }
    return true;
}
