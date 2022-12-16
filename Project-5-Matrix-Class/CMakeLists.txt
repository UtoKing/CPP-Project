cmake_minimum_required(VERSION 3.22)
project(Project_5_Matrix_Class)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-mavx2")
set(CMAKE_CXX_FLAGS "-mfma")
set(CMAKE_CXX_FLAGS "-O3")
set(CMAKE_CXX_FLAGS "-Wpsabi")

add_compile_options(-march=native)

include_directories(include)

add_executable(Project_5_Matrix_Class main.cpp include/Matrix.h include/Matrix.inl include/matrix_add.inl include/matrix_subtract.inl include/matrix_multiply.inl main.h include/matrix_operation.inl include/Tensor.inl include/Tensor.h include/vector_operation.h include/tensor_operation.inl include/tensor_add.inl include/tensor_subtract.inl include/tensor_multiply.inl)
