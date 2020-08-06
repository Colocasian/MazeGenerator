#include <cstdlib>
#include <cstring>
#include <iostream>
#include <random>
#include <string>
#include <unistd.h>

#include "MazeGenerator/maze_algos.hpp"
#include "MazeGenerator/maze_print.hpp"

int error_prompt(char* argv[]) {
    std::cerr << argv[0] << ": do `mazer -h` for help" << std::endl;
    return 1;
}

int error_prompt(char* argv[], const char* e) {
    std::cerr << argv[0] << ": " << e << '\n';
    return error_prompt(argv);
}

int help_prompt() {
    std::cout << "MazeGenerator v0.5.0\n" <<
        "\n" <<
        "usage:\n" <<
        "  path/to/mazer -a<algo-name> -x<width> -y<height> [-p<print-style>] [-s<seed>]\n" <<
        "  path/to/mazer -h\n" <<
        "\n" <<
        "options\n" <<
        "  -a = algorithm used for maze generation\n" <<
        "  -x = width of main maze grid\n" <<
        "  -y = height of main maze grid\n" <<
        "  -p = printing style used to print maze\n" <<
        "        (uses style 'block' if not specified)\n" <<
        "  -s = seed used in maze generation\n" <<
        "        (Randomised seed is used if not provided)\n" <<
        "  -h = prints this help menu & terminates\n" <<
        "\n" <<
        "algo-name:\n" <<
        "  dfs, kruskal, recurse_div, wilson\n" <<
        "\n" <<
        "print-style:\n" <<
        "  block (default), thinwall\n" <<
        "\n" <<
        "example:\n" <<
        "  ./mazer -akruskal -x15 -y10 -s2\n" <<
        "  ./mazer -a dfs -x 20 -y 20" <<
        std::endl;
    return 0;
}

int main(int argc, char* argv[]) {
    std::string algo("");
    bool algo_spec = false;
    std::string printer("");
    bool printer_spec = false;
    int x = 0;
    bool x_spec = false;
    int y = 0;
    bool y_spec = false;
    unsigned int seed = 0;
    bool seeded = false;
    bool help = false;
    int c;

    opterr = 1;

    while ((c = getopt(argc, argv, "a:p:x:y:s:h")) != -1) {
        switch (c) {
            case 'a':
                algo_spec = true;
                algo = std::string(optarg);
                break;
            case 'p':
                printer_spec = true;
                printer = std::string(optarg);
                break;
            case 'x':
                x_spec = true;
                x = std::stoi(optarg);
                break;
            case 'y':
                y_spec = true;
                y = std::stoi(optarg);
                break;
            case 's':
                seeded = true;
                seed = std::stoi(optarg);
                break;
            case 'h':
                help = true;
                break;
            default:
                return error_prompt(argv);
        }
    }

    if (help) {
        return help_prompt();
    }

    if (!(x_spec && y_spec))
        return error_prompt(argv, "Dimensions not specified");
    if (x <= 0 || y <= 0)
        return error_prompt(argv, "Non-positive dimensions not supported");

    if (!seeded)
        seed = (std::random_device())();

    mbit mz[((x-1)*y+x*(y-1)+BSZ-1)/BSZ];
    if (!algo_spec)
        return error_prompt(argv, "No algorithm name provided");

    if (algo == "kruskal")
        kruskal_gen(mz, x, y, seed);
    else if (algo == "dfs")
        dfs_gen(mz, x, y, seed);
    else if (algo == "recurse_div")
        recurse_div_gen(mz, x, y, seed);
    else if (algo == "wilson")
        wilson_gen(mz, x, y, seed);
    else
        return error_prompt(argv, "Invalid algorithm name");

    if ((!printer_spec) || (printer == "block"))
        printmaze_block(mz, x, y);
    else if (printer == "thinwall")
        printmaze_thinwall(mz, x, y);
    else
        return error_prompt(argv, "Invalid printing style");

    if (!seeded)
        std::cout << "Seed used was " << seed << std::endl;

    std::cout << std::flush;
}
