#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TCell{
    struct TCell *right, *bottom;
    int line, column;
    float value;
}TCell;

typedef struct{
    int lineSize, columnSize; 
    TCell *start, *endLine, *endColumn;
}TMatrix;

int Insert(TMatrix *mat, int line, int column, float value);
void PrintMatrix(TMatrix *A);
void DeleteMatrix(TMatrix *A);

TMatrix *InitializeMatrix(int lines, int columns);
TMatrix *ReadMatrix(TMatrix *A);
TMatrix *SumMatrix(TMatrix *A, TMatrix *B);
TMatrix *MultipliesMatrix(TMatrix *A, TMatrix *B);

float returnCellValue(TMatrix *mat, int line, int column);
