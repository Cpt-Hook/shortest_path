#include <iostream>
#include <fstream>
#include <ncurses.h>
#include <cstring>
#include "grid.h"
#include "algorithms.h"

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

int main(int argc, char *argv[]) {
    if(argc != 3) {
        std::cout << "Arguments: file_name algorithm" << std::endl;
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


    if(strcmp(argv[2], "dfs") == 0) {
        init_ncurses();
        dfs(grid, start, end);
    }else if(strcmp(argv[2], "bfs") == 0) {
        init_ncurses();
        bfs(grid, start, end);
    }else {
        std::cout << "Bad algorithm" << std::endl;
        return 1;
    }
    print_grid(grid);

    addch('\n');
    printw("Press q to quit");
    int input;
    while((input = getch()) != 'q') {
        ;
    }

    endwin();
}
