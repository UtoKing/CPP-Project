//
// Created by UtoKing on 2022/12/10.
//

#include "Matrix.h"
#include <iostream>
#include <immintrin.h>

using namespace std;
namespace Mat {
//multiplication
template<typename T>
Matrix<T> Matrix<T>::multiply(const Matrix<T> &matrix) const {
  if (not this->getData()) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Invalid object."
		 << endl;
	return Matrix<T>();
  }
  if (not matrix.getData()) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Input is invalid."
		 << endl;
	return Matrix<T>();
  }

  if (this->column != matrix.getRow()) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: First matrix's column doesn't match second's row."
		 << endl;
	return Matrix<T>();
  }

  size_t r_row = this->row, r_column = matrix.getColumn(),
	  middle = this->column;

  auto *p_t = new T[r_row * r_column];
  if (p_t == nullptr) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Failed to allocate memory."
		 << endl;
	return Matrix<T>();
  }

  for (int i = 0; i < r_row; ++i) {
	for (int j = 0; j < middle; ++j) {
	  auto r = *(this->data.get() + i * middle + j);
	  for (int k = 0; k < r_column; ++k) {
		*(p_t + i * r_column + k) += r * *(matrix.getData().get() + j * r_column + k);
	  }
	}
  }
  return Matrix<T>(r_row, r_column, p_t);
}

template<typename T>
Matrix<T> Matrix<T>::multiply(const T &t) const {
  if (not this->getData()) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Invalid object."
		 << endl;
	return Matrix<T>();
  }

  auto *p_t = new T[row * column];
  if (p_t == nullptr) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Failed to allocate memory."
		 << endl;
	return Matrix<T>();
  }

  for (int i = 0; i < row * column; ++i) {
	*(p_t + i) = t * *(data.get() + i);
  }

  return Matrix<T>(row, column, p_t);
}

template<typename T>
bool Matrix<T>::multiply_(const Matrix<T> &matrix) {
  if (not data) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Invalid object."
		 << endl;
	return false;
  }
  if (not matrix.getData()) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Input is invalid."
		 << endl;
	return false;
  }

  if (this->column != matrix.getRow()) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: First matrix's column doesn't match second's row."
		 << endl;
	return false;
  }

  size_t r_row = this->row, r_column = matrix.getColumn(),
	  middle = this->column;

  for (int i = 0; i < r_row; ++i) {
	for (int j = 0; j < middle; ++j) {
	  auto r = *(this->data.get() + i * middle + j);
	  for (int k = 0; k < r_column; ++k) {
		*(data.get() + i * r_column + k) += r * *(matrix.getData().get() + j * r_column + k);
	  }
	}
  }
  return true;
}

template<typename T>
bool Matrix<T>::multiply_(const T &t) {
  if (not data) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Invalid object."
		 << endl;
	return false;
  }

  auto *p_t = new T[row * column];
  if (p_t == nullptr) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Failed to allocate memory."
		 << endl;
	return false;
  }

  for (int i = 0; i < row * column; ++i) {
	*(data.get() + i) *= t;
  }

  return true;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &matrix) {
  return this->multiply(matrix);
}
template<typename T>
Matrix<T> Matrix<T>::operator*(const T &t) const {
  return this->multiply(t);
}

template<typename U, typename V>
Matrix<U> operator*(const V &v, const Matrix<U> &matrix) {
  return matrix.multiply(U(v));
}
template<typename T>
Matrix<T> &Matrix<T>::operator*=(const Matrix<T> &matrix) {
  this->multiply_(matrix);
  return *this;
}
template<typename T>
Matrix<T> &Matrix<T>::operator*=(const T &t) {
  this->multiply_(t);
  return *this;
}

}
