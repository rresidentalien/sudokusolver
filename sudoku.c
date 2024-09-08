#include <stdio.h>
#include "functions.h"

int unsolved = 81;
int SIZE_ROWS = 9;
int SIZE_COLUMNS = 9;

int main() {
    int **puzzle, **puzzle_copy;
    int i = 0;
    Cell ***cell, ***cell_copy;

    puzzle = createPuzzle();
    puzzle_copy = createPuzzle();

    cell = setUpPuzzle(puzzle);
    cell_copy = setUpPuzzle(puzzle_copy);

    printPuzzle(cell, cell);
    printf("\n\n");

    do {
        i++;
        checkPuzzle(cell);
    } while (unsolved >= 1 && i < 100);


    printPuzzle(cell, cell_copy);
    printf("Iterations = %d\n", i);

    return 0;
}
