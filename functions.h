// puzzle.h
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

extern int unsolved;
extern int SIZE_ROWS;
extern int SIZE_COLUMNS;

typedef struct box {
    struct Box *next;
} Box;

typedef struct cell {
    int number;
    int possible[9]; /*9 numbers, either 0 or 1, indicating whether a certain number (9-1) can be put in that cell
    0 = can be that number      1 = can't be that number
    9 8 7 6 5 4 3 2 1
    0 1 1 1 1 0 1 1 0   this sequence would mean that the number can be 9, 4 or 1*/
    int solvable; //count of possible numbers that can be placed in a cell
    Box *box;
    int row;
    int column;
} Cell;

int updateSudoku(Cell ***, int, int);
Cell ***setUpPuzzle(int **);
void solveCell(Cell *);
int checkPuzzle(Cell ***);
int **createPuzzle();
void printPuzzle(Cell ***);

#endif // FUNCTIONS_H