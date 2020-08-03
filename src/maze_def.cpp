#include <iostream>

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

void printmaze(const mbit* mz, std::size_t width, std::size_t height) {
    std::size_t mzw = (width << 1) - 1;
    std::size_t mzh = (height << 1) - 1;
    for (std::size_t i = 0; i < mzw+1; i++)
        std::cout << "██";
    std::cout << "██\n";

    for (std::size_t i = 0; i < mzh; i++) {
        std::cout << "██";
        for (std::size_t j = 0; j < mzw; j++) {
            std::size_t cellno = i * mzw + j;
            if (cellno & 1)
                std::cout << (getcell(mz, cellno >> 1)? "  ": "██");
            else
                std::cout << ((i & 1)? "██": "  ");
        }
        std::cout << "██\n";
    }

    for (std::size_t i = 0; i < mzw+1; i++)
        std::cout << "██";
    std::cout << "██\n";
}
