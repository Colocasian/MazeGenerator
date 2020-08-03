#ifndef COLOC_MAZE_DEFINITIONS
#define COLOC_MAZE_DEFINITIONS

#include <cstddef>

typedef char mbit;
#define BSZ (8*sizeof(mbit))

bool getcell(const mbit* mz, std::size_t cno);
void setcellon(mbit* mz, std::size_t cno);
void setcelloff(mbit* mz, std::size_t cno);
void togcell(mbit* mz, std::size_t cno);
void printmaze(const mbit *mz, std::size_t width, std::size_t height);

void kruskal_gen(mbit *mz, const std::size_t width, const std::size_t height, const unsigned int seed);
void dfs_gen(mbit *mz, const std::size_t width, const std::size_t height, const unsigned int seed);
void recurse_div_gen(mbit *mz, const std::size_t width, const std::size_t height, const unsigned int seed);
#endif
