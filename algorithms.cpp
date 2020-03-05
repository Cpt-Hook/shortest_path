//
// Created by standa on 2/23/20.
//

#include "algorithms.h"
#include <queue>
#include <set>
#include <tuple>
#include <stack>
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

void DSWrapper::process_cell(Cell *next, Cell *current) {
    if (next->state == STATE::UNDISCOVERED) {
        next->state = STATE::OPEN;
        next->prev = current;
        push(next);
    }
}

class DFSWrapper : public DSWrapper {
private:
    std::stack<Cell*> stack;

public:
    void push(Cell *cell) override {
        stack.push(cell);
    }

    Cell* pop() override {
        Cell *temp = stack.top();
        stack.pop();
        return temp;
    }

    bool empty() override {
        return stack.empty();
    }
};

class BFSWrapper : public DSWrapper {
private:
    std::queue<Cell*> queue;

public:
    void push(Cell *cell) override {
        queue.push(cell);
    }

    Cell* pop() override {
        Cell *temp = queue.front();
        queue.pop();
        return temp;
    }

    bool empty() override {
        return queue.empty();
    }
};

class RandomWrapper : public DSWrapper {
private:
    std::vector<Cell*> vector;

public:
    RandomWrapper() {
        std::srand(std::time(nullptr));
    }

    void push(Cell *cell) override {
        vector.push_back(cell);
    }

    Cell* pop() override {
        int index = std::rand() % vector.size();
        Cell *temp = vector[index];
        vector.erase(vector.begin() + index);
        return temp;
    }

    bool empty() override {
        return vector.empty();
    }
};

template <typename T>
class PriorityQueueWrapper : public DSWrapper {
private:
    std::multiset<Cell*, T> set;

public:
    void push(Cell *cell) override {
        set.insert(cell);
    }

    Cell* pop() override {
        auto first_iterator = set.begin();
        Cell *temp = *first_iterator;
        set.erase(first_iterator);
        return temp;
    }

    bool empty() override {
        return set.empty();
    }

protected:
    void remove(Cell* cell) {
        set.erase(cell);
    }
};

class GreedyWrapper : public PriorityQueueWrapper<GreedyCompare> {};

class DijkstraWrapper : public PriorityQueueWrapper<DijsktraCompare> {
    void process_cell(Cell *next, Cell *current) override {
        if (next->state == STATE::UNDISCOVERED) {
            next->state = STATE::OPEN;
            next->prev = current;
            next->path_length = current->path_length + 1;
            push(next);
        }else if(next->state == STATE::OPEN && next->path_length > current->path_length + 1) {
            remove(next); 
            next->path_length = current->path_length + 1;
            push(next);
        }
    }
};

class AstarWrapper : public PriorityQueueWrapper<AstarCompare> {
    void process_cell(Cell *next, Cell *current) override {
        if (next->state == STATE::UNDISCOVERED) {
            next->state = STATE::OPEN;
            next->prev = current;
            next->path_length = current->path_length + 1;
            push(next);
        }else if(next->state == STATE::OPEN && next->path_length + next->heuristic > current->path_length + 1 + current->heuristic) {
            remove(next); 
            next->path_length = current->path_length + 1;
            push(next);
        }
    }
};

bool GreedyCompare::operator()(Cell *first, Cell *second) {
    return first->heuristic < second->heuristic;
}

bool DijsktraCompare::operator()(Cell *first, Cell *second) {
    return first->path_length < second->path_length;
}

bool AstarCompare::operator()(Cell *first, Cell *second) {
    if(first->path_length + first->heuristic == second->path_length + second->heuristic) {
        return first->path_length < second->path_length;
    }else {
        return first->path_length + first->heuristic < second->path_length + second->heuristic;
    }
}

Solver::Solver(Maze &maze, ALGORITHM_NAME name) : maze(maze) {
    switch(name) {
        case ALGORITHM_NAME::BFS:
            ds = new BFSWrapper;
            break;
        case ALGORITHM_NAME::DFS:
            ds = new DFSWrapper;
            break;
        case ALGORITHM_NAME::RANDOM:
            ds = new RandomWrapper;
            break;
        case ALGORITHM_NAME::GREEDY:
            ds = new GreedyWrapper;
            break;
        case ALGORITHM_NAME::ASTAR:
            ds = new AstarWrapper;
            break;
        case ALGORITHM_NAME::DIJKSTRA:
            ds = new DijkstraWrapper;
            break;
        default:
            throw std::invalid_argument("Invalid algorithm name not caught");
    }
}

Solver::~Solver() {
    delete ds;
}

Cell* Solver::right_cell(Cell *cell) {
    if((int)maze.grid[0].size() > cell->coords.x + 1 && maze.grid[cell->coords.y][cell->coords.x + 1].blank) {
        return &maze.grid[cell->coords.y][cell->coords.x + 1];
    }
    return nullptr;
}


Cell* Solver::left_cell(Cell *cell) {
    if(cell->coords.x > 0 && maze.grid[cell->coords.y][cell->coords.x - 1].blank) {
        return &maze.grid[cell->coords.y][cell->coords.x - 1];
    }
    return nullptr;
}


Cell* Solver::up_cell(Cell *cell) {
    if(cell->coords.y > 0 && maze.grid[cell->coords.y - 1][cell->coords.x].blank) {
        return &maze.grid[cell->coords.y - 1][cell->coords.x];
    }
    return nullptr;
}

Cell* Solver::down_cell(Cell *cell) {
    if((int)maze.grid.size() > cell->coords.y + 1 && maze.grid[cell->coords.y + 1][cell->coords.x].blank) {
        return &maze.grid[cell->coords.y + 1][cell->coords.x];
    }
    return nullptr;
}

int Solver::find_path(Cell *end) {
    int counter = -1; //do not count the first node
    Cell *current = end;
    while(current) {
        ++counter;
        current->state = STATE::PATH;
        current = current->prev;
    }
    return counter;
}

void Solver::revert_path(Cell *end) {
    Cell *current = end;
    while(current) {
        current->state = STATE::CLOSED;
        current = current->prev;
    }
}

void Solver::print_maze_state(Cell *current, bool &print, int iteration_counter) const {
    printw("Iteration %d\n", iteration_counter);
    find_path(current);
    maze.print_maze();
    revert_path(current);
    if(getch() == 'q') {
        print = false;
    }
    move(0,0);
}

void Solver::process_cell(Cell *next, Cell *current) {
    ds->process_cell(next, current);
}

std::tuple<bool, int, int> Solver::solve(bool print) {
    int iteration_counter = 0;
    bool found_end = false;
    maze.get_start_cell().state = STATE::OPEN;
    ds->push(&maze.get_start_cell());

    while (!ds->empty()) {
        ++iteration_counter;
        Cell *current = ds->pop();

        if (current->coords == maze.end) {
            found_end = true;
            break;
        }

        Cell *next;
        if ((next = left_cell(current))) {
            process_cell(next, current);
        }
        if ((next = right_cell(current))) {
            process_cell(next, current);
        }
        if ((next = up_cell(current))) {
            process_cell(next, current);
        }
        if ((next = down_cell(current))) {
            process_cell(next, current);
        }

        current->state = STATE::CLOSED;

        if(print) {
            print_maze_state(current, print, iteration_counter);
        }
    }

    int path_length;
    if(found_end) {
        path_length = find_path(&maze.get_end_cell());
    }

    return {found_end, iteration_counter, path_length}; //last iteration not printed, need to increment counter
}
