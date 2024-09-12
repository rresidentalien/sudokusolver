#include <stdio.h>
#include "functions.h"

int unsolved = 81;
int SIZE_ROWS = 9;
int SIZE_COLUMNS = 9;

int main() {

    int progress;
    int **puzzle;
    Sudoku *sudoku, *sudoku_unsolved;

    puzzle = createPuzzle();

    sudoku = setUpPuzzle(puzzle);
  
    printPuzzle(sudoku->cells);
    

    while (unsolved > 0)
    {
        progress = checkPuzzle(sudoku->cells, sudoku->squares);

        if (progress == 0)
        {
            printf("\nFailed to solve the puzzle!\n\n");
            break;
        }
    }

    printf("\nFinished puzzle:\n");
    printPuzzle(sudoku->cells);

    return 0;
}