#include <algorithm>
#include <cstring>
#include <random>
#include <stack>

#include <MazeGenerator/maze_def.hpp>

void dfs_gen(mbit *mz, const std::size_t width, const std::size_t height,
             const unsigned int seed) {
  std::size_t ccount = width * height;
  int mzwidth = (width << 1) - 1;

  std::memset(mz, 0,
              (((width - 1) * height + width * (height - 1) + BSZ - 1) / BSZ) *
                  sizeof(mbit));

  std::mt19937 mt(seed);
  mbit d[4];
  d[0] = 0;
  d[1] = 1;
  d[2] = 2;
  d[3] = 3;

  std::stack<std::size_t> stk;
  std::size_t spos =
      (std::uniform_int_distribution<std::size_t>(0, ccount - 1))(mt);
  stk.push(spos << 2);

  mbit *visited = new mbit[(ccount + BSZ - 1) / BSZ];
  std::memset(visited, 0, ((ccount + BSZ - 1) / BSZ) * sizeof(mbit));

  while (!stk.empty()) {
    std::size_t at = stk.top();
    stk.pop();
    int dir = at & 3;
    at >>= 2;

    if (!getcell(visited, at)) {
      setcellon(visited, at);
      if (at != spos) {
        std::size_t x = (at % width) << 1;
        std::size_t y = (at / width) << 1;
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

      std::shuffle(d, d + 4, mt);

      for (std::size_t i = 0; i < 4; i++) {
        if ((d[i] == 0) && (at + width < ccount) &&
            (!getcell(visited, at + width)))
          stk.push((at + width) << 2);
        else if ((d[i] == 1) && (at % width != (width - 1)) &&
                 (!getcell(visited, at + 1)))
          stk.push(((at + 1) << 2) | 1);
        else if ((d[i] == 2) && (at >= width) &&
                 (!getcell(visited, at - width)))
          stk.push(((at - width) << 2) | 2);
        else if ((d[i] == 3) && ((bool)(at % width)) &&
                 (!getcell(visited, at - 1)))
          stk.push(((at - 1) << 2) | 3);
      }
    }
  }
}
