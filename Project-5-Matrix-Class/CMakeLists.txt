cmake_minimum_required(VERSION 3.22)
project(Project_5_Matrix_Class)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(Project_5_Matrix_Class main.cpp include/Matrix.h src/Matrix.cpp)
