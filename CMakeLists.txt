project(WordleSolver)
cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_STANDARD 17)

# This is for clangd vscode extension
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Install conan (https://github.com/conan-io/cmake-conan)
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.16.1/conan.cmake"
                "${CMAKE_BINARY_DIR}/conan.cmake"
                EXPECTED_HASH SHA256=396e16d0f5eabdc6a14afddbcfff62a54a7ee75c6da23f32f7a31bc85db23484
                TLS_VERIFY ON)
endif()
include(${CMAKE_BINARY_DIR}/conan.cmake)
conan_cmake_install(PATH_OR_REFERENCE ${PROJECT_SOURCE_DIR})

# Strict compile errors, with warnings
# if ( CMAKE_COMPILER_IS_GNUCC )
#     set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")
# endif()
# if ( MSVC )
#     set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /W4")
# endif()

# References the conan library
include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

# Find imported packages
find_package(OpenCV REQUIRED)

# This is the main program, and the library it targets
add_executable(solve_wordle
    solve_wordle.cpp
)

target_link_libraries(solve_wordle PRIVATE
    solver
    opencv::highgui
    opencv::imgproc
    opencv::imgcodecs
)

# target_include_directories(solve_wordle PRIVATE
#     ${CMAKE_BINARY_DIR}
# )

# Directories to include to search for additional CMakeLists.txt
add_subdirectory(solver)
