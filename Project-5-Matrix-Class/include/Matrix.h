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
class Matrix {
 private:
  shared_ptr<T> data;
  size_t row, column;

  //Addition
  bool add_(const T &);
  bool add_(const Matrix<T> &);

  //Subtraction
  bool subtract_(const T &);
  bool subtract_(const Matrix<T> &);

 public:
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
  size_t getRow() const { return this->row; }
  size_t getColumn() const { return this->column; }

  T getElement(size_t r, size_t c);
  bool setElement(size_t r, size_t c, const T &t);

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

  //Assignment
  Matrix<T> &operator=(const Matrix<T> &);

  template<typename U>
  friend ostream &operator<<(ostream &os, const Matrix<U> &matrix);

  ~Matrix() {
	data.reset();
  }
};

}// Mat

#endif //PROJECT_5_MATRIX_CLASS_INCLUDE_MATRIX_H_
