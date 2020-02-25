#include <iostream>
#include <fstream>
#include <ncurses.h>
#include <cstring>
#include <tuple>
#include <cstring>
#include "grid.h"
#include "algorithms.h"

enum class ALGORITHM_NAME {
    INVALID, DFS, BFS
};

const std::string dfs_string = "dfs";
const std::string bfs_string = "bfs";

ALGORITHM_NAME check_algorithm_name(const std::string input) {
    if(input == dfs_string) {
        return ALGORITHM_NAME::DFS;
    }else if(input == bfs_string) {
        return ALGORITHM_NAME::BFS;
    }else {
        return ALGORITHM_NAME::INVALID;
    }
}

std::tuple<bool, int, int> run_algorithm(ALGORITHM_NAME name, Maze &maze, bool print) {
    switch(name) {
        case ALGORITHM_NAME::BFS:
            return bfs(maze, print);
            break;
        case ALGORITHM_NAME::DFS:
            return dfs(maze, print);
            break;
        default:
            return {false, -1, -1};
            break;
    }
}

void init_ncurses() {
    initscr(); cbreak();
    noecho();
    keypad(stdscr, true);
    start_color();
    use_default_colors();
    init_pair(BLUE_PAIR, COLOR_BLUE, -1);
    init_pair(RED_PAIR, COLOR_RED, -1);
    init_pair(YELLOW_PAIR, COLOR_YELLOW, -1);
    init_pair(GREEN_PAIR, COLOR_GREEN, -1);
}

void ncurses_print(ALGORITHM_NAME algorithm, Maze &maze, bool print) {
    init_ncurses();

    auto [found_end, iteration_counter, path_length] = run_algorithm(algorithm, maze, print);

    if(found_end) {
        printw("Iteration count: %d, path length: %d\n", iteration_counter, path_length);
    }else {
        printw("Iteration count: %d, path not found\n", iteration_counter);
    }
    maze.print_maze();

    printw("Press q to quit");
    int input;
    while((input = getch()) != 'q') {
        ;
    }

    endwin();
}

int main(int argc, char *argv[]) {
    if(argc < 3) {
        std::cout << "Arguments: file_name algorithm [noprint]" << std::endl;
        return 1;
    }

    ALGORITHM_NAME algorithm = check_algorithm_name(argv[2]);
    if(algorithm == ALGORITHM_NAME::INVALID) {
        std::cout << "Bad algorithm" << std::endl;
        return 1;
    }

    std::string input_file_path = argv[1];
    std::ifstream ifstream = std::ifstream(input_file_path);

    if(!ifstream) {
        std::cout << "Could not open given file" << std::endl;
        return 1;
    }

    Maze maze;
    if(!maze.load_maze(ifstream)) {
        std::cout << "Bad input" << std::endl;
        return 1;
    }

    bool print = !(argc >= 4 && strcmp(argv[3], "noprint") == 0);

    ncurses_print(algorithm, maze, print);
}
