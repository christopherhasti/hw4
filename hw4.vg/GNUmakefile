prog = wam
CC = gcc
CXX = g++

# Compiler flags (-g for debugging/valgrind, -pthread for threading)
CFLAGS = -g -Wall -pthread
CXXFLAGS = -g -Wall -pthread

# Linker flags
LDFLAGS = -pthread -lX11 -lfltk

# All object files needed for the final executable
# (Ensure deq.c is in your folder so deq.o can be built)
OBJS = main.o mole.o lawn.o lawnimp.o threads.o mtq.o deq.o

# Default target
all: $(prog)

# Link the executable using g++
$(prog): $(OBJS)
	$(CXX) $(OBJS) -o $(prog) $(LDFLAGS)

# Rule for compiling .c files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule for compiling .cc files
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(prog) $(OBJS)