//
// Created by standa on 2/23/20.
//

#ifndef STATE_SPACE_SEARCH_ALGORITHMS_H
#define STATE_SPACE_SEARCH_ALGORITHMS_H

#include <vector>
#include <stack>
#include "maze.h"

enum class ALGORITHM_NAME {
    INVALID, DFS, BFS, RANDOM, GREEDY, ASTAR, DIJKSTRA
};

const std::string random_string = "random";
const std::string dfs_string = "dfs";
const std::string bfs_string = "bfs";
const std::string greedy_string = "greedy";
const std::string astar_string = "astar";
const std::string dijkstra_string = "dijkstra";

class DSWrapper {
public:
    virtual ~DSWrapper() = default; 

    virtual void process_cell(Cell *next, Cell *current);
    virtual void push(Cell *cell) = 0;
    virtual Cell* pop() = 0;
    virtual bool empty() = 0;
};

class Solver {
public:
    Maze &maze;

    explicit Solver(Maze &maze, ALGORITHM_NAME name);
    ~Solver();
    std::tuple<bool, int, int> solve(bool print);

private:
    DSWrapper *ds;

    void process_cell(Cell *next, Cell *current);
    void print_maze_state(Cell *current, bool &print, int iteration_counter) const;
    Cell* down_cell(Cell *cell);
    Cell* up_cell(Cell *cell);
    Cell* left_cell(Cell *cell);
    Cell* right_cell(Cell *cell);

    static int find_path(Cell *end);
    static void revert_path(Cell *end);
};

class GreedyCompare {
public:
    bool operator()(Cell *first, Cell *second) const;
};

class DijsktraCompare {
public:
    bool operator()(Cell *first, Cell *second) const;
};

class AstarCompare {
public:
    bool operator()(Cell *first, Cell *second) const;
};

#endif //STATE_SPACE_SEARCH_ALGORITHMS_H
