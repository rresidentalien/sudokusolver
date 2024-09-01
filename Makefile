# Define the compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Define the target executable
TARGET = sudoku_solver

# Define the source files
SRCS = sudoku.c functions.c

# Define the object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Rule to link the object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile source files into object files
%.o: %.c functions.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

run: all
	./sudoku.exe