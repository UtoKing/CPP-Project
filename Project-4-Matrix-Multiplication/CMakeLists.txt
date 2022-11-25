cmake_minimum_required(VERSION 3.16)
project(Project_4_Matrix_Multiplication C)

find_package(OpenBLAS REQUIRED)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_FLAGS "-mavx2")
set(CMAKE_C_FLAGS "-mfma")
set(CMAKE_C_FLAGS "-O3")
set(CMAKE_C_FLAGS "-march=native")

include_directories(/usr/local/OpenBLAS/include)
link_directories(/usr/local/OpenBLAS/lib)

include_directories(include)

add_executable(Project_4_Matrix_Multiplication main.c src/matrixOperation.c include/matrixOperation.h include/main.h)

target_link_libraries(Project_4_Matrix_Multiplication openblas)