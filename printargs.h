#ifndef __PRINT_ARGS_H__
#define __PRINT_ARGS_H__

#include <ostream>


struct args_print_context_t {
    int argc;
    char **argv;

    args_print_context_t(int a, char* b[]):argc(a),argv(b) {}
};

args_print_context_t print_args(int argc, char *argv[]) {
    return args_print_context_t(argc, argv);
}

std::ostream& operator<< (std::ostream& os, const args_print_context_t& a) {
    os << "args: [";
    for (int i = 0; i < a.argc; i += 1) {
        os << "'" << a.argv[i] << "',";
    }
    os << "]";
    return os;
}


#endif//__PRINT_ARGS_H__
