#include <stdio.h>
#include "functions.h"

int unsolved = 81;
int SIZE_ROWS = 9;
int SIZE_COLUMNS = 9;

int main() {
    int **puzzle;
    Cell ***cell;

    puzzle = createPuzzle();

    cell = setUpPuzzle(puzzle);

    printPuzzle(cell);
    printf("\n\n");

    do {
        checkPuzzle(cell);
    }while (unsolved >= 1);

    printPuzzle(cell);

    return 0;
}