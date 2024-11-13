cmake_minimum_required(VERSION 3.27)
project(cpp_chess CXX)  # Ensure this specifies CXX for C++ projects

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)  # Set the desired C++ standard (11, 14, 17, or 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include the source directory
include_directories(src)

# Define the executable and its sources
add_executable(cpp_chess
        src/board.cpp
        src/board.h
        src/main.cpp
        src/game.cpp
        src/utils.cpp
)
