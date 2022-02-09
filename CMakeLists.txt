project(WordleSolver)
cmake_minimum_required(VERSION 3.10.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(GNUInstallDirs)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(solver)

add_executable(solve_wordle
    solve_wordle.cpp
)

target_link_libraries(solve_wordle
    solver
)