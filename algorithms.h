//
// Created by standa on 2/23/20.
//

#ifndef STATE_SPACE_SEARCH_ALGORITHMS_H
#define STATE_SPACE_SEARCH_ALGORITHMS_H

#include <vector>
#include "grid.h"

bool bfs(Grid &grid, Coords &start, Coords &end);
bool dfs(Grid &grid, Coords &start, Coords &end);

#endif //STATE_SPACE_SEARCH_ALGORITHMS_H
