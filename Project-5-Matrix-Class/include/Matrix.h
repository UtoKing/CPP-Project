//
// Created by UtoKing on 2022/12/2.
//

#ifndef PROJECT_5_MATRIX_CLASS_INCLUDE_MATRIX_H_
#define PROJECT_5_MATRIX_CLASS_INCLUDE_MATRIX_H_

#include <cstddef>
namespace Mat {

template<typename T>
class Matrix {
 private:
  size_t row, column, channel;
  T *data;
};

} // Mat

#endif //PROJECT_5_MATRIX_CLASS_INCLUDE_MATRIX_H_
