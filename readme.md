# Tetris in C

A classic Tetris implementation written in C using SDL2 for graphics and input handling.

## About

This project is a fully functional Tetris game that I built to explore C programming with moderate complexity. While I'm no C expert, this codebase demonstrates core game development concepts including game loops, input handling, collision detection, and graphics rendering.

The game features all the classic Tetris mechanics you'd expect:
- Seven different tetromino shapes (I, O, T, S, Z, J, L)
- Line clearing with score tracking
- Increasing difficulty as you progress
- Smooth piece movement and rotation
- Real-time game state display

All feedback and suggestions for improvement are welcome!

## Features

- **Classic Gameplay**: Traditional Tetris rules and mechanics
- **Score System**: Points awarded for clearing lines
- **Visual Feedback**: Clean SDL2-based graphics with a game board and score display
- **Responsive Controls**: Smooth piece movement, rotation, and dropping
- **Game Over Detection**: Automatic game end when pieces reach the top

## Controls

- **Left Arrow**: Move piece left
- **Right Arrow**: Move piece right
- **Down Arrow**: Soft drop (faster fall)
- **Up Arrow**: Rotate piece clockwise
- **Space**: Hard drop (instant fall)

## Requirements

- **CMake**: Required for building the project
- **C Compiler**: GCC or Clang recommended
- **SDL2**: Graphics library (included as vendored dependency)

## Build Instructions

```bash
mkdir build
cd build
cmake ..
make
```

## Running

After building, run the executable from the build directory:

```bash
./tetris
```

## Project Structure

The codebase is organized to separate concerns:
- Game logic and state management
- SDL2 graphics and rendering
- Input handling and controls
- Tetromino shape definitions and rotations

## Contributing

This is a learning project, so contributions, suggestions, and code reviews are highly appreciated! Feel free to open issues or submit pull requests.