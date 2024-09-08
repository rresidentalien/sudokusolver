// puzzle.h
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

extern int unsolved;
extern int SIZE_ROWS;
extern int SIZE_COLUMNS;

typedef struct Sudoku {
    struct Cell ***cells;
    struct Square **squares;
} Sudoku;

typedef struct Square {
    struct Cell **cells;
    int numbers;
    int possible[9];
    int solvable;
    struct Square *next;
} Square;

typedef struct Cell {
    int number;
    int possible[9]; /*9 numbers, either 0 or 1, indicating whether a certain number (9-1) can be put in that cell
    0 = can be that number      1 = can't be that number
    9 8 7 6 5 4 3 2 1
    0 1 1 1 1 0 1 1 0   this sequence would mean that the number can be 9, 4 or 1*/
    int solvable; //count of possible numbers that can be placed in a cell
    Square *square;
    int row;
    int column;
} Cell;

Square **createSquares();
int updateSquares(Cell ***, int, int);
int squareSingles(Cell ***, Square **);
int updateSudoku(Cell ***, int, int);
Sudoku *setUpPuzzle(int **);
Sudoku *createSudoku(Cell ***, Square **);
void solveCell(Cell *);
int checkPuzzle(Cell ***, Square **);
int **createPuzzle();
void printPuzzle(Cell ***, Cell ***);

#endif // FUNCTIONS_H
