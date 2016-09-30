#include <iostream>

#include "easylogging++.h"
#include "application.h"
#include "printargs.h"


INITIALIZE_EASYLOGGINGPP;


int main(int argc, char *argv[]) {
    try {
        START_EASYLOGGINGPP(argc, argv);
        LOG(INFO) << "Starting app.";
        LOG(INFO) << "Commands: " << print_args(argc, argv);

        Application app;
        app.run();
    } catch (std::exception& e) {
        LOG(FATAL) << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

