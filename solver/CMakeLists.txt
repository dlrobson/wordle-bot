# Create a library that other files can reference
add_library(solver src/wordle_solver.cpp src/solver_benchmark.cpp)

target_include_directories(solver PUBLIC include)
