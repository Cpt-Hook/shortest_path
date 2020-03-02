//
// Created by standa on 2/23/20.
//
#include "maze.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <ncurses.h>

Cell::Cell(Coords coords, bool blank) :
    prev(nullptr), coords(coords), state(STATE::UNDISCOVERED), blank(blank) {}

char Cell::get_print_char() const {
    if(!blank) {
        return WALL_CHAR;
    }else if(state == STATE::UNDISCOVERED) {
        return BLANK_CHAR;
    }else if(state == STATE::CLOSED) {
        return CLOSED_CHAR;
    }else if(state == STATE::OPEN) {
        return OPEN_CHAR;
    }
    return PATH_CHAR;
}

void Cell::addchar() const {
    char print_char = get_print_char();
    switch(print_char) {
        case PATH_CHAR:
            addch(print_char | COLOR_PAIR(GREEN_PAIR));
            break;
        case OPEN_CHAR:
            addch(print_char | COLOR_PAIR(YELLOW_PAIR));
            break;
        case CLOSED_CHAR:
            addch(print_char | COLOR_PAIR(RED_PAIR));
            break;
        default:
            addch(print_char);
            break;
    }
}

void Cell::addchar_start() {
    addch(START_CHAR | COLOR_PAIR(BLUE_PAIR));
}

void Cell::addchar_end() {
    addch(END_CHAR | COLOR_PAIR(BLUE_PAIR));
}

bool Maze::load_maze(std::istream &istream) {
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
                grid.back().emplace_back(current, cell_char == ' ');
                ++current.x;
            }
            current.x = 0;
            ++current.y;
        }
    }
    return true;
}

Cell& Maze::get_cell(Coords coords) {
    return grid[coords.y][coords.x];
}

Cell& Maze::get_start_cell() {
    return get_cell(start);
}

Cell& Maze::get_end_cell() {
    return get_cell(end);
}

std::ostream &operator<<(std::ostream &stream, const Coords &coords) {
    stream << coords.x << ", " << coords.y;
    return stream;
}

std::ostream &operator<<(std::ostream &stream, const Cell &cell) {
    stream << cell.get_print_char();
    return stream;
}

std::ostream &operator<<(std::ostream &stream, const Maze &maze) {
    for(size_t i = 0; i < maze.grid.size(); ++i) {
        for(size_t j = 0; j < maze.grid[0].size(); ++j) {
            Coords current_coords = {(int)j, (int)i};
            if(current_coords == maze.start) {
                stream << START_CHAR;
            }else if(current_coords == maze.end) {
                stream << END_CHAR;
            }else {
                stream << maze.grid[i][j];
            }
        }
        stream << std::endl;
    }
    return stream;
}

bool Coords::operator==(const Coords &other) const {
    return x == other.x && y == other.y;
}

void Maze::print_maze() const {
    for(size_t i = 0; i < grid.size(); ++i) {
        for(size_t j = 0; j < grid[0].size(); ++j) {
            Coords current_coords = {(int)j, (int)i};
            if(current_coords == start) {
                Cell::addchar_start();
            }else if(current_coords == end) {
                Cell::addchar_end();
            }else {
                grid[i][j].addchar();
            }
        }
        addch('\n');
    }
    refresh();
}

