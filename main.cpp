#include <iostream>
#include <fstream>
#include "grid.h"
#include "algorithms.h"

int main() {
    std::vector<std::vector<Cell>> grid;
    Coords start, end;

//    auto file = std::ifstream("dataset/4.txt");
    auto &file = std::cin;

    if(!load_grid(grid, start, end, file)) {
        std::cout << "bad input" << std::endl;
        return 1;
    }
    print_grid(grid);
}
