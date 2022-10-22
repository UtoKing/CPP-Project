cmake_minimum_required(VERSION 3.16)
project(Project_3_Matrix_Operation C)

set(CMAKE_C_STANDARD 99)

include_directories(include)

add_executable(Project_3_Matrix_Operation main.c include/matrix.h src/matrixOperation.c include/matrixOperation.h main.h)
