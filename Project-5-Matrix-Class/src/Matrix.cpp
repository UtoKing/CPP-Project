//
// Created by UtoKing on 2022/12/5.
//

#include "Matrix.h"
#include <iostream>
//#include <string>

using namespace std;
namespace Mat {

template<typename T>
T Matrix<T>::getElement(size_t r, size_t c) {
  if (not this->data) {
	cerr << "Error: Null pointer!" << endl;
	return 0;
  }
  if (r >= this->row or c >= this->column) {
	cerr << "Error: Indices out of range!" << endl;
	return 0;
  }

  return *(this->data.get() + r * this->column + c);
}

template<typename T>
bool Matrix<T>::setElement(size_t r, size_t c, const T &t) {
  if (not this->data) {
	cerr << "Error: Null pointer!" << endl;
	return false;
  }
  if (r >= this->row or c >= this->column) {
	cerr << "Error: Indices out of range!" << endl;
	return false;
  }

  *(this->data.get() + r * this->column + c) = t;
  return true;
}

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
Matrix<T> operator+(const Matrix<T> &matrix1, const Matrix<T> &matrix2) {
  return matrix1.add(matrix2);
}

template<typename T>
Matrix<T> operator+(const Matrix<T> &matrix, const T &t) {
  return matrix.add(t);
}

template<typename T>
ostream &operator<<(ostream &os, const Matrix<T> &matrix) {
  os << '[';
  shared_ptr<T> p_c = matrix.getData();
  for (size_t j = 0; j < matrix.row; ++j) {
	if (j != 0) os << ' ';
	os << '[';
	for (size_t k = 0; k < matrix.column; ++k) {
	  os << *(p_c.get() + j * (matrix.column) + k);
	  if (k < matrix.column - 1) os << ", ";
	}
	os << ']';
	if (j < matrix.row - 1) os << endl;
  }
  os << ']' << endl;
  return os;
}
}
