//
// Created by UtoKing on 2022/12/13.
//

#ifndef PROJECT_5_MATRIX_CLASS_INCLUDE_TENSOR_H_
#define PROJECT_5_MATRIX_CLASS_INCLUDE_TENSOR_H_

#include <iostream>
#include "Matrix.h"

using namespace std;

namespace Mat {

template<typename T>
class Tensor {
 private:
  size_t channel;
  Matrix<T> **matrix_;

 public:
  Tensor() : channel(0) {}
  Tensor(size_t r, size_t col, size_t ch);
  Tensor(size_t r, size_t col, size_t ch, T *p_t);

  //Basic information getter
  size_t getRow() const { return matrix_[0]->getRow(); }
  size_t getColumn() const { return matrix_[0]->getColumn(); }
  size_t getChannel() const { return channel; }
  T getElement(size_t, size_t, size_t);
  bool setElement(size_t, size_t, size_t, const T &);

  //Matrix operation
  Tensor<T> transpose() const;

  //io stream
  template<typename U>
  friend ostream &operator<<(ostream &os, const Tensor<U> &tensor);

  ~Tensor() {
	matrix_[0]->~Matrix<T>();
  }
};
} // Mat

#include "Tensor.inl"

#endif //PROJECT_5_MATRIX_CLASS_INCLUDE_TENSOR_H_
