#include <stdio.h>
#include <stdlib.h>
#include "sparse_matrix.h"



TMatrix *ReadMatrix(TMatrix *A){

    char fileName[100], line[100];
    printf("\nType the name of the file to be read: ");
    scanf("%s", fileName);

    int lines=0, columns=0;
    int linePos=0, columnPos=0;
    float value=0.0;

    FILE *file;

    file = fopen(fileName, "r");

    if (!file){
        printf("ERROR to open file");
        return NULL;
    }

    fgets(line, 100, file); //read first line that contains m and n
    sscanf(line, "%d %d", &lines, &columns);

    if (lines<=0 || columns<=0){
        printf("Invalid value for line or column. Impossible to creat matrix.");
        return 0;
    }


    A = InitializeMatrix(lines, columns);

    while(fgets(line, 100, file)){
        sscanf(line, "%d %d %f", &linePos, &columnPos, &value);
        if (value){
            Insert(A, linePos, columnPos, value);
        }
    }
    fclose(file);
    return A;

}

TMatrix *InitializeMatrix(int line, int column){
    TMatrix *A;
    int i=0;
    A = (TMatrix*)malloc(sizeof(TMatrix));

    if (!A || line <= 0 || column <= 0){
        printf("\nIncorrect matrix");
        return 0;
    }

    //Initialize all with NULL and the values of line and column
    A->start = NULL;
    A->endLine = NULL;
    A->endColumn = NULL;
    A->lineSize = line;
    A->columnSize = column;

    //Master cell
    TCell *masterCell;
    masterCell = (TCell*)malloc(sizeof(TCell));

    if (!masterCell){
        printf("Error creating master cell");
        return 0;
    }

    masterCell->column = -1;
    masterCell->line = -1;

    //Everything points to the only existent cell
    A->start = masterCell;
    A->endLine = masterCell;
    A->endColumn = masterCell;

    for (i = 1; i <= A->columnSize; i++){ //Initial cells (without any value) of each column
        TCell *firstC;
        firstC = (TCell*)malloc(sizeof(TCell));
        if (firstC){
            // First column
            firstC->column = -1;
            firstC->line = 0;
            A->endColumn->right = firstC;
            A->endColumn = firstC;
            firstC->right = A->start;
            firstC->bottom = firstC;
        }

    }
    for (i = 1; i <= A->lineSize; i++){ //Initial cells (without any value) of each line
        TCell *firstL;
        firstL = (TCell*)malloc(sizeof(TCell));
        if (firstL){
            //First line
            firstL->column = 0;
            firstL->line = -1;
            A->endLine->bottom = firstL;
            A->endLine = firstL;
            firstL->bottom = A->start;
            firstL->right = firstL;
        }
    }

    return A;
}

void PrintMatrix(TMatrix *A){

    if (!A || !A->lineSize || !A->columnSize){
        printf("Incorrect or inexistent matrix");

    }else{
        int i, j;
        TCell *cell;
        cell = A->start->bottom;
        printf("\n\n");
        for (i = 1; i <= A->lineSize; i++){
            for (j = 1; j <= A->columnSize; j++){
                //If cell have connection with line and column, print its value, otherwise print 0.00
                if (cell->right->line == i && cell->right->column == j){
                    cell = cell->right;
                    printf("\t%0.2f", cell->value);
                }
                else{
                    printf("\t0.00");
                }
            }
            printf("\n");
            cell = cell->right->bottom;
        }
    }
}


int Insert(TMatrix *A, int line, int column, float value){
    int i;

    if (!A || A->lineSize <= 0 || A->columnSize <= 0 || !value || line>A->lineSize || column>A->columnSize || !value || line < 1 || column < 1){ \
        return 0;
    }

    TCell *cellAux, *cellLine,  *cellColumn; //temporary cell

    cellAux = (TCell*)malloc(sizeof(TCell));
    if (!cellAux){
        printf("It was not possible to aloc new cell");
        return 0;
    }
    //Initialize all necessary variables
    cellAux->line = line;
    cellAux->column = column;
    cellAux->value = value;
    cellLine = A->start->bottom;
    cellColumn = A->start->right;

   /** Iterate over column **/

    for (i = 0; i < column-1; i++){
        cellColumn = cellColumn->right;
    }

    i=0;
    while (i<line && cellColumn->bottom->column != -1){
        if (cellColumn->bottom->line > cellAux->line){
            cellAux->bottom = cellColumn->bottom;
            cellColumn->bottom = cellAux;
        }
        else{
            cellColumn = cellColumn->bottom;
        }
        i++;
    }
    if (cellColumn->bottom->column == -1){
        cellAux->bottom = cellColumn->bottom;
        cellColumn->bottom = cellAux;
    }

    
   /** Iterate over line **/

    for (i=0; i<line-1; i++){
        cellLine = cellLine->bottom;
    }
    i=0;
    while (i<column && cellLine->right->line != -1){
        if (cellLine->right->column > cellAux->column){
            cellAux->right = cellLine->right;
            cellLine->right = cellAux;
        }
        else{
            cellLine = cellLine->right;
        }
        i++;
    }
    if (cellLine->right->line == -1){
        cellAux->right = cellLine->right;
        cellLine->right = cellAux;
    }
    return 1;
}

void DeleteMatrix(TMatrix *A){
    int j = 1,i = 1;

    TCell *mainCell, *cellAux;

    mainCell = A->start->bottom;
    mainCell = mainCell->right;

    for (i = 1; i <= A->lineSize; i++){
        for (j = 1; j <= A->columnSize; j++){
            if (mainCell->line == i && mainCell->column == j){
                cellAux = mainCell;
                mainCell = mainCell->right;
                free(cellAux);
            }
        }
        mainCell = mainCell->bottom->right;
    }

    mainCell = A->start->right;

    for (i = 0; i < A->lineSize; i++){ //Heads column
        cellAux = mainCell;
        mainCell = mainCell->right;
        free(cellAux);//free up space
    }

    mainCell = A->start->bottom;
    for (i = 0; i < A->columnSize; i++){ //Heas line
        cellAux = mainCell;
        mainCell = mainCell->bottom;
        free(cellAux); //free up space
    }

    mainCell = A->start;
    free(mainCell); //free up space of head

    A->endColumn = A->endLine = A->start = NULL;
    A->lineSize = A->columnSize = 0;
    A = NULL;
}

TMatrix *SumMatrix(TMatrix *A, TMatrix *B){
    int i, j;
    float result;
    TMatrix *C;
    TCell *cellsA, *cellsB;

    if (A->lineSize != B->lineSize || A->columnSize != B->columnSize){
        printf("\nMatrices have different sizes, it is not possible to sum");
        return NULL;
    }

    C = InitializeMatrix(A->lineSize, A->columnSize);

    cellsA = A->start->bottom;
    cellsB = B->start->bottom;
    int lines = A->lineSize;
    int columns = A->columnSize;
    for (i = 1; i <=lines ; i++){
        for (j = 1; j <= columns; j++){
            //If there are values on both cells, sum it up and insert on new matrix
            if (j == cellsA->right->column && j == cellsB->right->column){

                result = cellsA->right->value + cellsB->right->value;

                if (result){
                    Insert(C, i, j, result);
                }

                cellsA = cellsA->right;
                cellsB = cellsB->right;
            }
            //If there is a value only on matrix A, insert this value on the corresponding position
            else if (j == cellsA->right->column){

                Insert(C, i, j, cellsA->right->value);

                cellsA = cellsA->right;
            }
            //If there is a value only on matrix B, insert this value on the corresponding position
            else if (j == cellsB->right->column){

                Insert(C, i, j, cellsB->right->value);

                cellsB = cellsB->right;
            }
        }
        cellsA = cellsA->right->bottom;
        cellsB = cellsB->right->bottom;
    }

    return C;
}

TMatrix *MultipliesMatrix(TMatrix *A, TMatrix *B){
    int i=0, j=0, k=0;
    float total;
    TMatrix *C;

    if (A->columnSize != B->lineSize){
        printf("\nIt was not possible to multiply matrices.\nNumber of columns of A is different from number of lines of B.\n");
        return NULL;
    }

    if (!A || !B || !A->lineSize || !A->columnSize || !B->columnSize){
        return NULL;
    }

    C = InitializeMatrix(A->lineSize, B->columnSize); //C has number of lines of A and number of columns of B

    for (i = 1; i <= A->lineSize; i++){
        for (j = 1; j <= B->columnSize; j++){
            total = 0;
            for (k = 1; k <= A->columnSize; k++){
                total += returnCellValue(A,i,k) * returnCellValue(B,k,j);
            }
            if (total){
                Insert(C,i,j,total);
            }
        }
    }
    return C;
}

float returnCellValue(TMatrix *A, int line, int column){
    TCell *pCell;
    
    pCell = A->start->right;
    
    int i = 0;
    for (i = 0; i < column-1; i++){
        pCell = pCell->right;
    }
    
    pCell = pCell->bottom;
    
    while(pCell->column != -1){
        
        if (pCell->line == line){
            return pCell->value;
        }
        pCell = pCell->bottom;
    }

    return 0;
}
