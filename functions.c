#include <stdio.h>
#include <stdlib.h>
#include "functions.h"


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