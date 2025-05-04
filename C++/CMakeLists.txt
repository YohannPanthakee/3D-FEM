cmake_minimum_required(VERSION 3.13)  # CMake version check
project(3D_FEM)                       # Create project "simple_example"
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard


# Include directories for Eigen and matplotlib-cpp
include_directories(.)
include_directories(lib/matplotlib)
include_directories(lib/Eigen)
include_directories(lib/Json/include)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(CPP_Solver
               main.cpp
               src/loader.cpp
               src/loader.h)

find_package(Python COMPONENTS Development)
target_include_directories(CPP_Solver PRIVATE ${Python_INCLUDE_DIRS})
target_link_libraries(CPP_Solver ${Python_LIBRARIES})


