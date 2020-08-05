#include <cstdlib>
#include <cstring>
#include <iostream>
#include <random>
#include <unistd.h>

#include <MazeGenerator/maze_def.hpp>

int main(int argc, char* argv[]) {
    char* algo = nullptr;
    int x = 0;
    int y = 0;
    bool seeded = false;
    unsigned int seed = 0;
    bool help = false;
    int c;

    opterr = 1;

    while ((c = getopt(argc, argv, "a:x:y:s:h")) != -1) {
        switch (c) {
            case 'a':
                algo = optarg;
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
        std::cout << "MazeGenerator v0.4.0\n" <<
            "\n" <<
            "usage:\n" <<
            "  path/to/mazer -a<algo-name> -x<width> -y<height> [-s<seed>]\n" <<
            "  path/to/mazer -h\n" <<
            "\n" <<
            "options\n" <<
            "  -a = algorithm used for maze generation\n" <<
            "  -x = width of main maze grid\n" <<
            "  -y = height of main maze grid\n" <<
            "  -s = seed used in maze generation\n" <<
            "        (Randomised seed is used if not provided)\n" <<
            "  -h = prints this help menu & terminates\n" <<
            "\n" <<
            "algo-names:\n" <<
            "  dfs, kruskal, recurse_div, wilson\n" <<
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

    char mz[((x-1)*y+x*(y-1)+BSZ-1)/BSZ];
    if (algo == nullptr) {
        std::cerr << "No algorithm name provided" << std::endl;
        return 1;
    } else if (!std::strcmp(algo, "kruskal"))
        kruskal_gen(mz, x, y, seed);
    else if (!std::strcmp(algo, "dfs"))
        dfs_gen(mz, x, y, seed);
    else if (!std::strcmp(algo, "recurse_div"))
        recurse_div_gen(mz, x, y, seed);
    else if (!std::strcmp(algo, "wilson"))
        wilson_gen(mz, x, y, seed);
    else {
        std::cerr << "Invalid algorithm name" << std::endl;
        return 1;
    }

    if (!seeded)
        std::cout << "Seed used was " << seed << std::endl;
    printmaze(mz, x, y);
    std::cout << std::flush;
}
