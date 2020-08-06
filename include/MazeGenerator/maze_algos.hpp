#ifndef COLOC_MAZE_ALGORITHMS
#define COLOC_MAZE_ALGORITHMS

#include "MazeGenerator/maze_def.hpp"

void kruskal_gen(mbit *mz, const std::size_t width, const std::size_t height, const unsigned int seed);
void dfs_gen(mbit *mz, const std::size_t width, const std::size_t height, const unsigned int seed);
void recurse_div_gen(mbit *mz, const std::size_t width, const std::size_t height, const unsigned int seed);
void wilson_gen(mbit *mz, const std::size_t mz_w, const std::size_t mz_h, const unsigned int seed);

#endif
