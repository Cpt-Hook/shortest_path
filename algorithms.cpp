//
// Created by standa on 2/23/20.
//

#include "algorithms.h"
#include <queue>
#include <tuple>
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
        if(next->print_char != START_CHAR && next->print_char != END_CHAR)
            next->print_char = OPEN_CHAR;
        queue.push(next);
    }
}

int find_path(Cell *end) {
    int counter = -1; //do not count the first node
    Cell *current = end;
    while(current) {
        ++counter;
        if(current->print_char != START_CHAR && current->print_char != END_CHAR)
            current->print_char = PATH_CHAR;
        current = current->prev;
    }
    return counter;
}

void revert_path(Cell *end) {
    Cell *current = end;
    while(current) {
        if(current->print_char != START_CHAR && current->print_char != END_CHAR)
            current->print_char = CLOSED_CHAR;
        current = current->prev;
    }
}

std::tuple<bool, int, int> bfs(Maze &maze, bool print) {
    int iteration_counter = 0;
    bool found_end = false;
    std::queue<Cell *> queue;
    maze.get_start_cell().state = STATE::OPEN;
    queue.push(&maze.get_start_cell());

    while (!queue.empty()) {
        Cell *current = queue.front();
        queue.pop();

        if (current->coords == maze.end) {
            found_end = true;
            break;
        }

        Cell *next;
        if ((next = left_cell(maze.grid, current))) {
            process_cell_bfs(queue, next, current);
        }
        if ((next = right_cell(maze.grid, current))) {
            process_cell_bfs(queue, next, current);
        }
        if ((next = up_cell(maze.grid, current))) {
            process_cell_bfs(queue, next, current);
        }
        if ((next = down_cell(maze.grid, current))) {
            process_cell_bfs(queue, next, current);
        }

        if(current->print_char != START_CHAR && current->print_char != END_CHAR) {
            current->print_char = CLOSED_CHAR;
        }
        current->state = STATE::CLOSED;

        ++iteration_counter;
        if(print) {
            printw("Iteration %d\n", iteration_counter);
            find_path(current);
            maze.print_maze();
            revert_path(current);
            if(getch() == 'q') {
                print = false;
            }
            move(0,0);
        }
    }

    int path_length;
    if(found_end) {
        path_length = find_path(&maze.get_end_cell());
    }

    return {found_end, ++iteration_counter, path_length}; //last iteration not printed, need to increment counter
}

inline void process_cell_dfs(std::stack<Cell*> &stack, Cell *next, Cell *current) {
    if (next->state == STATE::UNDISCOVERED) {
        next->state = STATE::OPEN;
        next->prev = current;
        if(next->print_char != START_CHAR && next->print_char != END_CHAR) 
            next->print_char = OPEN_CHAR;
        stack.push(next);
    }
}


std::tuple<bool, int, int> dfs(Maze &maze, bool print) {
    int iteration_counter = 0;
    bool found_end = false;
    std::stack<Cell*> stack;
    maze.get_start_cell().state = STATE::OPEN;
    stack.push(&maze.get_start_cell());

    while(!stack.empty()) {
        Cell *current = stack.top();
        stack.pop();

        if (current->coords == maze.end) {
            found_end = true;
            break;
        }

        Cell *next;
        if ((next = left_cell(maze.grid, current))) {
            process_cell_dfs(stack, next, current);
        }
        if ((next = right_cell(maze.grid, current))) {
            process_cell_dfs(stack, next, current);
        }
        if ((next = up_cell(maze.grid, current))) {
            process_cell_dfs(stack, next, current);
        }
        if ((next = down_cell(maze.grid, current))) {
            process_cell_dfs(stack, next, current);
        }
        if(current->print_char != START_CHAR && current->print_char != END_CHAR) {
            current->print_char = CLOSED_CHAR;
        }
        current->state = STATE::CLOSED;

        ++iteration_counter;
        if(print) {
            printw("Iteration %d\n", iteration_counter);
            find_path(current);
            maze.print_maze();
            revert_path(current);
            if(getch() == 'q') {
                print = false;
            }
            move(0, 0);
        }
    }

    int path_length;
    if(found_end) {
        path_length = find_path(&maze.get_end_cell());
    }

    return {found_end, ++iteration_counter, path_length}; //last iteration not printed, need to increment counter
}
