#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int inputStrictPositiveInt(char s[]){
    int n;
    n=0;
    do{
        printf("\n%s: ", s);
        scanf(" %d", &n);
    }while(n<=0);
    return n;
}

float** inputMatrix(int m, int n){
    float** matrix = (float**)calloc(m,sizeof(float*));

    for(int i = 0; i<m; i++){
        matrix[i] = (float*)calloc(n, sizeof(float));
        for(int j = 0; j<n; j++){
            printf("a[%d][%d]: ",i+1,j+1);
            scanf(" %f", &matrix[i][j]);
        }
    }
    return matrix;
}

//TO-DO: stampare i numeri con la virgola come frazione di interi
void printMatrix(float** matrix, int m, int n){
    for(int i = 0; i<m; i++){
        for(int j = 0; j<n; j++){
            if(fabs(matrix[i][j] - (int)matrix[i][j])<0.000001f){
                printf("%d ", (int)matrix[i][j]);
            }
            else printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }
}

//Controlla se la matrice è a gradini
int isEchelonForm(float** matrix, int m, int n){
    int previous = -1;
    for(int i = 0; i<m; i++){
        for(int j = 0; j<n; j++){
            if(matrix[i][j]!=0){
                if(j>previous){
                    previous = j;
                    break;
                }
                else return 0;
            }
        }
    }
    return 1;
}

//Non usato (OP1 del Teorema di Gauss-Jordan)
//TO-DO: scambiare le righe usando gli indirizzi invece di scambiare i valori
void swapRows(float** matrix, int col, int r1, int r2){
    float* temp = (float*)calloc(col, sizeof(float));
    for(int i = 0; i<col; i++) temp[i] = matrix[r1][i];
    for(int i = 0; i<col; i++) matrix[r1][i] = matrix[r2][i];
    for(int i = 0; i<col; i++) matrix[r2][i] = temp[i];
}

//Non usato (OP2 del Teorema di Gauss-Jordan)
void multiplyRow(float** matrix, int r, int col, float lambda){
    for(int i = 0; i < col; i++) matrix[r][i]*=lambda;
}

//Usato (OP3 del Teorema di Gauss-Jordan)
void linCombRow(float** matrix, int m, int n, int r1, int r2, float lambda){
    for(int j = 0; j < n; j++){
        matrix[r1][j] += (lambda*matrix[r2][j]);
    }
}

void gaussMatrixReduction(float** matrix, int m, int n){
    int current_row = 0;
    int pivot = 0;
    while(!isEchelonForm(matrix, m, n)){
        for(int c = 0; c<n; c++){
            if(matrix[current_row][c]!=0){
                pivot = c;
                break;
            }
        }
        for(int r = current_row+1; r < m; r++){
            float e_to_del = matrix[r][pivot];
            float lambda = -e_to_del/matrix[current_row][pivot];
            linCombRow(matrix, m, n, r, current_row, lambda);
        }
        current_row += 1;
    }
}

//TO-DO: Calcolo determinante, matrice inversa, rango, sistemi lineari

int main(){
    int m, n;

    m = inputStrictPositiveInt("Righe matrice");
    n = inputStrictPositiveInt("Colonne matrice");
    
    float** matrix = inputMatrix(m, n);

    //Prima della riduzione di Gauss
    if(isEchelonForm(matrix, m, n)){
        printf("\nMatrice ridotta a gradini!");
    }
    else printf("\nMatrice non ridotta a gradini!");
    printf("\n");
    printMatrix(matrix, m, n);

    gaussMatrixReduction(matrix, m, n);

    //Dopo la riduzione di Gauss
    if(isEchelonForm(matrix, m, n)){
        printf("\nMatrice ridotta a gradini!");
    }
    else printf("\nMatrice non ridotta a gradini!");
    printf("\n");
    printMatrix(matrix, m, n);

    return 0;
}