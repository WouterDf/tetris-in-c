//
// Created by Wouter Deferme on 18/01/2025.
//

#ifndef MATRIX_H
#define MATRIX_H

typedef struct Matrix
{
    int rows;
    int cols;
    int* content;
} Matrix;


Matrix*
matrixMake( int rows, int cols );

int
matrixGet( const Matrix* matrix, int row, int col );

void
matrixSet( const Matrix* matrix, int row, int col, int value );

void
matrixSets( const Matrix* matrix, ...);

void
matrixFree( Matrix* matrix );

#endif //MATRIX_H
