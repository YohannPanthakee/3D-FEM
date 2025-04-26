cmake_minimum_required(VERSION 3.13)  # CMake version check
project(3D_FEM)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

# Add main.cpp file of the project root directory as a source file
set(SOURCE_FILES src/main.cpp)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(CPP_Solver ${SOURCE_FILES})

# Include directories for Eigen and matplotlib-cpp
target_include_directories(CPP_Solver PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/Eigen
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/matplotlib
)

# Find Python3 (since matplotlib-cpp depends on Python)
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

# Include Python headers
target_include_directories(CPP_Solver PRIVATE ${Python3_INCLUDE_DIRS})

# Link Python libraries
target_link_libraries(CPP_Solver PRIVATE ${Python3_LIBRARIES})