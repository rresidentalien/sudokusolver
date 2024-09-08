#include <stdio.h>
#include "functions.h"

int unsolved = 81;
int SIZE_ROWS = 9;
int SIZE_COLUMNS = 9;

int main() {
    int **puzzle;
    Sudoku *sudoku;

    puzzle = createPuzzle();

    sudoku = setUpPuzzle(puzzle);

    printPuzzle(sudoku->cells);
    printf("\n\n");

    do {
        checkPuzzle(sudoku->cells, sudoku->squares);
    }while (unsolved >= 1);

    printPuzzle(sudoku->cells);

    return 0;
}