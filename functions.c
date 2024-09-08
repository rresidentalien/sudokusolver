#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int squareSingles(Cell ***sudoku, Square **squares) {
    int i, j, k;
    int count, temp;

    //loop through squares
    for (i = 0; i < 9; ++i) {
        //loop through possible array
        for (j = 0; j < 9; ++j) {
            count = 0;

            //loop through cells
            for (k = 0; k < 9; ++k) {
                if (squares[i]->cells[k]->number != 0) {
                    continue;
                }

                if (squares[i]->cells[k]->possible[j] == 0) {
                    ++count;
                    temp = k;
                }

                if (count == 2) {
                    break;
                }
            }
            if (count == 1) {
                squares[i]->cells[temp]->number = j + 1;
                --unsolved;
                squares[i]->cells[temp]->solvable = 0;

                updateSudoku(sudoku, squares[i]->cells[temp]->row, squares[i]->cells[temp]->column);
            }
        }
    }
}

Square **createSquares() {
    int i, j;
    Square **squares;
    squares = calloc(9, sizeof(Square*));

    for (i = 0; i < 9; ++i) {
        squares[i] = malloc(sizeof(Square));
        squares[i]->cells = calloc(9, sizeof(Cell*));
        squares[i]->numbers = 0;
        squares[i]->solvable = 9;

        for (j = 0; j < 9; ++j) {
            squares[i]->possible[j] = 0;
        }
    }
    return squares;
}

int updateSquares(Cell ***cell, int row, int column) {
    int i;
    int number = cell[row][column]->number;
    Square *square;
    square = cell[row][column]->square;

    for (i = 0; i < 9; ++i) {
        if (square->cells[i]->possible[number - 1] == 0) {
            --square->cells[i]->solvable;
            square->cells[i]->possible[number - 1] = 1;
        }
    }
}

Sudoku *createSudoku(Cell ***cells, Square **squares) {
    Sudoku *sudoku;
    sudoku = malloc(sizeof(Sudoku));
    sudoku->cells = cells;
    sudoku->squares = squares;

    return sudoku;
}

/*function that allocates space for the puzzle and fills out each cell with information (number, row, column), sets number of
solvable values to 9 and changes all numbers 1 through 9 to possible
if a cell already has a number in it (other than 0), its solvable count is changed to 0, number of unsolved cells is decremented
and function updateSudoku is called*/
Sudoku *setUpPuzzle(int **puzzle) {
    Cell ***cell;
    Square **squares;
    int i, j, k;
    int currentSquare = 0;

    cell = (Cell***)calloc(9, sizeof(Cell**));
    squares = createSquares();

    for (i = 0; i < SIZE_ROWS; ++i) {
        cell[i] = (Cell**)calloc(9, sizeof(Cell*));

        for (j = 0; j < SIZE_COLUMNS; ++j) {
            cell[i][j] = (Cell*)calloc(9, sizeof(Cell));

            cell[i][j]->number = puzzle[i][j];
            cell[i][j]->row = i;
            cell[i][j]->column = j;
            cell[i][j]->solvable = 9;

            squares[currentSquare]->cells[squares[currentSquare]->numbers] = cell[i][j];
            cell[i][j]->square = squares[currentSquare];
            ++squares[currentSquare]->numbers;

            for (k = 0; k < SIZE_ROWS; ++k) {
                cell[i][j]->possible[k] = 0;
            }

            if (j == 2 || j == 5) {
                ++currentSquare;
            }
        }

        currentSquare -= 2;
        if (i == 2) {
            currentSquare = 3;
        }
        if (i == 5) {
            currentSquare = 6;
        }
    }

    for (i = 0; i < SIZE_ROWS; ++i) {
        for (j = 0; j < SIZE_COLUMNS; ++j) {
            if (cell[i][j]->number != 0) {
                cell[i][j]->solvable = 0; //it already has a number in that place, so it does not need to be solved
                updateSudoku(cell, i, j);
                updateSquares(cell, i, j);
                --unsolved;
            }
        }
    }

    return createSudoku(cell, squares);
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

/*if a cell can only have one number be put into it, solveCell and updateSudoku are called*/
int checkPuzzle(Cell ***cell, Square **square) {
    int i, j;

    for (i = 0; i < SIZE_ROWS; ++i) {
        for (j = 0; j < SIZE_COLUMNS; ++j) {
            if (cell[i][j]->solvable == 1) {
                solveCell(cell[i][j]);
                updateSudoku(cell, i, j);
                updateSquares(cell, i, j);
            }
        }
    }
    squareSingles(cell, square);

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
void printPuzzle(Cell ***puzzle, Cell ***compared) {
    int i, j;

    printf("-------------------------------\n");
    for (i = 0; i < SIZE_ROWS; ++i) {
        printf("|");
        for (j = 0; j < SIZE_COLUMNS; ++j) {
            if (puzzle[i][j]->number == compared[i][j]->number) {
                printf(" %d ", puzzle[i][j]->number);
            }
            else {
                printf(" %d*", puzzle[i][j]->number);
            }
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
