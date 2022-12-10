//
// Created by UtoKing on 2022/12/5.
//

#include "Matrix.h"
#include <iostream>
#include <immintrin.h>

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
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &matrix) {
  this->row = matrix.row;
  this->column = matrix.column;
  this->data = matrix.getData();
  return *this;
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
