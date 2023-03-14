#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"


int **getMatrix(int row, int column);
void printMatrix(int **matrix, int row, int column);
void printVector(int* vector);

int main() {
    int row = 4;
    int column = 4;
    int **matrix = getMatrix(row, column);
    printMatrix(matrix, row, column);

    printf("det new m = %d\n", det(matrix, row, column));


    return 0;
}

int **getMatrix(int row, int column) {
    int **matrix = (int**) calloc(row, sizeof(int*));

    for (int i = 0; i < row; i++) {
        matrix[i] = (int*) calloc(column, sizeof(int));
    }

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            matrix[i][j] = rand() % 10;
        }
    }

    return matrix;
}

void printMatrix(int **matrix, int row, int column) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void printVector(int* vector, int size_vector) {
    for (int i = 0; i < size_vector; i++) {
        printf("%d ", *(vector + i));
    }
    printf("\n");
}
