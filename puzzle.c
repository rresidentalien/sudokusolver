#include <stdio.h>
#include <stdlib.h>
#include "puzzle.h"

int **createPuzzle() {
    int **puzzle;
    int i, j;
    int array[9][9];

    FILE *puzzletxt = fopen("puzzle.txt", "r");
    if (puzzletxt == NULL) {
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < 9; ++i) {
        for (j = 0; j < 9; ++j) {
            fscanf(puzzletxt, "%d", &array[i][j]);
        }
    }

    fclose(puzzletxt);

    puzzle = (int**)calloc(9, sizeof(int*));
    for (i = 0; i < 9; ++i) {
        puzzle[i] = (int*)calloc(9, sizeof(int));
        for (j = 0; j < 9; ++j) {
            puzzle[i][j] = array[i][j];
        }
    }

    return puzzle;
}



void printPuzzle(int **puzzle) {
    int i, j;

    printf("-------------------------------\n");
    for (i = 0; i < 9; ++i) {
        printf("|");
        for (j = 0; j < 9; ++j) {
            printf(" %d ", puzzle[i][j]);
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