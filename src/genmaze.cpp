#include <iostream>
#include <random>
#include <string>

#include <maze_def.h>

int main(int argc, char *argv[]) {
    if (argc >= 4) {
        unsigned int width = std::stoi(argv[2]);
        unsigned int height = std::stoi(argv[3]);
        if (width == 0 || height == 0) {
            std::cout << "Need positive width and height" << std::endl;
            return 0;
        }

        unsigned int wcount = (width-1)*height + width*(height-1);
        unsigned int seed;
        if (argc >= 5)
            seed = std::stoi(argv[4]);
        else {
            std::random_device rd;
            seed = rd();
        }

        char mz[(wcount + BSZ - 1)/BSZ] = {0};
        if (std::string(argv[1]) == "kruskal")
            kruskal_gen(mz, width, height, seed);
        else if (std::string(argv[1]) == "dfs")
            dfs_gen(mz, width, height, seed);
        else if (std::string(argv[1]) == "recurse_div")
            recurse_div_gen(mz, width, height, seed);
        else {
            std::cout << "Unknown algorithm" << std::endl;
            return 0;
        }

        if (argc < 5)
            std::cout << "The current seed used was " << seed << std::endl;
        printmaze(mz, width, height);
    }
}
