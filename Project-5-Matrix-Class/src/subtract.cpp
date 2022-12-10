//
// Created by UtoKing on 2022/12/10.
//

#include "Matrix.h"
#include <iostream>

using namespace std;

namespace Mat {
//subtraction
template<typename T>
Matrix<T> Matrix<T>::subtract(const Matrix<T> &matrix) const {
  if (not this->data or not matrix.getData()) {
	cerr << "Error: Null pointer!" << endl;
	return Matrix<T>();
  }
  if (this->row != matrix.row or this->column != matrix.column) {
	cerr << "Error: matrix are not the same size" << endl;
	return Matrix<T>();
  }

  T *p_t = new T[this->row * this->column];
  for (int i = 0; i < this->row * this->column; ++i) {
	*(p_t + i) = *(this->data.get() + i) - *(matrix.getData().get() + i);
  }
  return Matrix<T>(this->row, this->column, p_t);
}

template<typename T>
Matrix<T> Matrix<T>::subtract(const T &t) const {
  if (not this->data) {
	cerr << "Error: Null pointer!" << endl;
	return Matrix<T>();
  }

  T *p_t = new T[this->row * this->column];
  for (int i = 0; i < this->row * this->column; ++i) {
	*(p_t + i) = *(this->data.get() + i) - t;
  }
  return Matrix<T>(this->row, this->column, p_t);
}

template<typename T>
bool Matrix<T>::subtract_(const Matrix<T> &matrix) {
  if (not this->data or not matrix.getData()) {
	cerr << "Error: Null pointer!" << endl;
	return false;
  }
  if (this->row != matrix.row or this->column != matrix.column) {
	cerr << "Error: matrix are not the same size" << endl;
	return false;
  }

  for (int i = 0; i < this->row * this->column; ++i) {
	*(this->data.get() + i) = *(this->data.get() + i) - *(matrix.getData().get() + i);
  }
  return true;
}

template<typename T>
bool Matrix<T>::subtract_(const T &t) {
  if (not this->data) {
	cerr << "Error: Null pointer!" << endl;
	return false;
  }

  for (int i = 0; i < this->row * this->column; ++i) {
	*(this->data.get() + i) -= t;
  }
  return true;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &matrix) {
  return this->subtract(matrix);
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const T &t) {
  return this->subtract(t);
}

template<typename T, typename V>
Matrix<T> operator-(const V &v, const Matrix<T> &matrix) {
  if (not matrix.data) {
	cerr << "Error: Null pointer!" << endl;
	return Matrix<T>();
  }

  T *p_t = new T[matrix.row * matrix.column];
  for (int i = 0; i < matrix.row * matrix.column; ++i) {
	*(p_t + i) = v - *(matrix.data.get() + i);
  }
  return Matrix<T>(matrix.row, matrix.column, p_t);
}

template<typename T>
Matrix<T> &Matrix<T>::operator-=(const Matrix<T> &matrix) {
  if (not this->data or not matrix.getData()) {
	cerr << "Error: Null pointer!" << endl;
	return *this;
  }
  if (this->row != matrix.row or this->column != matrix.column) {
	cerr << "Error: matrix are not the same size" << endl;
	return *this;
  }

  this->subtract_(matrix);
  return *this;
}

template<typename T>
Matrix<T> &Matrix<T>::operator-=(const T &t) {
  if (not this->data) {
	cerr << "Error: Null pointer!" << endl;
	return *this;
  }

  this->subtract_(t);
  return *this;
}
}
