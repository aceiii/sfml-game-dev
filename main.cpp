
#include <iostream>

#include "game.h"
#include "printargs.h"


int main(int argc, char *argv[]) {
    try {
        std::cout << "Starting app." << std::endl;
        std::cout << "Commands: " << print_args(argc, argv) << std::endl;

        Game game;
        game.run();
    } catch (std::exception& e) {
        std::cout << "\nEXCEPTION: " << e.what() << std::endl;
    }
    return 0;
}

