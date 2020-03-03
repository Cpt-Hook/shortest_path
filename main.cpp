#include <iostream>
#include <fstream>
#include <ncurses.h>
#include <cstring>
#include <tuple>
#include <cstring>
#include "maze.h"
#include "algorithms.h"

const std::string help_string = 
R"(Arguments: file_name algorithm [noprint]
algorithm: 'dfs', 'bfs', 'random', 'greedy', 'dijkstra', 'astar'
noprint: does not run an animation, only prints final path through the maze)";

ALGORITHM_NAME check_algorithm_name(const std::string input) {
    if(input == dfs_string) {
        return ALGORITHM_NAME::DFS;
    }else if(input == bfs_string) {
        return ALGORITHM_NAME::BFS;
    }else if(input == random_string) {
        return ALGORITHM_NAME::RANDOM;
    }else if(input == greedy_string){
        return ALGORITHM_NAME::GREEDY;
    }else if(input == astar_string){
        return ALGORITHM_NAME::ASTAR;
    }else if(input == dijkstra_string){
        return ALGORITHM_NAME::DIJKSTRA;
    }else {
        return ALGORITHM_NAME::INVALID;
    }
}

void init_ncurses() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);
    start_color();
    use_default_colors();
    init_pair(BLUE_PAIR, COLOR_BLUE, -1);
    init_pair(RED_PAIR, COLOR_RED, -1);
    init_pair(YELLOW_PAIR, COLOR_YELLOW, -1);
    init_pair(GREEN_PAIR, COLOR_GREEN, -1);
}

void ncurses_print(Solver &solver) {
    init_ncurses();

    auto [found_end, iteration_counter, path_length] = solver.solve(true);

    if(found_end) {
        printw("Iteration count: %d, path length: %d\n", iteration_counter, path_length);
    }else {
        printw("Iteration count: %d, path not found\n", iteration_counter);
    }
    solver.maze.print_maze();

    printw("Press q to quit");
    int input;
    while((input = getch()) != 'q') {
        ;
    }

    endwin();
}

void normal_print(Solver &solver) {
    auto [found_end, iteration_counter, path_length] = solver.solve(false);

    if(found_end) {
        std::cout << "Iteration count: " << iteration_counter << ", path length: " << path_length << std::endl;
    }else {
        std::cout << "Iteration count: " << iteration_counter << ", path not found" << std::endl;
    }
    std::cout << solver.maze;
}

int main(int argc, char *argv[]) {
    if(argc < 3) {
        std::cout << help_string << std::endl;
        return 1;
    }

    ALGORITHM_NAME algorithm = check_algorithm_name(argv[2]);
    if(algorithm == ALGORITHM_NAME::INVALID) {
        std::cout << "Bad algorithm" << std::endl;
        std::cout << help_string << std::endl;
        return 1;
    }

    std::ifstream ifstream = std::ifstream(argv[1]);
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
    Solver solver(maze, algorithm);

    if(print) {
        ncurses_print(solver);
    } else {
        normal_print(solver);
    }
}
