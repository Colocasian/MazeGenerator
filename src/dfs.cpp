#include <algorithm>
#include <random>
#include <stack>

#include <maze_def.h>

void dfs_gen(char *mz, const unsigned int width, const unsigned int height, const unsigned int seed) {
    int ccount = width * height;
    int mzwidth = (width << 1)-1;

    std::mt19937 mt(seed);
    char d[4];
    d[0] = 0;
    d[1] = 1;
    d[2] = 2;
    d[3] = 3;

    std::stack<int> stk;
    int spos = (std::uniform_int_distribution<int>(0, ccount-1))(mt);
    stk.push(spos << 2);

    char visited[(ccount+BSZ-1)/BSZ] = {0};

    while (!stk.empty()) {
        int at = stk.top();
        stk.pop();
        int dir = at & 3;
        at >>= 2;

        if (!getcell(visited, at)) {
            setcellon(visited, at);
            if (at != spos) {
                int x = (at % width) << 1;
                int y = (at / width) << 1;
                switch (dir) {
                    case 0:
                        y--;
                        break;
                    case 1:
                        x--;
                        break;
                    case 2:
                        y++;
                        break;
                    case 3:
                        x++;
                        break;
                }
                setcellon(mz, (mzwidth * y + x) >> 1);
            }

            std::shuffle(d, d+4, mt);

            for (int i = 0; i < 4; i++) {
                if ((d[i] == 0) && (at + width < ccount) && (!getcell(visited, at+width)))
                    stk.push((at + width) << 2);
                else if ((d[i] == 1) && (at % width != (width - 1)) && (!getcell(visited, at+1)))
                    stk.push(((at + 1) << 2) | 1);
                else if ((d[i] == 2) && (at >= width) && (!getcell(visited, at-width)))
                    stk.push(((at - width) << 2) | 2);
                else if ((d[i] == 3) && ((bool)(at % width)) && (!getcell(visited, at-1)))
                    stk.push(((at - 1) << 2) | 3);
            }
        }
    }
}
