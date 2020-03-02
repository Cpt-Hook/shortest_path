//
// Created by standa on 2/23/20.
//

#ifndef STATE_SPACE_SEARCH_ALGORITHMS_H
#define STATE_SPACE_SEARCH_ALGORITHMS_H

#include <vector>
#include "maze.h"

std::tuple<bool, int, int> bfs(Maze &maze, bool print=true);
std::tuple<bool, int, int> dfs(Maze &maze, bool print=true);
std::tuple<bool, int, int> random_search(Maze &maze, bool print=true);

#endif //STATE_SPACE_SEARCH_ALGORITHMS_H
