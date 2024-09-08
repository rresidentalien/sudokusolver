#include <stdio.h>
#include "functions.h"

int unsolved = 81;
int SIZE_ROWS = 9;
int SIZE_COLUMNS = 9;

int main() {

    int i = 0;
    int **puzzle;
    Sudoku *sudoku, *sudoku_copy;

    puzzle = createPuzzle();

    sudoku = setUpPuzzle(puzzle);
    sudoku_copy = setUpPuzzle(puzzle);
  
    printPuzzle(sudoku->cells, sudoku->cells);
    printf("\n\n");

    do {
        i++;
        checkPuzzle(sudoku->cells, sudoku->squares);
    }while (unsolved >= 1 && i < 100);

    printPuzzle(sudoku->cells, sudoku_copy->cells);
    printf("Iterations = %d\n", i);

    return 0;
}