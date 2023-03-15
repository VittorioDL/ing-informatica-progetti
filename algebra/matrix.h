#include <math.h>

float detSairus(float A[3][3]);
float** dot(float** A, int a_row, int a_column, float** B, int b_row, int b_column);
float **getCompl(float **matrix, int row, int column);
float det(float **matrix, int row, int column);
int getRk(float **matrix, int row, int column);
float** traspose(float **matrix, int row, int column);
float** getInv(float **matrix, int row, int column);
float **getMatrix(int row, int column);
float** getNullMatrix(int row, int column);
void printMatrix(float **matrix, int row, int column);
float** solveSystem(float **incomplete_matrix, int row, int column, float** b);


float** getNullMatrix(int row, int column) {
    float** matrix = (float**) calloc(row, sizeof(float**));
    for (int i = 0; i < row; ++i) {
        matrix[i] = (float*) calloc(column, sizeof(float));
    }

    return matrix;
}

float detSairus(float **A) {
    return A[0][0] * A[1][1] * A[2][2] + A[0][1] * A[1][2] * A[2][0] + A[0][2] * A[1][0] * A[2][1]
    - (A[0][1] * A[1][0] * A[2][2]) - (A[0][0] * A[1][2] * A[2][1]) - (A[0][2] * A[1][1] * A[2][0]);
}


float **getMatrix(int row, int column) {
    float **matrix = (float**) calloc(row, sizeof(float*));

    for (int i = 0; i < row; i++) {
        matrix[i] = (float*) calloc(column, sizeof(float));
    }

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            matrix[i][j] = rand() % 10;
        }
    }

    return matrix;
}

float **getCompl(float **matrix, int row, int column, int pos_i, int pos_j) {
    int size_new_m = (row - 1) * (column - 1);
    float **new_matrix = (float**) calloc(row, sizeof(float*));
    float *elements = (float*) calloc(size_new_m, sizeof(float));
    int count = 0;

    for (int i = 0; i < row - 1; ++i) {
        new_matrix[i] = (float*) calloc(column, sizeof(float));
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

   int index = 0;
   for (int i = 0; i < sqrt(size_new_m); ++i) {
       for (int j = 0; j < sqrt(size_new_m); ++j) {
           new_matrix[i][j] = elements[index];
           ++index;
       }
   }

    return new_matrix;

}

float det(float** matrix, int row, int column) {
    if (row == 3) {
        return detSairus(matrix);
    } else if(row == 1) {
        return matrix[0][0];
    } else if(row == 2) {
        return matrix[0][0] * matrix[1][1] - (matrix[0][1] * matrix[1][0]);
    } else {
        float det_m = 0;
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

int getRk(float **matrix, int row, int column) {
    return 0;
}

float** traspose(float **matrix, int row, int column) {
    float** new_matrix = getNullMatrix(column, row);
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            new_matrix[j][i] = matrix[i][j];
        }
    }

    return new_matrix;
}

float** getInv(float** matrix, int row, int column) {
    int detA = det(matrix, row, column);
    float** inv = getNullMatrix(row, column);

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            inv[i][j] = pow((-1), i + j) * det(getCompl(matrix, row, column, i, j), row - 1, column - 1);
        }
    }

    float** trasposed_inv = traspose(inv, row, column);
    
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            trasposed_inv[i][j] = trasposed_inv[i][j] / detA;
        }
    }
    

    return trasposed_inv;
}

void printMatrix(float **matrix, int row, int column) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }
}

float** dot(float** A, int a_row, int a_column, float** B, int b_row, int b_column) {
    float** AB = getNullMatrix(a_row, b_column);
    int j_es = 0;

    for (int i = 0; i < a_row; ++i) {
        int ij = 0;
        for (int j = 0; j < b_column; ++j) {
            ij += A[i][j] * B[j][i]; 
        }

        AB[i][j_es] = ij;
        if (j_es == b_column - 1) {
            j_es = 0;
        } else {
            j_es++;
        }
    }

    return AB;
}

float** solveSystem(float **incomplete_matrix, int row, int column, float** b) {
    float **inverse = getInv(incomplete_matrix, row, column);

    return dot(incomplete_matrix, row, column, b, row, 1);
}
