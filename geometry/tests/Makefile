# Define the compiler and the linker. The linker must be defined since
# the implicit rule for linking uses CC as the linker. g++ can be
# changed to clang++.
CXX = clang++
CC  = clang++

# Define preprocessor, compiler, and linker flags. Uncomment the # lines
# if you use clang++ and wish to use libc++ instead of GNU's libstdc++.
CXXFLAGS =  -g -O2 -Wall -W
CXXFLAGS += -Wmissing-braces -Wparentheses -Wold-style-cast 
CXXFLAGS += -std=c++11 
LDFLAGS =   -g -lpython2.7 
CPPFLAGS = -std=c++11
#CPPFLAGS =  -stdlib=libc++
#CXXFLAGS += -stdlib=libc++
#LDFLAGS +=  -stdlib=libc++

# Targets
PROGS = quickhull_test closest_pair_test intersection_test triangulation_test test_random

all: $(PROGS)

# Targets rely on implicit rules for compiling and linking
quickhull_test: quickhull_test.o
closest_pair_test: closest_pair_test.o
intersection_test: intersection_test.o
triangulation_test: triangulation_test.o
test_random: test_random.o

# Phony targets
.PHONY: all clean

# Standard clean
clean:
	rm -f *.o $(PROGS)

# Custom clean
custom_clean:
	rm -f *.d
	rm -f *.d.*

# Generate dependencies in *.d files
%.d: %.cc
	@set -e; rm -f $@; \
         $(CPP) -MM $(CPPFLAGS) $< > $@.$$$$; \
         sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
         rm -f $@.$$$$

# Include the *.d files
SRC = $(wildcard *.cc)
include $(SRC:.cc=.d)
