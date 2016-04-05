# the compiler: gcc for C program, define as g++ for C++
CC = cc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -std=c11 -g -Wall -lm

# the build target executable:
#TARGET = tests graph_tests

#all: $(TARGET)
all: tests graph_tests data_structures_test

tests: tests.o
graph_tests: graph_tests.o
data_structures_test: data_structures_test.o

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	$(RM) $(TARGET)
