#include <stdio.h>
#include "functions.h"

int main() {
    int **puzzle;
    Square ***sudoku;

    puzzle = createPuzzle();
    setUpPuzzle();

    printPuzzle(puzzle);

    return 0;
}