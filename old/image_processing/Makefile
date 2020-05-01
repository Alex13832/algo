# Makefile
CXX ?= g++

CFLAGS  = -std=c11 -g -Wall -lm
CXXFLAGS += -Wall $(shell pkg-config --cflags opencv)
LDFLAGS += $(shell pkg-config --libs --static opencv)
CXXFLAGS += -std=c++11


# Define all objects here
OBJ   = test_image_processing image_processing
OBJS  = $(addsuffix .o,$(OBJ))

all:
	make compile

compile:
	make $(OBJS)
	make fooexe

# Executable file
fooexe: $(OBJS)
	$(CXX) -o fooexe $(OBJS) $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -rf $(OBJS) fooexe *.dSYM
