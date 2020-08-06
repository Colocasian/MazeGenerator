#include <cstdlib>
#include <cstring>
#include <iostream>
#include <random>
#include <string>
#include <unistd.h>

#include "MazeGenerator/maze_algos.hpp"
#include "MazeGenerator/maze_print.hpp"

int main(int argc, char* argv[]) {
    std::string algo("");
    std::string printer("");
    bool printer_specified = false;
    int x = 0;
    int y = 0;
    bool seeded = false;
    unsigned int seed = 0;
    bool help = false;
    int c;

    opterr = 1;

    while ((c = getopt(argc, argv, "a:p:x:y:s:h")) != -1) {
        switch (c) {
            case 'a':
                algo = std::string(optarg);
                break;
            case 'p':
                printer_specified = true;
                printer = std::string(optarg);
                break;
            case 'x':
                x = std::stoi(optarg);
                break;
            case 'y':
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
                return 1;
        }
    }

    if (help) {
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

    if (x <= 0 || y <= 0) {
        std::cerr << "Positive height & width required" << std::endl;
        return 1;
    }

    if (!seeded)
        seed = (std::random_device())();

    mbit mz[((x-1)*y+x*(y-1)+BSZ-1)/BSZ];
    if (algo == "") {
        std::cerr << "No algorithm name provided" << std::endl;
        return 1;
    } else if (algo == "kruskal")
        kruskal_gen(mz, x, y, seed);
    else if (algo == "dfs")
        dfs_gen(mz, x, y, seed);
    else if (algo == "recurse_div")
        recurse_div_gen(mz, x, y, seed);
    else if (algo == "wilson")
        wilson_gen(mz, x, y, seed);
    else {
        std::cerr << "Invalid algorithm name" << std::endl;
        return 1;
    }

    if ((!printer_specified) || (printer == "block"))
        printmaze_block(mz, x, y);
    else if (printer == "thinwall")
        printmaze_thinwall(mz, x, y);
    else {
        std::cout << "Invalid printing style" << std::endl;
        return 1;
    }

    if (!seeded)
        std::cout << "Seed used was " << seed << std::endl;

    std::cout << std::flush;
}
