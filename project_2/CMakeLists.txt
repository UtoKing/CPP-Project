cmake_minimum_required(VERSION 3.16)
project(project_2)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(project_2 main.cpp src/strMultiply.cpp src/strAdd.cpp src/numberFunctions.cpp src/strMinus.cpp src/strDivision.cpp src/basicFunction.cpp src/RPN_convert.cpp include/RPN_convert.h)
