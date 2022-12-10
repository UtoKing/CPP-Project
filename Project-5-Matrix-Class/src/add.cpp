//
// Created by UtoKing on 2022/12/10.
//

#include "Matrix.h"
#include <iostream>

using namespace std;

namespace Mat {
//addition
template<typename T>
Matrix<T> Matrix<T>::add(const Matrix<T> &matrix) const {
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
	*(p_t + i) = *(this->data.get() + i) + *(matrix.getData().get() + i);
  }
  return Matrix<T>(this->row, this->column, p_t);
}

template<typename T>
Matrix<T> Matrix<T>::add(const T &t) const {
  if (not this->data) {
	cerr << "Error: Null pointer!" << endl;
	return Matrix<T>();
  }

  T *p_t = new T[this->row * this->column];
  for (int i = 0; i < this->row * this->column; ++i) {
	*(p_t + i) = t + *(this->data.get() + i);
  }
  return Matrix<T>(this->row, this->column, p_t);
}

template<typename T>
bool Matrix<T>::add_(const Matrix<T> &matrix) {
  if (not this->data or not matrix.getData()) {
	cerr << "Error: Null pointer!" << endl;
	return false;
  }
  if (this->row != matrix.row or this->column != matrix.column) {
	cerr << "Error: matrix are not the same size" << endl;
	return false;
  }

  for (int i = 0; i < this->row * this->column; ++i) {
	*(this->data.get() + i) = *(this->data.get() + i) + *(matrix.getData().get() + i);
  }
  return true;
}

template<typename T>
bool Matrix<T>::add_(const T &t) {
  if (not this->data) {
	cerr << "Error: Null pointer!" << endl;
	return false;
  }

  for (int i = 0; i < this->row * this->column; ++i) {
	*(this->data.get() + i) += t;
  }
  return true;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &matrix) {
  return this->add(matrix);
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const T &t) {
  return this->add(t);
}

template<typename T, typename V>
Matrix<T> operator+(const V &v, const Matrix<T> &matrix) {
  return matrix.add(T(v));
}

template<typename T>
Matrix<T> &Matrix<T>::operator+=(const Matrix<T> &matrix) {
  if (not this->data or not matrix.getData()) {
	cerr << "Error: Null pointer!" << endl;
	return *this;
  }
  if (this->row != matrix.row or this->column != matrix.column) {
	cerr << "Error: matrix are not the same size" << endl;
	return *this;
  }

  this->add_(matrix);
  return *this;
}

template<typename T>
Matrix<T> &Matrix<T>::operator+=(const T &t) {
  if (not this->data) {
	cerr << "Error: Null pointer!" << endl;
	return *this;
  }

  this->add_(t);
  return *this;
}
}
