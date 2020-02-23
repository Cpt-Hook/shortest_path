//
// Created by standa on 2/23/20.
//

#include "algorithms.h"
#include <queue>

inline void process_cell(std::queue<Cell*> &queue, Cell *next, Cell *current) {
    if (next->state != STATE::OPEN) {
        next->state = STATE::OPEN;
        next->prev = current;
        queue.push(next);
    }
}

void find_path(Cell &end) {
    Cell *current = &end;
    while(current) {
        std::cout << current->coords << std::endl;
        current->print_char = '#';
        current = current->prev;
    }
}

void bfs(std::vector<std::vector<Cell>> &grid, Coords &start, Coords &end) {
    std::queue<Cell *> queue = std::queue<Cell *>();
    grid[start.y][start.x].state = STATE::OPEN;
    queue.push(&grid[start.y][start.x]);

    while (!queue.empty()) {
        Cell *current = queue.front();
        queue.pop();

        if (current->coords == end) {
            break;
        }
        Cell *next;
        if ((next = left_cell(grid, current))) {
            process_cell(queue, next, current);
        }
        if ((next = right_cell(grid, current))) {
            process_cell(queue, next, current);
        }
        if ((next = up_cell(grid, current))) {
            process_cell(queue, next, current);
        }
        if ((next = down_cell(grid, current))) {
            process_cell(queue, next, current);
        }
    }
    find_path(grid[end.y][end.x]);
}
