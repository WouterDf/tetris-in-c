//
// Created by Wouter Deferme on 18/01/2025.
//

#include "tetris_shape.h"
#include "matrix.h"

/*
 * Get the board coordinates of a tetris shape with origin at i, j at a given rotation.
 */
inline Matrix*
getLocalShapeCells( TETRIS_SHAPE tetris_shape, int i, int j, TETRIS_ROT tetris_rot )
{
    Matrix* m = matrixMake( 4, 2 );

    if( tetris_shape == TETRIS_SHAPE_L && tetris_rot == TETRIS_ROT_0 )
    {
        matrixSets( m, COORDS_SHAPE_L_ROT_0 );
    }

    if( tetris_shape == TETRIS_SHAPE_L && tetris_rot == TETRIS_ROT_90 )
    {
        matrixSets( m, COORDS_SHAPE_L_ROT_90 );
    }

    if( tetris_shape == TETRIS_SHAPE_L && tetris_rot == TETRIS_ROT_180 )
    {
        matrixSets( m, COORDS_SHAPE_L_ROT_180 );
    }

    if( tetris_shape == TETRIS_SHAPE_L && tetris_rot == TETRIS_ROT_270 )
    {
        matrixSets( m, COORDS_SHAPE_L_ROT_270 );
    }


    if( tetris_shape == TETRIS_SHAPE_J && tetris_rot == TETRIS_ROT_0 )
    {
        matrixSets( m, COORDS_SHAPE_J_ROT_0);
    }
    if( tetris_shape == TETRIS_SHAPE_J && tetris_rot == TETRIS_ROT_90 )
    {
        matrixSets( m, COORDS_SHAPE_J_ROT_90);
    }
    if( tetris_shape == TETRIS_SHAPE_J && tetris_rot == TETRIS_ROT_180 )
    {
        matrixSets( m, COORDS_SHAPE_J_ROT_180);
    }
    if( tetris_shape == TETRIS_SHAPE_J && tetris_rot == TETRIS_ROT_270 )
    {
        matrixSets( m, COORDS_SHAPE_J_ROT_270);
    }

    if( tetris_shape == TETRIS_SHAPE_SQUARE )
    {
        matrixSets( m, COORDS_SHAPE_SQUARE_ROT_0 );
    }

    if( tetris_shape == TETRIS_SHAPE_S && tetris_rot == TETRIS_ROT_0  )
    {
        matrixSets( m, COORDS_SHAPE_S_ROT_0 );
    }
    if( tetris_shape == TETRIS_SHAPE_S && tetris_rot == TETRIS_ROT_90  )
    {
        matrixSets( m, COORDS_SHAPE_S_ROT_90 );
    }
    if( tetris_shape == TETRIS_SHAPE_S && tetris_rot == TETRIS_ROT_180  )
    {
        matrixSets( m, COORDS_SHAPE_S_ROT_180 );
    }
    if( tetris_shape == TETRIS_SHAPE_S && tetris_rot == TETRIS_ROT_270  )
    {
        matrixSets( m, COORDS_SHAPE_S_ROT_270 );
    }

    if( tetris_shape == TETRIS_SHAPE_Z && tetris_rot == TETRIS_ROT_0   )
    {
        matrixSets( m, COORDS_SHAPE_Z_ROT_0 );
    }
    if( tetris_shape == TETRIS_SHAPE_Z && tetris_rot == TETRIS_ROT_90   )
    {
        matrixSets( m, COORDS_SHAPE_Z_ROT_90 );
    }
    if( tetris_shape == TETRIS_SHAPE_Z && tetris_rot == TETRIS_ROT_180   )
    {
        matrixSets( m, COORDS_SHAPE_Z_ROT_180 );
    }
    if( tetris_shape == TETRIS_SHAPE_Z && tetris_rot == TETRIS_ROT_270   )
    {
        matrixSets( m, COORDS_SHAPE_Z_ROT_270 );
    }

    if( tetris_shape == TETRIS_SHAPE_LONG && tetris_rot == TETRIS_ROT_0 )
    {
        matrixSets( m, COORDS_SHAPE_LONG_ROT_0 );
    }
    if( tetris_shape == TETRIS_SHAPE_LONG && tetris_rot == TETRIS_ROT_90 )
    {
        matrixSets( m, COORDS_SHAPE_LONG_ROT_90 );
    }
    if( tetris_shape == TETRIS_SHAPE_LONG && tetris_rot == TETRIS_ROT_180 )
    {
        matrixSets( m, COORDS_SHAPE_LONG_ROT_0 );
    }
    if( tetris_shape == TETRIS_SHAPE_LONG && tetris_rot == TETRIS_ROT_270 )
    {
        matrixSets( m, COORDS_SHAPE_LONG_ROT_90 );
    }

    if( tetris_shape == TETRIS_SHAPE_T && tetris_rot == TETRIS_ROT_0 )
    {
        matrixSets( m, COORDS_SHAPE_T_ROT_0 );
    }
    if( tetris_shape == TETRIS_SHAPE_T && tetris_rot == TETRIS_ROT_90 )
    {
        matrixSets( m, COORDS_SHAPE_T_ROT_90 );
    }
    if( tetris_shape == TETRIS_SHAPE_T && tetris_rot == TETRIS_ROT_180 )
    {
        matrixSets( m, COORDS_SHAPE_T_ROT_180 );
    }
    if( tetris_shape == TETRIS_SHAPE_T && tetris_rot == TETRIS_ROT_270 )
    {
        matrixSets( m, COORDS_SHAPE_T_ROT_270 );
    }

    return m;
}