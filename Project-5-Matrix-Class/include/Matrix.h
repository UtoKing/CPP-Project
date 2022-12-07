//
// Created by UtoKing on 2022/12/2.
//

#ifndef PROJECT_5_MATRIX_CLASS_INCLUDE_MATRIX_H_
#define PROJECT_5_MATRIX_CLASS_INCLUDE_MATRIX_H_

#include <memory>
#include <iostream>

using namespace std;

namespace Mat {
template<typename T>
class Matrix;

template<typename T>
class Matrix {
 private:
  shared_ptr<T> data;

 public:
  size_t row, column;
  Matrix() : row(0), column(0) {}
  Matrix(size_t r, size_t c) : row(r), column(c) {
	data.get() = new T[r * c];
  }
  Matrix(size_t r, size_t c, T *p_t) : row(r), column(c) {
	shared_ptr<T> temp(p_t);
	data = temp;
  }
  Matrix(const Matrix &matrix) : row(matrix.row), column(matrix.column) {
	this->data = matrix.getData();
  }

  shared_ptr<T> getData() const { return this->data; }

  T getElement(size_t r, size_t c);
  bool setElement(size_t r, size_t c, const T &t);

  // Addition
  Matrix<T> add(const Matrix<T> &) const;
  bool add_(const Matrix<T> &);
  Matrix<T> add(const T &) const;
  bool add_(const T &);

  template<typename U>
  friend Matrix<U> operator+(const Matrix<U> &, const Matrix<U> &);

  template<typename U>
  friend Matrix<U> operator+(const Matrix<U> &, const U &);

  template<typename U>
  friend ostream &operator<<(ostream &os, const Matrix<U> &matrix);
};

}// Mat

#endif //PROJECT_5_MATRIX_CLASS_INCLUDE_MATRIX_H_
