#include "sparse_matrix.h"

void main(){

    TMatrix *A, *B, *C;

    A = ReadMatrix(A);
    PrintMatrix(A);
    B = ReadMatrix(B);
    PrintMatrix(B);
    
    C = SumMatrix(A, B);
    printf("\nThe result of the sum of the matrices is:");
    PrintMatrix(C);

    DeleteMatrix(B);
    DeleteMatrix(C);

    B = ReadMatrix(B);

    printf("\nA and B:");
    PrintMatrix(A);
    PrintMatrix(B);

    printf("\nThe result of the sum of the matrices is:");
    C = SumMatrix(A,B);
    PrintMatrix(C);

    printf("\nThe result of the product of the matrices is:");
    C = MultipliesMatrix(A,B);
    PrintMatrix(C);


    C = MultipliesMatrix(B, B);
    

    printf("\nA, B and C:");
    PrintMatrix(A);
    PrintMatrix(B);
    PrintMatrix(C);

    DeleteMatrix(A);
    DeleteMatrix(B);
    DeleteMatrix(C);

}
