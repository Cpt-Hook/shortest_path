#include <iostream>
#include <fstream>
#include "grid.h"
#include "algorithms.h"

int main(int argc, char *argv[]) {
    if(argc != 2) {
        std::cout << "Enter file name as an argument" << std::endl;
        return 1;
    }

    std::string input_file_path = argv[1];
    std::vector<std::vector<Cell>> grid, grid2;
    Coords start{}, end{};

    auto istream = std::ifstream(input_file_path);

    if(!istream) {
        std::cout << "Could not open given file" << std::endl;
        return 1;
    }

    if(!load_grid(grid, start, end, istream)) {
        std::cout << "Bad input" << std::endl;
        return 1;
    }
    grid2 = grid;

    std::cout << std::boolalpha << "dfs: " << dfs(grid, start, end) << std::endl;
    print_grid(grid);

    std::cout << std::endl;

    std::cout << std::boolalpha << "bfs: " << bfs(grid2, start, end) << std::endl;
    print_grid(grid2);
}
