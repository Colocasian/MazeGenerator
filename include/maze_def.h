#ifndef COLOC_MAZE_DEFINITIONS
#define COLOC_MAZE_DEFINITIONS
#include <vector>

#define BSZ (8*sizeof(char))

bool getcell(const char* mz, int cno);
void setcellon(char* mz, int cno);
void setcelloff(char* mz, int cno);
void togcell(char* mz, int cno);
void printmaze(const char *mz, int width, int height);

void kruskal_gen(char *mz, const unsigned int width, const unsigned int height, const unsigned int seed);
void dfs_gen(char *mz, const unsigned int width, const unsigned int height, const unsigned int seed);
void recurse_div_gen(char *mz, const int width, const int height, const int &seed);
#endif
