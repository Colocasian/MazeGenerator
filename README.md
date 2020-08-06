# Maze Generator

Various implementations of maze forming algorithms.

## Building

### Requirements

To compile this project, the needed components are:

- Valid C++ compiler
- CMake
- Boost library (libboost_program_options)

### Instructions

Just execute the following commands in the terminal

```sh
git clone https://github.com/Colocasian/MazeGenerator.git
cd MazeGenerator
mkdir build
cd build
cmake ..
make
```

To remove the build files, just remove the `build` directory

## How to use

After building, an executable named `mazer` will be present in the bin
directory. To see how to use the command, run `path/to/mazer -h` or
`path/to/mazer -h`.
