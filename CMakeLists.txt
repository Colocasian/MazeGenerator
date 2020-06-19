cmake_minimum_required(VERSION 3.10)

project(MazeGenerator VERSION 0.3.2 LANGUAGES CXX)

add_executable(mazer
    src/genmaze.cpp src/maze_func.cpp src/maze_algos/dfs.cpp
    src/maze_algos/kruskal.cpp src/maze_algos/recurse_div.cpp
)

target_include_directories(mazer
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(mazer PRIVATE -Ofast)

