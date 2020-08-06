cmake_minimum_required(VERSION 3.10)

project(MazeGenerator VERSION 0.6.1 LANGUAGES CXX)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_DEBUG_LIBS OFF)
set(Boost_USE_RELEASE_LIBS ON)
find_package(Boost REQUIRED COMPONENTS program_options)

add_executable(mazer
    src/genmaze.cpp src/maze_def.cpp src/maze_print.cpp src/maze_algos/dfs.cpp
    src/maze_algos/kruskal.cpp src/maze_algos/recurse_div.cpp
    src/maze_algos/wilson.cpp
)

configure_file (
    "${CMAKE_CURRENT_SOURCE_DIR}/include/MazeGenerator/version.h.in"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/MazeGenerator/version.h"
)

target_include_directories(mazer
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        ${Boost_INCLUDE_DIRS}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(mazer
    PRIVATE
        Boost::program_options
)

target_compile_options(mazer PRIVATE -O3)

