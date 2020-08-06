#ifndef COLOC_MAZE_PRINTING
#define COLOC_MAZE_PRINTING

#include "MazeGenerator/maze_def.hpp"

void printmaze_block(const mbit *mz, std::size_t width, std::size_t height);
void printmaze_thinwall(const mbit *mz, std::size_t width, std::size_t height);

#endif
