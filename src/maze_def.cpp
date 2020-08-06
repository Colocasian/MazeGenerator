#include <MazeGenerator/maze_def.hpp>

bool getcell(const mbit* mz, std::size_t cno) {
    return (bool)(mz[cno/BSZ] & (1 << (cno % BSZ)));
}

void setcellon(mbit* mz, std::size_t cno) {
    mz[cno/BSZ] |= (1 << (cno % BSZ));
}

void setcelloff(mbit* mz, std::size_t cno) {
    mz[cno/BSZ] &= ~(1 << (cno % BSZ));
}

void togcell(mbit* mz, std::size_t cno) {
    mz[cno/BSZ] ^= (1 << (cno % BSZ));
}

