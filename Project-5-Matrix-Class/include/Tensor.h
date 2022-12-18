//
// Created by UtoKing on 2022/12/13.
//

#ifndef PROJECT_5_MATRIX_CLASS_INCLUDE_TENSOR_H_
#define PROJECT_5_MATRIX_CLASS_INCLUDE_TENSOR_H_

#include <iostream>
#include <memory>
#include "Matrix.h"

using namespace std;

namespace Mat {

template<typename T>
class Tensor {
 private:
  size_t channel, row, column;
  shared_ptr<T> data;

 public:
  explicit Tensor(size_t ch = 0, size_t r = 0, size_t col = 0);
  Tensor(size_t, size_t, size_t, T *);
  Tensor(const Tensor<T> &);

  //Basic information getter and setter
  shared_ptr<T> getData() const { return this->data; }
  size_t getRow() const { return row; }
  size_t getColumn() const { return column; }
  size_t getChannel() const { return channel; }
  T getElement(size_t, size_t, size_t);
  bool setElement(size_t, size_t, size_t, const T &);
  Matrix<T> operator[](size_t);
  const Matrix<T> &operator[](size_t) const;

  //Tensor operation
  Tensor<T> transpose() const;
  Matrix<T> getChannelMatrix(size_t ch) const;

  //Tensor addition
  Tensor<T> operator+(const Tensor<T> &);
  Tensor<T> operator+(const Matrix<T> &);
  Tensor<T> operator+(const T &);
  template<typename U, typename V>
  friend Tensor<U> operator+(const V &, const Tensor<U> &);
  template<typename U>
  friend Tensor<U> operator+(const Matrix<U> &, const Tensor<U> &);
  Tensor<T> &operator+=(const Tensor<T> &);
  Tensor<T> &operator+=(const Matrix<T> &);
  Tensor<T> &operator+=(const T &);

  //subtraction
  Tensor<T> operator-(const Tensor<T> &);
  Tensor<T> operator-(const Matrix<T> &);
  Tensor<T> operator-(const T &);
  template<typename U, typename V>
  friend Tensor<U> operator-(const V &, const Tensor<U> &);
  template<typename U>
  friend Tensor<U> operator-(const Matrix<U> &, const Tensor<U> &);
  Tensor<T> &operator-=(const Tensor<T> &);
  Tensor<T> &operator-=(const Matrix<T> &);
  Tensor<T> &operator-=(const T &);

  //multiplication
  Tensor<T> operator*(const Tensor<T> &);
  Tensor<T> operator*(const Matrix<T> &);
  Tensor<T> operator*(const T &) const;
  template<typename U, typename V>
  friend Tensor<U> operator*(const V &, const Tensor<U> &);
  template<typename U>
  friend Tensor<U> operator*(const Matrix<U> &, const Tensor<U> &);
  Tensor<T> &operator*=(const Tensor<T> &);
  Tensor<T> &operator*=(const Matrix<T> &);
  Tensor<T> &operator*=(const T &);

  //Assignment
  Tensor<T> &operator=(const Tensor<T> &);

  //equal
  bool operator==(const Tensor<T> &);

  //io stream
  template<typename U>
  friend ostream &operator<<(ostream &os, const Tensor<U> &tensor);

  ~Tensor() {
	data.reset();
  }
};

} // Mat

#include "Tensor.inl"
#include "tensor_operation.inl"
#include "tensor_add.inl"
#include "tensor_subtract.inl"
#include "tensor_multiply.inl"

#endif //PROJECT_5_MATRIX_CLASS_INCLUDE_TENSOR_H_
