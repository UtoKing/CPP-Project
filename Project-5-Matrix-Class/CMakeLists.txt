cmake_minimum_required(VERSION 3.22)
project(Project_5_Matrix_Class)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-mavx2")
set(CMAKE_CXX_FLAGS "-mfma")
set(CMAKE_CXX_FLAGS "-O3")
set(CMAKE_CXX_FLAGS "-Wpsabi")

add_compile_options(-march=native)

include_directories(include)

add_executable(Project_5_Matrix_Class main.cpp include/Matrix.h src/Matrix.cpp src/add.cpp src/subtract.cpp src/multiply.cpp main.h)
