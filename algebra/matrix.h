#include <math.h>

int detSairus(int A[3][3]);
int **getCompl(int **matrix, int row, int column);
int det(int **matrix, int row, int column);

int detSairus(int **A) {
    return A[0][0] * A[1][1] * A[2][2] + A[0][1] * A[1][2] * A[2][0] + A[0][2] * A[1][0] * A[2][1]
    - (A[0][1] * A[1][0] * A[2][2]) - (A[0][0] * A[1][2] * A[2][1]) - (A[0][2] * A[1][1] * A[2][0]);
}

int nRow(int **matrix) {
    return sizeof(**matrix);
}

int **getCompl(int **matrix, int row, int column, int pos_i, int pos_j) {
    int size_new_m = (row - 1) * (column - 1);
    int **new_matrix = (int**) calloc(row, sizeof(int*));
    int *elements = (int*) calloc(size_new_m, sizeof(int));
    int count = 0;

    for (int i = 0; i < row - 1; ++i) {
        new_matrix[i] = (int*) calloc(column, sizeof(int));
    }

    for (int i = 0; i < row; ++i) {
        if (i == pos_i) {
            continue;
        }
        for (int j = 0; j < column; ++j) {
            if (j == pos_j) {
                continue;
            } else {
                *(elements + count) = matrix[i][j];
                count++;
            }
        }
    }

    /*
    for (int i = 0; i < size_new_m; ++i) {
        printf("%d\n", elements[i]);
    }
    */

   int index = 0;
   for (int i = 0; i < sqrt(size_new_m); ++i) {
       for (int j = 0; j < sqrt(size_new_m); ++j) {
           new_matrix[i][j] = elements[index];
           ++index;
       }
   }

    return new_matrix;

}

int det(int** matrix, int row, int column) {
    if (row == 3) {
        return detSairus(matrix);
    } else {
        int det_m = 0;
        bool sign = true;
        int i = 0;
        for (int j = 0; j < column; ++j) {
            if (sign) {
                det_m += matrix[i][j] * det(getCompl(matrix, row, column, i, j), row - 1, column - 1);
                sign = false;
            } else {
                det_m -= matrix[i][j] * det(getCompl(matrix, row, column, i, j), row - 1, column - 1);
                sign = true;
            }
        }

        return det_m;
    }
}
