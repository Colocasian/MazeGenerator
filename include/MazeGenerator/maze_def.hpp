#ifndef COLOC_MAZE_DEFINITIONS
#define COLOC_MAZE_DEFINITIONS

#include <cstddef>

typedef char mbit;
#define BSZ (8 * sizeof(mbit))

bool getcell(const mbit *mz, std::size_t cno);
void setcellon(mbit *mz, std::size_t cno);
void setcelloff(mbit *mz, std::size_t cno);
void togcell(mbit *mz, std::size_t cno);

#endif
