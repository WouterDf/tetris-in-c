#include "matrix.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

Matrix*
matrixMake( const int rows, const int cols )
{
    Matrix* matrix = malloc( sizeof (Matrix) );
    int* content = malloc( rows * cols * sizeof(int) );
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->content = content;
    return matrix;
}

int
matrixGet( const Matrix* matrix, const int row, const int col )
{
    const int idx = row * matrix->cols + col;
    return matrix->content[idx];
}

void matrixSet( const Matrix *matrix, const int row, const int col, const int value )
{
    if (row >= matrix->rows || row < 0 || col >= matrix->cols || col < 0)
    {
        printf( "Attempted to set out-of-bounds!" );
        return;
    }
    const int idx = row * matrix->cols + col;
    matrix->content[idx] = value;
}

void matrixSets( const Matrix *matrix, ... )
{
    va_list args;
    va_start( args, matrix->rows * matrix->cols );
    for( int i = 0; i < matrix->rows; i++ )
    {
        for( int j = 0; j < matrix->cols; j++ )
        {
            matrixSet( matrix, i,
                j ,
                va_arg( args, int )  );
        }
    }
    va_end( args );
}

void
matrixFree( Matrix* matrix )
{
    free(matrix->content);
    free(matrix);
}

