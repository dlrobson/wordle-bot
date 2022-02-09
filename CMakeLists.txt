project(WordleSolver)
cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_STANDARD 17)

# This is for clangd vscode extension
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# References the conan library
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Directories to include to search for additional CMakeLists.txt
add_subdirectory(solver)

# This is the main program
add_executable(solve_wordle
    solve_wordle.cpp
)

# Ensure we can find the classes stored in the solver directory
target_link_libraries(solve_wordle
    solver
)