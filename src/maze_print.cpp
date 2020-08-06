#include <iostream>

#include <MazeGenerator/maze_def.hpp>

void printmaze_block(const mbit* mz, std::size_t width, std::size_t height) {
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

void printmaze_thinwall(const mbit* mz, std::size_t width, std::size_t height) {
    std::size_t mzw = (width << 1) - 1;
    std::size_t mzh = (height << 1) - 1;
    for (std::size_t i = 0; i < mzw+1; i++)
        std::cout << "██";
    std::cout << "██\n";

    for (std::size_t i = 0; i < mzh; i++) {
        std::cout << "██";
        for (std::size_t j = 0; j < mzw; j++) {
            std::size_t cellno = i * mzw + j;
            if (cellno & 1) {
                std::size_t wallno = cellno >> 1;
                if (getcell(mz, wallno))
                    std::cout << "  ";
                else {
                    if (wallno % ((width << 1)-1) < (width-1))
                        std::cout <<  "│ ";
                    else
                        std::cout <<  "──";
                }
            } else {
                if (i & 1) {
                    std::size_t rw = (cellno >> 1);
                    int wall_check = ((int)(!getcell(mz, rw-1)) << 3) |
                        ((int)(!getcell(mz, rw+width-1)) << 2) |
                        ((int)(!getcell(mz, rw)) << 1) |
                        ((int)(!getcell(mz, rw-width)));
                    switch (wall_check) {
                        case 0b0000:
                            std::cout << "  ";
                            break;
                        case 0b0001:
                            std::cout << "╵ ";
                            break;
                        case 0b0010:
                            std::cout << "╶─";
                            break;
                        case 0b0011:
                            std::cout << "└─";
                            break;
                        case 0b0100:
                            std::cout << "╷ ";
                            break;
                        case 0b0101:
                            std::cout << "│ ";
                            break;
                        case 0b0110:
                            std::cout << "┌─";
                            break;
                        case 0b0111:
                            std::cout << "├─";
                            break;
                        case 0b1000:
                            std::cout << "╴ ";
                            break;
                        case 0b1001:
                            std::cout << "┘ ";
                            break;
                        case 0b1010:
                            std::cout << "──";
                            break;
                        case 0b1011:
                            std::cout << "┴─";
                            break;
                        case 0b1100:
                            std::cout << "┐ ";
                            break;
                        case 0b1101:
                            std::cout << "┤ ";
                            break;
                        case 0b1110:
                            std::cout << "┬─";
                            break;
                        case 0b1111:
                            std::cout << "┼─";
                            break;
                        default:
                            std::cout << "██";
                            break;
                    }
                } else
                    std::cout << "  ";
            }
        }
        std::cout << "██\n";
    }

    for (std::size_t i = 0; i < mzw+1; i++)
        std::cout << "██";
    std::cout << "██\n";
}

