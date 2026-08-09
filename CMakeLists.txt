cmake_minimum_required(VERSION 3.10)
project(ArbitrageDetector VERSION 1.0.0 LANGUAGES CXX)

# Enforce C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler flags for high performance
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -Wextra -Wpedantic")

# Include directories
include_directories(include)

# Add executable
add_executable(detector 
    src/main.cpp
    src/ArbitrageDetector.cpp
)
