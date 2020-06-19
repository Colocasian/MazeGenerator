#include <random>
#include <stack>

#include <MazeGenerator/maze_def.h>

void recurse_div_gen(char *mz, const int width, const int height, const int &seed) {
    int mzwidth = (width << 1) - 1;
    int wcount = (width-1)*height + width*(height-1);

    for (int i = 0; i < (wcount + BSZ - 1) / BSZ; i++)
        mz[i] = (char)(-1);

    std::mt19937 mt(seed);
    std::stack<int> xy;

    xy.push(0);
    xy.push(0);
    xy.push(width-2);
    xy.push(height-2);
    int x1, y1, x2, y2;

    while (!xy.empty()) {
        y2 = xy.top();
        xy.pop();
        x2 = xy.top();
        xy.pop();
        y1 = xy.top();
        xy.pop();
        x1 = xy.top();
        xy.pop();

        if (x1 > x2 || y1 > y2)
            continue;

        int x = (std::uniform_int_distribution<int>(x1, x2))(mt);
        int y = (std::uniform_int_distribution<int>(y1, y2))(mt);

        xy.push(x1);
        xy.push(y1);
        xy.push(x-1);
        xy.push(y-1);

        xy.push(x1);
        xy.push(y+1);
        xy.push(x-1);
        xy.push(y2);

        xy.push(x+1);
        xy.push(y1);
        xy.push(x2);
        xy.push(y-1);

        xy.push(x+1);
        xy.push(y+1);
        xy.push(x2);
        xy.push(y2);

        unsigned char r = (std::uniform_int_distribution<unsigned char>((char)0, (char)3))(mt);

        int l1 = x1 << 1;
        int l2 = (x2 << 1) + 2;
        int t1 = (y << 1) | 1;
        for (int i = l1; i <= l2; i += 2)
            setcelloff(mz, (mzwidth * t1 + i) >> 1);

        l1 = (y1 << 1);
        l2 = (y2 << 1) + 2;
        t1 = (x << 1) | 1;
        for (int i = l1; i <= l2; i += 2)
            setcelloff(mz, (mzwidth * i + t1) >> 1);

        int hx, hy;
        if (r != (char)0) {
            hx = x;
            hy = (std::uniform_int_distribution<int>(y, y2))(mt);

            hx = (hx << 1) | 1;
            hy = (hy << 1) | 1;
            setcellon(mz, (mzwidth * (hy+1) + hx) >> 1);
        }
        if (r != (char)1) {
            hx = (std::uniform_int_distribution<int>(x, x2))(mt);
            hy = y;

            hx = (hx << 1) | 1;
            hy = (hy << 1) | 1;
            setcellon(mz, (mzwidth * hy + hx + 1) >> 1);
        }
        if (r != (char)2) {
            hx = x;
            hy = (std::uniform_int_distribution<int>(y1, y))(mt);

            hx = (hx << 1) | 1;
            hy = (hy << 1) | 1;
            setcellon(mz, (mzwidth * (hy-1) + hx) >> 1);
        }
        if (r != (char)3) {
            hx = (std::uniform_int_distribution<int>(x1, x))(mt);
            hy = y;

            hx = (hx << 1) | 1;
            hy = (hy << 1) | 1;
            setcellon(mz, (mzwidth * hy + hx - 1) >> 1);
        }
    }
}
