PROJ = mazer
IDIR =../include
CC = g++
CXXFLAGS = -I$(IDIR)

ODIR = obj

_DEPS = maze_def.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = genmaze.o maze_func.o kruskal.o dfs.o recurse_div.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

BDIR = ../bin

DIRS = $(ODIR) $(BDIR)

$(shell mkdir -p $(DIRS))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CXXFLAGS)

$(PROJ): $(OBJ)
	$(CC) -o $(BDIR)/$@ $^ $(CXXFLAGS)

.PHONY: clean

clean:
	rm -rf $(ODIR) $(BDIR) $(IDIR)/*~
