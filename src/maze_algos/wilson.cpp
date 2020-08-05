#include <cstring>
#include <random>
#include <unordered_map>
#include <utility>

#include "MazeGenerator/maze_def.hpp"

void wilson_gen(mbit *mz, const std::size_t mz_w, const std::size_t mz_h, const unsigned int seed) {
    std::size_t ccount = mz_w * mz_h;
    std::size_t wcount = (mz_w-1)*mz_h + (mz_h-1)*mz_w;

    std::memset(mz, 0, ((wcount+BSZ-1)/BSZ) * sizeof(mbit));
    mbit partof_mz[(ccount+BSZ-1)/BSZ];
    std::memset(partof_mz, 0, ((ccount+BSZ-1)/BSZ) * sizeof(mbit));
    std::mt19937 mt(seed);

    std::size_t starter = (std::uniform_int_distribution<std::size_t>(0, ccount-1))(mt);
    setcellon(partof_mz, starter);

    std::size_t cells_left = ccount - 1;

    while (cells_left) {
        std::unordered_map<std::size_t, std::size_t> tmp_strg;

        tmp_strg[(std::size_t)(-1)] = (std::uniform_int_distribution<std::size_t>(0, ccount-1))(mt);
        std::size_t crrnt_pos = tmp_strg[(std::size_t)(-1)];
        std::size_t prnt_pos = (std::size_t)(-1);

        while (!getcell(partof_mz, crrnt_pos)) {
            int dirs_pos[4];
            int dirs_top = 0;

            if (crrnt_pos < ccount - mz_w && crrnt_pos+mz_w != prnt_pos)
                dirs_pos[dirs_top++] = 0;
            if (crrnt_pos % mz_w != mz_w-1 && crrnt_pos+1 != prnt_pos)
                dirs_pos[dirs_top++] = 1;
            if (crrnt_pos >= mz_w && crrnt_pos-mz_w != prnt_pos)
                dirs_pos[dirs_top++] = 2;
            if (crrnt_pos % mz_w != 0 && crrnt_pos-1 != prnt_pos)
                dirs_pos[dirs_top++] = 3;

            prnt_pos = crrnt_pos;
            switch(dirs_pos[(std::uniform_int_distribution<int>(0,dirs_top-1))(mt)]) {
                case 0:
                    crrnt_pos += mz_w;
                    break;
                case 1:
                    crrnt_pos++;
                    break;
                case 2:
                    crrnt_pos -= mz_w;
                    break;
                case 3:
                    crrnt_pos--;
                    break;
            }

            tmp_strg[prnt_pos] = crrnt_pos;
            if (tmp_strg.find(crrnt_pos) != tmp_strg.end()) {
                std::size_t del_pos = tmp_strg[crrnt_pos];
                while (del_pos != crrnt_pos) {
                    std::size_t tmp_num = del_pos;
                    del_pos = tmp_strg[del_pos];
                    tmp_strg.erase(tmp_num);
                }

                if (crrnt_pos < ccount - mz_w && tmp_strg.find(crrnt_pos+mz_w) != tmp_strg.end() && tmp_strg[crrnt_pos+mz_w] == crrnt_pos)
                    prnt_pos = crrnt_pos+mz_w;
                else if (crrnt_pos % mz_w != mz_w-1 && tmp_strg.find(crrnt_pos+1) != tmp_strg.end() && tmp_strg[crrnt_pos+1] == crrnt_pos)
                    prnt_pos = crrnt_pos+1;
                else if (crrnt_pos >= mz_w && tmp_strg.find(crrnt_pos-mz_w) != tmp_strg.end() && tmp_strg[crrnt_pos-mz_w] == crrnt_pos)
                    prnt_pos = crrnt_pos-mz_w;
                else if (crrnt_pos % mz_w != 0 && tmp_strg.find(crrnt_pos-1) != tmp_strg.end() && tmp_strg[crrnt_pos-1] == crrnt_pos)
                    prnt_pos = crrnt_pos-1;
                else
                    prnt_pos = (std::size_t)(-1);
            }
        }

        std::size_t crt_pos = tmp_strg[(std::size_t)(-1)];
        while (crt_pos != crrnt_pos) {
            std::size_t ncrt_pos = tmp_strg[crt_pos];
            std::size_t crt_mv;

            if (ncrt_pos == crt_pos+mz_w)
                crt_mv = 0;
            if (ncrt_pos == crt_pos+1)
                crt_mv = 1;
            if (crt_pos == ncrt_pos+mz_w)
                crt_mv = 2;
            if (crt_pos == ncrt_pos+1)
                crt_mv = 3;

            std::size_t crt_x = crt_pos % mz_w;
            std::size_t crt_y = crt_pos / mz_w;

            std::size_t brk_wall;
            switch (crt_mv) {
                case 0:
                    brk_wall = (crt_y+1)*(mz_w-1) + crt_y*mz_w + crt_x;
                    break;
                case 1:
                    brk_wall = crt_y*(2*mz_w-1) + crt_x;
                    break;
                case 2:
                    brk_wall = crt_y*(mz_w-1) + (crt_y-1)*mz_w + crt_x;
                    break;
                case 3:
                    brk_wall = crt_y*(2*mz_w-1) + crt_x - 1;
                    break;
            }

            setcellon(partof_mz, crt_pos);
            cells_left--;
            setcellon(mz, brk_wall);
            crt_pos = ncrt_pos;
        }
    }
}

