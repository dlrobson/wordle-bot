# Create a library that other files can reference
add_library(
    solver src/wordle.cpp src/solver_benchmark.cpp src/positional_solver.cpp
           src/wordle_utils.cpp src/frequency_solver.cpp src/solver.cpp)

target_include_directories(solver PUBLIC include)
