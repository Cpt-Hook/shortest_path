//
// Created by standa on 2/23/20.
//

#include "algorithms.h"
#include <queue>
#include <stack>
#include <ncurses.h>

inline Cell *right_cell(Grid &grid, Cell *cell) {
    if((int)grid[0].size() > cell->coords.x + 1 && grid[cell->coords.y][cell->coords.x + 1].blank) {
        return &grid[cell->coords.y][cell->coords.x + 1];
    }
    return nullptr;
}


inline Cell *left_cell(Grid &grid, Cell *cell) {
    if(cell->coords.x > 0 && grid[cell->coords.y][cell->coords.x - 1].blank) {
        return &grid[cell->coords.y][cell->coords.x - 1];
    }
    return nullptr;
}


inline Cell *up_cell(Grid &grid, Cell *cell) {
    if(cell->coords.y > 0 && grid[cell->coords.y - 1][cell->coords.x].blank) {
        return &grid[cell->coords.y - 1][cell->coords.x];
    }
    return nullptr;
}

inline Cell *down_cell(Grid &grid, Cell *cell) {
    if((int)grid.size() > cell->coords.y + 1 && grid[cell->coords.y + 1][cell->coords.x].blank) {
        return &grid[cell->coords.y + 1][cell->coords.x];
    }
    return nullptr;
}

inline void process_cell_bfs(std::queue<Cell*> &queue, Cell *next, Cell *current) {
    if (next->state == STATE::UNDISCOVERED) {
        next->state = STATE::OPEN;
        next->prev = current;
        if(next->print_char != 'S' && next->print_char != 'E')
            next->print_char = '*';
        queue.push(next);
    }
}

void find_path(Cell &end) {
    Cell *current = &end;
    while(current) {
        if(current->print_char != 'S' && current->print_char != 'E')
            current->print_char = '#';
        current = current->prev;
    }
}

bool bfs(Grid &grid, Coords &start, Coords &end, bool print) {
    bool found_end = false;
    std::queue<Cell *> queue;
    grid[start.y][start.x].state = STATE::OPEN;
    queue.push(&grid[start.y][start.x]);

    while (!queue.empty()) {
        Cell *current = queue.front();
        queue.pop();

        if(print) {
            print_grid(grid);
            getch();
            move(0,0);
        }

        if (current->coords == end) {
            found_end = true;
            break;
        }

        Cell *next;
        if ((next = left_cell(grid, current))) {
            process_cell_bfs(queue, next, current);
        }
        if ((next = right_cell(grid, current))) {
            process_cell_bfs(queue, next, current);
        }
        if ((next = up_cell(grid, current))) {
            process_cell_bfs(queue, next, current);
        }
        if ((next = down_cell(grid, current))) {
            process_cell_bfs(queue, next, current);
        }

        if(current->print_char != 'S' && current->print_char != 'E') {
            current->print_char = '-';
        }
        current->state = STATE::CLOSED;
    }

    if(found_end) {
        find_path(grid[end.y][end.x]);
    }
    grid[start.y][start.x].print_char = 'S';
    grid[end.y][end.x].print_char = 'E';

    return found_end;
}

inline void process_cell_dfs(std::stack<Cell*> &stack, Cell *next, Cell *current) {
    if (next->state == STATE::UNDISCOVERED) {
        next->state = STATE::OPEN;
        next->prev = current;
        if(next->print_char != 'S' && next->print_char != 'E')
            next->print_char = '*';
        stack.push(next);
    }
}


bool dfs(Grid &grid, Coords &start, Coords &end, bool print) {
    bool found_end = false;
    std::stack<Cell*> stack;
    grid[start.y][start.x].state = STATE::OPEN;
    stack.push(&grid[start.y][start.x]);

    while(!stack.empty()) {
        Cell *current = stack.top();
        stack.pop();

        if(print) {
            print_grid(grid);
            getch();
            move(0, 0);
        }

        if (current->coords == end) {
            found_end = true;
            break;
        }

        Cell *next;
        if ((next = left_cell(grid, current))) {
            process_cell_dfs(stack, next, current);
        }
        if ((next = right_cell(grid, current))) {
            process_cell_dfs(stack, next, current);
        }
        if ((next = up_cell(grid, current))) {
            process_cell_dfs(stack, next, current);
        }
        if ((next = down_cell(grid, current))) {
            process_cell_dfs(stack, next, current);
        }
        if(current->print_char != 'S' && current->print_char != 'E') {
            current->print_char = '-';
        }
        current->state = STATE::CLOSED;
    }

    if(found_end) {
        find_path(grid[end.y][end.x]);
    }

    return found_end;
}
