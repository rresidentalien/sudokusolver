// puzzle.h
#ifndef PUZZLE_H
#define PUZZLE_H

typedef struct box {
    
} Box;

typedef struct square {
    int number;
    char possible; /*9 characters, either 0 or 1, indicating whether a certain number (9-1) can be put in that square
    0 = can be that number      1 = can't be that number
    987654321
    011110110   this sequence would mean that a certain position can be 9, 4 or 1*/
    Box *box;
    int row;
    int column;
} Square;


Square ***setUpPuzzle(int **puzzle);
int **createPuzzle();
void printPuzzle(int **puzzle);

#endif // PUZZLE_H