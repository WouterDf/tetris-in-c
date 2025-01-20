//
// Created by Wouter Deferme on 18/01/2025.
//

#ifndef TETRIS_SHAPE_H
#define TETRIS_SHAPE_H
#include "matrix.h"

/**************************************************************************
** Tetris shapes
**************************************************************************/
typedef int TETRIS_SHAPE;
#define TETRIS_SHAPE_SQUARE 0
#define TETRIS_SHAPE_LONG   1
#define TETRIS_SHAPE_T      2
#define TETRIS_SHAPE_Z      3
#define TETRIS_SHAPE_S      4
#define TETRIS_SHAPE_L      5
#define TETRIS_SHAPE_J      6

/**************************************************************************
** Tetris shape rotations
**************************************************************************/
typedef int TETRIS_ROT;
#define TETRIS_ROT_0        0
#define TETRIS_ROT_90       1
#define TETRIS_ROT_180      2
#define TETRIS_ROT_270      3

/**************************************************************************
** Method prototype
**************************************************************************/
Matrix* getLocalShapeCells( TETRIS_SHAPE tetris_shape, int i, int j, TETRIS_ROT tetris_rot );

/**************************************************************************
** Tetris shape coordinates
**************************************************************************/
#define COORDS_SHAPE_L_ROT_0 \
    i,      j-1,    \
    i,      j,      \
    i,      j+1,    \
    i+1,    j+1

#define COORDS_SHAPE_L_ROT_90 \
    i+1,    j,    \
    i,      j,    \
    i-1,    j,    \
    i-1,    j+1

#define COORDS_SHAPE_L_ROT_180 \
    i,      j+1,    \
    i,      j,      \
    i,      j-1,    \
    i-1,    j-1

#define COORDS_SHAPE_L_ROT_270 \
    i-1,    j,      \
    i,      j,      \
    i+1,    j,      \
    i+1,    j-1

#define COORDS_SHAPE_J_ROT_0 \
    i,      j-1,    \
    i,      j,      \
    i,      j+1,    \
    i-1,    j+1

#define COORDS_SHAPE_J_ROT_90 \
    i+1,    j,      \
    i,      j,      \
    i-1,    j,      \
    i-1,    j-1

#define COORDS_SHAPE_J_ROT_180 \
    i,      j+1,    \
    i,      j,      \
    i,      j-1,    \
    i+1,    j-1

#define COORDS_SHAPE_J_ROT_270\
    i-1,    j,      \
    i,      j,      \
    i+1,    j,      \
    i+1,    j+1

#define COORDS_SHAPE_SQUARE_ROT_0\
    i,      j,      \
    i+1,    j,      \
    i,      j+1,    \
    i+1,    j+1

#define COORDS_SHAPE_S_ROT_0\
    i,      j,      \
    i+1,    j,      \
    i,      j+1,    \
    i-1,    j+1

#define COORDS_SHAPE_S_ROT_90\
    i,      j,      \
    i,      j+1,    \
    i-1,    j,      \
    i-1,    j-1

#define COORDS_SHAPE_S_ROT_180\
    i,      j,      \
    i-1,    j,      \
    i,      j-1,    \
    i+1,    j-1

#define COORDS_SHAPE_S_ROT_270\
    i,      j,      \
    i,      j-1,    \
    i+1,    j,      \
    i+1,    j+1

#define COORDS_SHAPE_Z_ROT_0\
    i,      j,      \
    i+1,    j,      \
    i,      j-1,    \
    i-1,    j-1

#define COORDS_SHAPE_Z_ROT_90\
    i,      j,      \
    i,      j+1,    \
    i+1,    j,      \
    i+1,    j-1

#define COORDS_SHAPE_Z_ROT_180\
    i,      j,      \
    i-1,    j,      \
    i,      j+1,    \
    i+1,    j+1

#define COORDS_SHAPE_Z_ROT_270\
    i,      j,      \
    i,      j-1,    \
    i-1,    j,      \
    i-1,    j+1

#define COORDS_SHAPE_LONG_ROT_0\
    i,      j,      \
    i,      j-1,    \
    i,      j+1,    \
    i,      j+2

#define COORDS_SHAPE_LONG_ROT_90\
    i,      j,      \
    i-1,    j,      \
    i+1,    j,      \
    i+2,    j

#define COORDS_SHAPE_T_ROT_0\
    i,      j,      \
    i,      j-1,    \
    i-1,    j,      \
    i+1,    j

#define COORDS_SHAPE_T_ROT_90\
    i,      j,      \
    i+1,    j,      \
    i,      j+1,    \
    i,      j-1

#define COORDS_SHAPE_T_ROT_180\
    i,      j,      \
    i,      j+1,    \
    i-1,    j,      \
    i+1,    j

#define COORDS_SHAPE_T_ROT_270\
    i,      j,      \
    i-1,    j,      \
    i,      j+1,    \
    i,      j-1

#endif //TETRIS_SHAPE_H
