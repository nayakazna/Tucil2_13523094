cmake_minimum_required(VERSION 3.16)
project(QuadtreeCompressor CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include directories
include_directories(
    src/modules
    src/modules/external
)

# Source files
file(GLOB MODULE_SOURCES
    src/modules/*.cpp
)

add_executable(main
    src/main.cpp
    ${MODULE_SOURCES}
)
