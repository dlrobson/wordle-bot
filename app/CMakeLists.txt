# Find imported packages
find_package(OpenCV REQUIRED)

# This is the main program, and the library it targets
add_executable(solve_wordle solve_wordle.cpp)
target_link_libraries(solve_wordle PRIVATE solver)
