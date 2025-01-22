//
// Created by Wouter Deferme on 17/01/2025.
//

#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include <sys/time.h>
#include "matrix.h"
#include "tetris_shape.h"

/**************************************************************************
** Structs
**************************************************************************/

typedef struct Window
{
    SDL_Window*     window_instance;
    SDL_Renderer*   renderer;
} Window;

typedef struct GameState
{
    bool            running;            /**< Game will exit if running is set to false */
    Matrix*         board;              /**< Pieces on the board (with exception of player-controlled shape */
    TETRIS_SHAPE    active_shape;       /**< Shape that is controlled by player */
    TETRIS_ROT      active_shape_rot;   /**< Shape rotation */
    int             active_shape_x;     /**< x-position of shape pivot point on board */
    int             active_shape_y;     /**< yposition of shape pivot point on board */
    int             score;              /**< Total player score */
} GameState;

typedef struct Color
{
    uint8_t     r;
    uint8_t     g;
    uint8_t     b;
    uint8_t     a;
} Color;

typedef int             RESULT;
#define RESULT_SUCCESS  0;
#define RESULT_ERROR    -1;

/**************************************************************************
** Config
**************************************************************************/
#define WINDOW_TITLE            "Tetris"
#define WINDOW_WIDTH            600
#define WINDOW_HEIGHT           900
#define GAME_LOOP_SLEEP_MS      0
#define LOGIC_LOOP_TICK_MS      700
#define RENDER_LOOP_TICK_MS     20
#define INPUT_LOOP_TICK_MS      50
#define PRINT_FPS               false
#define BOARD_WIDTH             10
#define BOARD_HEIGHT            20
#define SCORE_PER_ROW           100
#define CELL_SIZE_PX            20
#define CELL_PADDING_PX         1
#define BOARD_POS_X             20
#define BOARD_POS_Y             20
#define SHAPE_SPAWN_X           5
#define SHAPE_SPAWN_Y           (-1)

/**************************************************************************
** Colors
**************************************************************************/
Color COLOR_DARK    = { 0x29,   0x29,   0x29,   0xFF };
Color COLOR_BLACK   = { 0x00,   0x00,   0x00,   0xFF };
Color COLOR_YELLOW  = { 246,    250,    112,    0xFF };
Color COLOR_RED     = { 255,    0,      96,     0xFF };
Color COLOR_GREEN   = { 0,      223,    162,    0xFF };
Color COLOR_BLUE    = { 0,      121,    255,    0xFF };

Color SHAPE_COLORS[ 7 ];

/**************************************************************************
** Forward references
**************************************************************************/
RESULT          initWindow();
RESULT          initGameState( GameState* game_state );
void            destroyWindow();
void            loop( Window* window, GameState* game_state );
int             randomInt( int min, int max );
typedef struct  Chrono Chrono;
Chrono*         chronoStart();
int             chronoGet(Chrono* chrono);
bool            chronoTick(Chrono* chrono, int delta_ms);
void            chronoReset(Chrono* chrono);
void            eventTick( GameState* game_state );
void            inputTick( GameState* game_state );
void            logicTick( GameState* game_state );
void            renderTick( GameState* game_state, Window* window );
TETRIS_SHAPE    randomShape();
TETRIS_ROT      randomRotation();
/**************************************************************************
** Main
**************************************************************************/
int
main()
{
    SHAPE_COLORS[ TETRIS_SHAPE_SQUARE ]   = COLOR_YELLOW;
    SHAPE_COLORS[ TETRIS_SHAPE_T ]        = COLOR_RED;
    SHAPE_COLORS[ TETRIS_SHAPE_LONG ]     = COLOR_GREEN;
    SHAPE_COLORS[ TETRIS_SHAPE_S ]        = COLOR_BLUE;
    SHAPE_COLORS[ TETRIS_SHAPE_Z ]        = COLOR_YELLOW;
    SHAPE_COLORS[ TETRIS_SHAPE_J ]        = COLOR_RED;
    SHAPE_COLORS[ TETRIS_SHAPE_L ]        = COLOR_GREEN;

    Window*     window              = malloc( sizeof( Window ) );
    GameState*  game_state     = malloc( sizeof( GameState ) );

    if( initWindow( window ) < 0 )                  return RESULT_ERROR;
    if( initGameState( game_state ) < 0)        return RESULT_ERROR;

    loop( window, game_state );

    destroyWindow( window );
    matrixFree( game_state->board );
    free( window );
    free( game_state );

    return RESULT_SUCCESS;
}


/**
 * Main game loop. Triggers event, logic and render ticks at specific frequencies.
 */
void
loop( Window* window, GameState* game_state )
{
    Chrono* chronoFps           = chronoStart();
    Chrono* chronoFpsSampler    = chronoStart();
    Chrono* chronoLogicTick     = chronoStart();
    Chrono* chronoRenderTick    = chronoStart();
    Chrono* chronoInputTick     = chronoStart();

    do
    {
        if ( PRINT_FPS )
        {
            int delta_ms = chronoGet( chronoFps );
            if( chronoTick( chronoFpsSampler, 1000 ) )
            {
                printf( "Tick time: %d ms. FPS: %f \n", delta_ms, (float) 1000 / delta_ms );
            }
            chronoReset( chronoFps );
        }

        eventTick( game_state );
        if( chronoTick( chronoInputTick, INPUT_LOOP_TICK_MS ) )     inputTick(  game_state );
        if( chronoTick( chronoLogicTick, LOGIC_LOOP_TICK_MS ) )     logicTick(  game_state );
        if( chronoTick( chronoRenderTick, RENDER_LOOP_TICK_MS ) )   renderTick( game_state, window );

        SDL_Delay(GAME_LOOP_SLEEP_MS);

    } while ( game_state->running == true );

    free( chronoFps );
    free( chronoLogicTick );
    free( chronoFpsSampler );
    free( chronoRenderTick );
    free( chronoInputTick );
}


RESULT
initGameState( GameState* game_state )
{
    if( game_state == NULL )
    {
        return RESULT_ERROR ;
    }
    game_state->running = true;
    game_state->score = 0;
    game_state->active_shape = randomShape();
    game_state->active_shape_rot = randomRotation();
    game_state->active_shape_x = SHAPE_SPAWN_X;
    game_state->active_shape_y = SHAPE_SPAWN_Y;
    game_state->board = matrixMake( BOARD_WIDTH, BOARD_HEIGHT );

    for ( int i = 0; i < BOARD_WIDTH; i++ )
    {
        for ( int j = 0; j < BOARD_HEIGHT; j++ )
        {
            matrixSet( game_state->board, i, j, 0 );
        }
    }

    return RESULT_SUCCESS;
}

// Validate if new shape position and rotation is within bounds of the board and
// not colliding with shapes that were already dropped.
bool
validateShape( GameState* game_state, int x, int y, TETRIS_ROT tetris_rot )
{
    bool valid = true;
    Matrix* coords = getLocalShapeCells( game_state->active_shape, x, y, tetris_rot );

    for( int coord = 0; coord < coords->rows; coord++ )
    {
        const int new_x = matrixGet( coords, coord, 0 );
        const int new_y = matrixGet( coords, coord, 1 );

        // Check collision with board bounds. y < 0 is allowed for
        // spawned blocks.
        if( new_x < 0                   ||
            new_x > BOARD_WIDTH - 1     ||
            new_y > BOARD_HEIGHT - 1 )
        {
            valid = false;
            break;
        }

        // Check for collision with board elements (but only when y > 0 to prevent out
        // of bounds matrixGet)
        if( new_y > 0 && matrixGet( game_state->board, new_x, new_y) > 0 )
        {
            valid = false;
            break;
        }
    }

    free( coords );
    return valid;
}

// Rotate active piece by 90 deg clockwise (if it does not collide).
void
rotateShape( GameState* game_state )
{
    TETRIS_ROT target_rot;
    if ( game_state->active_shape_rot < 3 )
    {
        target_rot = game_state->active_shape_rot + 1;
    } else
    {
        target_rot = 0;
    }

    if( !validateShape( game_state, game_state->active_shape_x, game_state->active_shape_y, target_rot ) )
    {
        return;
    }

    game_state->active_shape_rot = target_rot;
}

// Move shape along dx or dy (if it does not collide). Returns 0 on success
// and -1 on failure (collision).
int
moveShape( GameState* game_state, int dx, int dy )
{
    const int target_x = game_state->active_shape_x + dx;
    const int target_y = game_state->active_shape_y + dy;

    if( !validateShape( game_state, target_x, target_y, game_state->active_shape_rot ) )
    {
        return -1;
    }
    game_state->active_shape_x = target_x;
    game_state->active_shape_y = target_y;
    return 0;
}

// Spawn a new shape.
void
spawnShape( GameState* game_state )
{
    game_state->active_shape = randomInt( 0, 6 );
    game_state->active_shape_rot = randomInt( 0, 3 );
    game_state->active_shape_x = SHAPE_SPAWN_X;
    game_state->active_shape_y = SHAPE_SPAWN_Y;
}

// Freeze shape in place on the board.
void
freezeShape( GameState* game_state )
{
    Matrix* coords = getLocalShapeCells( game_state->active_shape,
                                        game_state->active_shape_x,
                                        game_state->active_shape_y,
                                        game_state->active_shape_rot );

    for( int coord = 0; coord < coords->rows; coord++ )
    {
        const int x = matrixGet( coords, coord, 0 );
        const int y = matrixGet( coords, coord, 1 );
        matrixSet( game_state->board, x, y, 1 );
    }

    free( coords );
}

// Find full rows, clear them and add to the score.
void
clearFullRows( GameState* game_state)
{
    // Loop over all board rows from bottom to top.
    int row = BOARD_HEIGHT - 1;
    while ( row > 0 )
    {
        bool is_row_full = true;
        for( int col = 0; col < BOARD_WIDTH; col++ )
        {
            if ( matrixGet( game_state->board, col, row ) == 0 )
            {
                is_row_full = false;
                break;
            }
        }

        if (is_row_full)
        {
            // Clear this line
            for( int col = 0; col < BOARD_WIDTH; col++ )
            {
                matrixSet( game_state->board, col, row, 0 );
            }

            // Move all lines above 1 row downward
            for( int i = row; i > 1; i-- )
            {
                for( int j = 0; j < BOARD_WIDTH; j++ )
                {
                    matrixSet( game_state->board, j, i, matrixGet( game_state->board, j, i - 1 ) );
                }
            }

            // Add score
            game_state->score += SCORE_PER_ROW;

            // All rows moved down, so the loop should check this row again
        } else
        {
            // Loop should check next row (1 up)
            row--;
        }
    }
}

void
logicTick( GameState* game_state )
{
    // Gravity
    int result = moveShape( game_state, 0, 1 );

    // Spawn new shape if shape cannot move
    if( result < 0 )
    {
        freezeShape( game_state );
        spawnShape( game_state );
    }

    clearFullRows( game_state );
}

// Draws a cell in the board at i (height) and j (width) at color
void
drawCell( Window* window, int i, int j, Color color )
{
    SDL_Rect fillRect = {   BOARD_POS_X + i * CELL_PADDING_PX + i * CELL_SIZE_PX,
                            BOARD_POS_Y + j * CELL_PADDING_PX + j * CELL_SIZE_PX,
                            CELL_SIZE_PX,
                            CELL_SIZE_PX };

    SDL_SetRenderDrawColor( window->renderer, color.r, color.g, color.b, color.a );
    SDL_RenderFillRect( window->renderer, &fillRect );
}

// Draws a tetris shape in the board at i (height) and j (width) and rotation (tetris_rot).
void
drawTetrisShape( Window* window, int tetris_shape, int i, int j, TETRIS_ROT tetris_rot )
{
    Matrix* m = getLocalShapeCells( tetris_shape, i, j, tetris_rot );

    for( int coord = 0; coord < m->rows; coord++ )
    {
        const int x = matrixGet( m, coord, 0 );
        const int y = matrixGet( m, coord, 1 );

        if ( y < 0 )
        {
            return;
        }
        drawCell( window,
                x,
                y,
                SHAPE_COLORS[ tetris_shape ] );
    }

    free( m );
}

void
drawScore( Window* window )
{
}

void
renderTick( GameState* game_state, Window* window )
{
    SDL_SetRenderDrawColor( window->renderer,
                            COLOR_DARK.r,
                            COLOR_DARK.g,
                            COLOR_DARK.b,
                            COLOR_DARK.a);
    SDL_RenderClear( window->renderer );

    // Draw board
    for( int i = 0; i < BOARD_WIDTH; i++ )
    {
        for( int j = 0; j < BOARD_HEIGHT; j++ )
        {
            if ( matrixGet( game_state->board, i, j ) == 0)
            {
                // Empty board cell
                drawCell( window, i, j, COLOR_BLACK );
            } else
            {
                // Board cell containing frozen shape
                drawCell( window, i, j, COLOR_YELLOW );
            }
        }
    }

    drawScore( window );

    // Draw active (player-controlled) shape
    drawTetrisShape(    window,
                        game_state->active_shape,
                        game_state->active_shape_x,
                        game_state->active_shape_y,
                        game_state->active_shape_rot );

    SDL_RenderPresent( window->renderer );
}



void
inputTick( GameState* game_state )
{
    const uint8_t* keysArray = SDL_GetKeyboardState( NULL );
    if ( keysArray[SDL_SCANCODE_DOWN] )
    {
        moveShape( game_state, 0 , 1 );
    }
    if( keysArray[SDL_SCANCODE_LEFT] )
    {
        moveShape( game_state, -1, 0 );
    }
    if( keysArray[SDL_SCANCODE_RIGHT] )
    {
        moveShape( game_state, 1, 0 );
    }
}

void
eventTick( GameState* game_state )
{
    SDL_Event event;
    while( SDL_PollEvent( &event ) != 0 )
    {
        if( event.type == SDL_QUIT )
        {
            game_state->running = false;
        }
        else if( event.type == SDL_KEYDOWN )
        {
            switch( event.key.keysym.sym )
            {
                case SDLK_ESCAPE:
                    game_state->running = false;
                    break;
                case SDLK_SPACE:
                    rotateShape( game_state );
                    break;
                default:
                    break;
            }
        }
    }
}

/**************************************************************************
** Chronometer logic for managing the game loop.
**************************************************************************/

typedef struct Chrono
{
    struct timeval start_time;
    struct timeval current_time;
} Chrono;

/*
 * Start a chronometer.
 */
Chrono*
chronoStart()
{
    Chrono* chrono = malloc( sizeof( Chrono ) );
    gettimeofday( &chrono->start_time, NULL );
    return chrono;
}

/*
 * Get the time in ms since the chronometer was started.
 */
int
chronoGet( Chrono* chrono )
{
    gettimeofday( &chrono->current_time, NULL );
    return ( chrono->current_time.tv_sec - chrono->start_time.tv_sec ) * 1000 +
        ( chrono->current_time.tv_usec - chrono->start_time.tv_usec ) / 1000;

}

/*
 * Reset chronometer start time.
 */
void
chronoReset( Chrono* chrono )
{
    gettimeofday( &chrono->start_time, NULL );
}

/*
 * Returns true if called after the chronometer has passed a set amount of time (delta_ms) and resets
 * the chronometer when it returns true. Can be used in a loop at a higher frequency then 1/delta_ms
 * for the intent of only invoking a method at frequency 1/delta_ms.
 */
bool
chronoTick( Chrono* chrono, int delta_ms )
{
    if( chronoGet( chrono ) >= delta_ms )
    {
        chronoReset( chrono );
        return true;
    }

    return false;
}

RESULT
initWindow(Window* window)
{

    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Could not initialize SDL. SDL_Error: %s\n", SDL_GetError() );
        return RESULT_ERROR;
    }

    window->window_instance = SDL_CreateWindow(
        WINDOW_TITLE,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN );

    if( window->window_instance == NULL )
    {
        printf( "Could not initialize Window. SDL_Error: %s\n", SDL_GetError() );
        return RESULT_ERROR;
    }

    window->renderer = SDL_CreateRenderer( window->window_instance, -1, SDL_RENDERER_ACCELERATED );

    if( window->renderer == NULL )
    {
        printf( "Could not initialize renderer. SDL_Error: %s\n", SDL_GetError() );
        return RESULT_ERROR;
    }

    return RESULT_SUCCESS;
}

void
destroyWindow( Window* window )
{
    SDL_DestroyWindow( window->window_instance );
    SDL_Quit();
}

// Generate a random number between min and max
int randomInt( int min, int max )
{
    return rand() % (max - min + 1) + min;
}

TETRIS_SHAPE
randomShape()
{
    return randomInt( 0, 6 );
}

TETRIS_ROT
randomRotation()
{
    return randomInt( 0, 3 );
}