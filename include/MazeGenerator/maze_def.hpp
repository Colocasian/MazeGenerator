#ifndef COLOC_MAZE_DEFINITIONS
#define COLOC_MAZE_DEFINITIONS

#include <cstddef>

typedef char mbit;
#define BSZ (8*sizeof(mbit))

bool getcell(const mbit* mz, int cno);
void setcellon(mbit* mz, int cno);
void setcelloff(mbit* mz, int cno);
void togcell(mbit* mz, int cno);
void printmaze(const mbit *mz, int width, int height);

void kruskal_gen(mbit *mz, const std::size_t width, const std::size_t height, const unsigned int seed);
void dfs_gen(mbit *mz, const std::size_t width, const std::size_t height, const unsigned int seed);
void recurse_div_gen(mbit *mz, const std::size_t width, const std::size_t height, const unsigned int seed);
#endif
