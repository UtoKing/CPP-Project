cmake_minimum_required(VERSION 3.16)
project(Project_4_Matrix_Multiplication C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_COMPILER gcc)

include_directories(include)

add_executable(Project_4_Matrix_Multiplication main.c src/matrixOperation.c include/matrixOperation.h include/main.h)
