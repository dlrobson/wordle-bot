# Create a library that other files can reference
add_library(solver
    src/WordleGuesser.cpp
)

target_include_directories(solver PUBLIC
    include
)