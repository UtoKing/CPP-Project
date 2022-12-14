//
// Created by UtoKing on 2022/12/2.
//

#ifndef PROJECT_5_MATRIX_CLASS_INCLUDE_MATRIX_H_
#define PROJECT_5_MATRIX_CLASS_INCLUDE_MATRIX_H_

#include <memory>
#include <iostream>
#include <vector>

using namespace std;

namespace Mat {

template<typename T>
class Matrix {
 private:
  shared_ptr<T> data;
  size_t row, column;

 public:
  explicit Matrix(size_t r = 0, size_t c = 0) : row(r), column(c) {
	shared_ptr<T> temp(new T[r * c]);
	data = temp;
  }
  Matrix(size_t r, size_t c, T *p_t) : row(r), column(c) {
	shared_ptr<T> temp(p_t);
	data = temp;
  }
  Matrix(const Matrix &matrix) : row(matrix.row), column(matrix.column) {
	data = matrix.getData();
  }

  //Basic information getter
  shared_ptr<T> getData() const { return this->data; }
  size_t getRow() const { return this->row; }
  size_t getColumn() const { return this->column; }
  T getElement(size_t r, size_t c);
  bool setElement(size_t r, size_t c, const T &t);
  vector<T> operator[](size_t r);
  const vector<T> &operator[](size_t) const;

  //Matrix operation
  Matrix<T> transpose() const;

  // Addition
  Matrix<T> add(const Matrix<T> &) const;
  Matrix<T> add(const T &) const;
  Matrix<T> operator+(const Matrix<T> &);
  Matrix<T> operator+(const T &);
  template<typename U, typename V>
  friend Matrix<U> operator+(const V &, const Matrix<U> &);
  Matrix<T> &operator+=(const Matrix<T> &);
  Matrix<T> &operator+=(const T &);

  //subtraction
  Matrix<T> subtract(const Matrix<T> &) const;
  Matrix<T> subtract(const T &) const;
  Matrix<T> operator-(const Matrix<T> &);
  Matrix<T> operator-(const T &);
  template<typename U, typename V>
  friend Matrix<U> operator-(const V &, const Matrix<U> &);
  Matrix<T> &operator-=(const Matrix<T> &);
  Matrix<T> &operator-=(const T &);

  //multiplication
  Matrix<T> multiply(const Matrix<T> &) const;
  Matrix<T> multiply(const T &) const;
  Matrix<T> operator*(const Matrix<T> &);
  Matrix<T> operator*(const T &) const;
  template<typename U, typename V>
  friend Matrix<U> operator*(const V &, const Matrix<U> &);
  Matrix<T> &operator*=(const Matrix<T> &);
  Matrix<T> &operator*=(const T &);

  //Assignment
  Matrix<T> &operator=(const Matrix<T> &);

  //equal
  bool operator==(const Matrix<T> &);

  //io stream
  template<typename U>
  friend ostream &operator<<(ostream &os, const Matrix<U> &matrix);

  ~Matrix() {
	data.reset();
  }
};
}// Mat

#include "matrix_add.inl"
#include "matrix_subtract.inl"
#include "matrix_multiply.inl"
#include "matrix_operation.inl"
#include "Matrix.inl"

#endif //PROJECT_5_MATRIX_CLASS_INCLUDE_MATRIX_H_
