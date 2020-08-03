#include <iostream>

#include <MazeGenerator/maze_def.hpp>

bool getcell(const mbit* mz, int cno) {
    return (bool)(mz[cno/BSZ] & (1 << (cno % BSZ)));
}

void setcellon(mbit* mz, int cno) {
    mz[cno/BSZ] |= (1 << (cno % BSZ));
}

void setcelloff(mbit* mz, int cno) {
    mz[cno/BSZ] &= ~(1 << (cno % BSZ));
}

void togcell(mbit* mz, int cno) {
    mz[cno/BSZ] ^= (1 << (cno % BSZ));
}

void printmaze(const mbit* mz, int width, int height) {
    int mzw = (width << 1) - 1;
    int mzh = (height << 1) - 1;
    for (int i = 0; i < mzw+1; i++)
        std::cout << "██";
    std::cout << "██\n";

    for (int i = 0; i < mzh; i++) {
        std::cout << "██";
        for (int j = 0; j < mzw; j++) {
            int cellno = i * mzw + j;
            if (cellno & 1)
                std::cout << (getcell(mz, cellno >> 1)? "  ": "██");
            else
                std::cout << ((i & 1)? "██": "  ");
        }
        std::cout << "██\n";
    }

    for (int i = 0; i < mzw+1; i++)
        std::cout << "██";
    std::cout << "██\n";
}
