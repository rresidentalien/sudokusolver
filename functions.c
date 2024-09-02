#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

/*function that allocates space for the puzzle and fills out each cell with information (number, row, column), sets number of
solvable values to 9 and changes all numbers 1 through 9 to possible
if a cell already has a number in it (other than 0), its solvable count is changed to 0, number of unsolved cells is decremented
and function updateSudoku is called*/
Cell ***setUpPuzzle(int **puzzle) {
    Cell ***cell;
    int i, j, k;

    cell = (Cell***)calloc(9, sizeof(Cell**));

    for (i = 0; i < SIZE_ROWS; ++i) {
        cell[i] = (Cell**)calloc(9, sizeof(Cell*));

        for (j = 0; j < SIZE_COLUMNS; ++j) {
            cell[i][j] = (Cell*)calloc(9, sizeof(Cell));

            cell[i][j]->number = puzzle[i][j];
            cell[i][j]->row = i;
            cell[i][j]->column = j;
            cell[i][j]->solvable = 9;

            for (k = 0; k < SIZE_ROWS; ++k) {
                cell[i][j]->possible[k] = 0;
            }
        }
    }

    for (i = 0; i < SIZE_ROWS; ++i) {
        for (j = 0; j < SIZE_COLUMNS; ++j) {
            if (cell[i][j]->number != 0) {
                cell[i][j]->solvable = 0; //it already has a number in that place, so it does not need to be solved
                updateSudoku(cell, i, j);
                --unsolved;
            }
        }
    }

    return cell;
}


/*function that will update possibility of a number being in a certain spot.
for every cell of the column/row, if a number can't be put in the cell, decrement solvable*/
int updateSudoku(Cell ***cell, int row, int column) {
    int i;
    int number = cell[row][column]->number;

    for (i = 0; i < SIZE_ROWS; ++i) {
        if (cell[i][column]->possible[number - 1] == 0) {
            --cell[i][column]->solvable;
        }
        cell[i][column]->possible[number - 1] = 1;
    }

    for (i = 0; i < SIZE_COLUMNS; ++i) {
        if (cell[row][i]->possible[number - 1] == 0) {
            --cell[row][i]->solvable;
        }
        cell[row][i]->possible[number - 1] = 1;
    }

    return 1;
}

/*if a number 1 through 9 is possible to be put in a cell, it is put in that cell, solvable is changed to 0 (to indicate
no possible solutions left) and unsolved is decremented*/
void solveCell(Cell *cell) {
    int i;
    for (i = 0; i < SIZE_ROWS; ++i) {
        if (cell->possible[i] == 0) {
            cell->number = i + 1;
            cell->solvable = 0;
            --unsolved;
        }
    }
}

/*if a cell can only have one number be put into it, solveCell and updateSudoku are callled*/
int checkPuzzle(Cell ***cell) {
    int i, j;

    for (i = 0; i < SIZE_ROWS; ++i) {
        for (j = 0; j < SIZE_COLUMNS; ++j) {
            if (cell[i][j]->solvable == 1) {
                solveCell(cell[i][j]);
                updateSudoku(cell, i, j);
            }
        }
    }
    return 1;
}


//reads the puzzle from puzzle.txt and returns it as a dynamically allocated 2d array
int **createPuzzle() {
    int **puzzle;
    int i, j;
    int array[9][9];

    FILE *puzzletxt = fopen("puzzle.txt", "r");
    if (puzzletxt == NULL) {
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < SIZE_ROWS; ++i) {
        for (j = 0; j < SIZE_COLUMNS; ++j) {
            fscanf(puzzletxt, "%d", &array[i][j]);
        }
    }

    fclose(puzzletxt);

    puzzle = (int**)calloc(9, sizeof(int*));
    for (i = 0; i < SIZE_ROWS; ++i) {
        puzzle[i] = (int*)calloc(9, sizeof(int));
        for (j = 0; j < SIZE_COLUMNS; ++j) {
            puzzle[i][j] = array[i][j];
        }
    }

    return puzzle;
}


//prints the puzzle into the terminal with some simple formatting
void printPuzzle(Cell ***puzzle) {
    int i, j;

    printf("-------------------------------\n");
    for (i = 0; i < SIZE_ROWS; ++i) {
        printf("|");
        for (j = 0; j < SIZE_COLUMNS; ++j) {
            printf(" %d ", puzzle[i][j]->number);
            if (((j + 1) % 3) == 0) {
                printf("|");
            }
        }
        printf("\n");
        if (((i + 1) % 3) == 0) {
            printf("-------------------------------\n");
        }
    }
}