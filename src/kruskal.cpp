#include <algorithm>
#include <random>

#include <maze_def.h>

class udfs {
private:
    std::vector<int> p, rank;

    int findset(int i) {
        return (p[i] == i)? i: (p[i] = findset(p[i]));
    }

public:
    udfs(int n) {
        rank.assign(n, 0);
        p.resize(n);
        for (int i = 0; i < n; i++)
            p[i] = i;
    }

    bool sameset(int i, int j) {
        return (findset(i) == findset(j));
    }

    void unionset(int i, int j) {
        if (!sameset(i, j)) {
            int x = p[i], y = p[j];
            if (rank[x] < rank[y])
                p[y] = x;
            else {
                p[x] = y;
                if (rank[x] == rank[y])
                    rank[y]++;
            }
        }
    }
};

void kruskal_gen(char *mz, const unsigned int width, const unsigned int height, const unsigned int seed) {
    int ccount = width*height;
    int wcount = (width-1) * height + width * (height-1);
    int mzwidth = (width << 1) - 1;

    for (int i = 0; i < (wcount + BSZ - 1) / BSZ; i++)
        mz[i] = (char)(0);

    udfs cells(ccount);

    std::mt19937 mt(seed);

    int wlord[wcount];
    for (int i = 0; i < wcount; i++)
        wlord[i] = i;
    std::shuffle(wlord, wlord+wcount, mt);

    int joins = ccount-1;
    for (int i = 0; ((bool)joins) && (i < wcount); i++) {
        int wallno = wlord[i];
        int c1, c2;

        wallno = (wallno << 1)|1;
        if ((wallno / mzwidth) & 1) {
            c1 = wallno - mzwidth;
            c2 = wallno + mzwidth;
        } else {
            c1 = wallno - 1;
            c2 = wallno + 1;
        }
        wallno >>= 1;
        c1 = ((c1 / mzwidth) * width + (c1 % mzwidth)) >> 1;
        c2 = ((c2 / mzwidth) * width + (c2 % mzwidth)) >> 1;

        if (!cells.sameset(c1, c2)) {
            joins--;
            cells.unionset(c1, c2);
            setcellon(mz, wallno);
        }
    }
}

