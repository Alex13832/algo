# Define the compiler and the linker. The linker must be defined since
# the implicit rule for linking uses CC as the linker. g++ can be
# changed to clang++.
CXX = clang++
CC  = clang++

# Define preprocessor, compiler, and linker flags. Uncomment the # lines
# if you use clang++ and wish to use libc++ instead of GNU's libstdc++.
CXXFLAGS =  -g -O2 -Wall -W -pedantic-errors
CXXFLAGS += -Wmissing-braces -Wparentheses -Wold-style-cast 
CXXFLAGS += -std=c++11 
LDFLAGS =   -g -lpython2.7 
CPPFLAGS = -std=c++11
#CPPFLAGS =  -stdlib=libc++
#CXXFLAGS += -stdlib=libc++
#LDFLAGS +=  -stdlib=libc++

# Targets
PROGS = test_bfs test_bellman_ford test_dijkstra test_prim test_kosaraju test_floyd_warshall

all: $(PROGS)

# Targets rely on implicit rules for compiling and linking
test_bfs: test_bfs.o
test_bellman_ford: test_bellman_ford.o
test_dijkstra: test_dijkstra.o
test_prim: test_prim.o
test_kosaraju: test_kosaraju.o
test_floyd_warshall: test_floyd_warshall.o

# Phony targets
.PHONY: all clean

# Standard clean
clean:
	rm -f *.o $(PROGS)

# Generate dependencies in *.d files
%.d: %.cc
	@set -e; rm -f $@; \
         $(CPP) -MM $(CPPFLAGS) $< > $@.$$$$; \
         sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
         rm -f $@.$$$$

# Include the *.d files
SRC = $(wildcard *.cc)
include $(SRC:.cc=.d)
