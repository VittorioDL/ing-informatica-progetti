#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BLACK "\x1b[30m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define WHITE "\x1b[37m"
#define RESET "\x1b[m"

int selectDifficulty(){
    int d;
    do{
        printf("\n--------Selezionare difficolta' del campo minato--------\n");
        printf("1: Principiante (9x9)\n");
        printf("2: Intermedio (16x16)\n");
        printf("3: Esperto (30x16)\n");
        printf(">>>: ");
        scanf("%d", &d);
    }while(d<1 || d>3);
    return d;
}

void drawField(int numRows, int numCols, char field[numRows][numCols]){
    printf("\n");
    for(int c = 0; c <= numCols; c++) {
        if(c>=1) printf(" %d",c-1);
        else printf(" ");
    }
    printf("\n");
    for(int r = 0; r < numRows; r++){      
        for(int c = 0; c <= numCols; c++){
            if(c==0) printf("%d ",r);
            else{
                switch(field[r][c-1]){
                    case '1': printf("%s%c %s", BLUE, field[r][c-1], RESET); break;
                    case '2': printf("%s%c %s", GREEN, field[r][c-1], RESET); break;
                    case '3': printf("%s%c %s", RED, field[r][c-1], RESET); break;
                    case '4': printf("%s%c %s", YELLOW, field[r][c-1], RESET); break;
                    case '5': printf("%s%c %s", MAGENTA, field[r][c-1], RESET); break;
                    case '6': printf("%s%c %s", CYAN, field[r][c-1], RESET); break;
                    case '7': printf("%c ", field[r][c-1]); break;
                    case '8': printf( "%c ", field[r][c-1]); break;
                    default: printf("%c ", field[r][c-1]);
                }
            }
        }
        printf("\n");
    }
    printf("\n");
}

int selectCol(int numCols){
    int c;
    do{
        printf("Numero colonna: ");
        scanf("%d",&c);
    }while(c<0||c>numCols);
    return c;
}

int selectRow(int numRows){
    int r;
    do{
        printf("\nNumero riga: ");
        scanf("%d",&r);
    }while(r<0||r>numRows);
    return r;
}

//Non usato (per il momento)
char selectAction(){
    char a;
    do{
        printf("Azione (f: flag, s: scopri): ");
        scanf(" %c",&a);
    }while(!(a=='f' || a=='s'));
    return a;
}

void generateField(int numRows, int numCols, int fieldNum[numRows][numCols], int bombs, int first_r, int first_c){
    int c = 0;
    //Place the bombs randomly
    while(c<bombs){
        int randR, randC;
        randR = rand() % numRows;
        randC = rand() % numCols;
        if(fieldNum[randR][randC]==10 || (randR==first_r && randC==first_c)) c--;
        else fieldNum[randR][randC]=10;
        c++;
    }
    //Calculate number of adjacent bombs
    for(int r = 0; r < numRows; r++) {
        for(int c = 0; c < numCols; c++) {
            if(fieldNum[r][c]!=10){
                int count = 0;
                for(int ri = -1; ri<=1; ri++){
                    for(int ci = -1; ci<=1; ci++){
                        if(ri+r>=0 && ri+r<numRows && ci+c>=0 && ci+c<numCols){
                            if(fieldNum[r+ri][c+ci]==10) count+=1;
                        }
                    }
                }
                fieldNum[r][c]=count;
            }
        }
    }
}

void convertField(int numRows, int numCols, int fieldNum[numRows][numCols], char fieldChar[numRows][numCols]){
    for(int r = 0; r < numRows; r++) {
        for(int c = 0; c < numCols; c++) {
            if(fieldNum[r][c]==9) fieldChar[r][c]='-';
            else if(fieldNum[r][c]<0) fieldChar[r][c]=abs(fieldNum[r][c])+'0';
        }
    }
}

void clearSquares(int numRows, int numCols, int fieldNum[numRows][numCols], int r, int c){
    if(fieldNum[r][c]==0 || fieldNum[r][c]==9){
        for(int ri = -1; ri<=1; ri++){
            for(int ci = -1; ci<=1; ci++){
                if(ri+r>=0 && ri+r<numRows && ci+c>=0 && ci+c<numCols){
                    if(fieldNum[r+ri][c+ci]==0){
                        fieldNum[r+ri][c+ci]=9;
                        clearSquares(numRows, numCols, fieldNum, r+ri, c+ci);
                    }
                    else if(fieldNum[r+ri][c+ci]<=8 && fieldNum[r+ri][c+ci]>=1){
                        fieldNum[r+ri][c+ci]*=-1;
                    }
                }
            }
        }
        // for(int ri = ((r>0)?-1:0); ri<=((r==numRows)?0:1); ri++){
        //     for(int ci = ((c>0)?-1:0); ci<=((c==numCols)?0:1); ci++){
        //         if(fieldNum[r+ri][c+ci]==0){
        //             fieldNum[r+ri][c+ci]=9;
        //             clearSquares(numRows, numCols, fieldNum, r+ri, c+ci);
        //         }
        //         else if(fieldNum[r+ri][c+ci]<=8 && fieldNum[r+ri][c+ci]>=1){
        //             fieldNum[r+ri][c+ci]*=-1;
        //         }
        //     }
        // } 
    }
    else if(fieldNum[r][c]<=8 && fieldNum[r][c]>=1){
        fieldNum[r][c]*=-1;
        
    }
}

int checkWin(int numRows, int numCols, int fieldNum[numRows][numCols]){
    int count = 0;
    for(int i = 0; i < numRows; i++){      
        for(int j = 0; j < numCols; j++){
            if(fieldNum[i][j]==0) return 0;
        }
    }
    return 1;
}

/*TO-DO: Aggiungere la possibilità di flaggare una bomba,
         scoprire celle adiacenti ad una cella flaggata,
         salvare le partite in un file con il punteggio e l'highscore*/  
//TO-DO_Long_term: Implementare una libreria grafica

int main(){
    srand(time(NULL));

    int d,numCols,numRows,bombs;
    
    d = selectDifficulty();

    //Set number of bombs based on difficulty d
    if(d==1) bombs = 10;
    else if(d==2) bombs = 32;
    else bombs = 60;

    //Assign value to numRows and numCols based on difficulty d
    if(d==1){
        numCols=9;
        numRows=9;
    }
    else if (d==2){
        numCols=16;
        numRows=16;
    }
    else{
        numCols=30;
        numRows=16;   
    }
    
    int fieldNum[numRows][numCols];
    char fieldChar[numRows][numCols];
    
    //Inizialize fieldChar with '~'
    for(int i = 0; i < numRows; i++){      
        for(int j = 0; j < numCols; j++){
            fieldChar[i][j] = '~';
            fieldNum[i][j] = 0;
        }
    }
    
    //Print empty field
    drawField(numRows, numCols, fieldChar);

    //Select first square to clear
    int r,c,lost=0;
    r = selectRow(numRows);
    c = selectCol(numCols);

    //Generate field
    generateField(numRows, numCols, fieldNum, bombs, r, c);
    clearSquares(numRows, numCols, fieldNum, r, c);
    convertField(numRows, numCols, fieldNum, fieldChar);
    drawField(numRows,numCols,fieldChar);

    while(!checkWin(numRows, numCols, fieldNum) && !lost){
        r = selectRow(numRows);
        c = selectCol(numCols);
        if(fieldNum[r][c]==10) lost = 1;
        
        clearSquares(numRows, numCols, fieldNum, r, c);
        convertField(numRows, numCols, fieldNum, fieldChar);
        drawField(numRows,numCols,fieldChar);
    }

    if(lost) printf("\nHai perso");
    else printf("\nHai vinto");

    return 0;
}