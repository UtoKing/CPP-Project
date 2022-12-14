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
  if (not this->data) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Invalid object."
		 << endl;
	return Matrix<T>();
  }
  if (not matrix.getData()) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Invalid input."
		 << endl;
	return Matrix<T>();
  }
  if (this->row != matrix.getRow() or this->column != matrix.getColumn()) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Matrix of different size."
		 << endl;
	return Matrix<T>();
  }

  T *p_t = new T[this->row * this->column];
  if (p_t == nullptr) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Failed to allocate memory."
		 << endl;
	return Matrix<T>();
  }
  for (int i = 0; i < this->row * this->column; ++i) {
	*(p_t + i) = *(this->data.get() + i) - *(matrix.getData().get() + i);
  }
  return Matrix<T>(this->row, this->column, p_t);
}

template<typename T>
Matrix<T> Matrix<T>::subtract(const T &t) const {
  if (not this->data) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Invalid object."
		 << endl;
	return Matrix<T>();
  }

  T *p_t = new T[this->row * this->column];
  if (p_t == nullptr) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Failed to allocate memory."
		 << endl;
	return Matrix<T>();
  }
  for (int i = 0; i < this->row * this->column; ++i) {
	*(p_t + i) = *(this->data.get() + i) - t;
  }
  return Matrix<T>(this->row, this->column, p_t);
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
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Invalid object."
		 << endl;
	return Matrix<T>();
  }

  auto *p_t = new T[matrix.getRow() * matrix.getColumn()];
  if (p_t == nullptr) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Failed to allocate memory."
		 << endl;
  }
  for (int i = 0; i < matrix.getRow() * matrix.getColumn(); ++i) {
	*(p_t + i) = v - *(matrix.data.get() + i);
  }
  return Matrix<T>(matrix.getRow(), matrix.getColumn(), p_t);
}

template<typename T>
Matrix<T> &Matrix<T>::operator-=(const Matrix<T> &matrix) {
  *this = this->subtract(matrix);
  return *this;
}

template<typename T>
Matrix<T> &Matrix<T>::operator-=(const T &t) {
  *this = this->subtract(t);
  return *this;
}

}
