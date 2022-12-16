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
  if (not this->data) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Invalid object."
		 << endl;
	return Matrix<T>();
  } else if (not matrix.getData()) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Input is invalid."
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
	*(p_t + i) = *(this->data.get() + i) + *(matrix.getData().get() + i);
  }
  return Matrix<T>(this->row, this->column, p_t);
}

template<typename T>
Matrix<T> Matrix<T>::add(const T &t) const {
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
	*(p_t + i) = t + *(this->data.get() + i);
  }
  return Matrix<T>(this->row, this->column, p_t);
}

template<typename T>
bool Matrix<T>::add_(const Matrix<T> &matrix) {
  if (not this->data) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Invalid object."
		 << endl;
	return false;
  } else if (not matrix.getData()) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Input is invalid."
		 << endl;
	return false;
  }
  if (this->row != matrix.getRow() or this->column != matrix.getColumn()) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Matrix of different size."
		 << endl;
	return false;
  }

  for (int i = 0; i < this->row * this->column; ++i) {
	*(this->data.get() + i) += *(matrix.getData().get() + i);
  }
  return true;
}

template<typename T>
bool Matrix<T>::add_(const T &t) {
  if (not this->data) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Invalid object."
		 << endl;
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

template<typename U, typename V>
Matrix<U> operator+(const V &v, const Matrix<U> &matrix) {
  return matrix.add(U(v));
}

template<typename T>
Matrix<T> &Matrix<T>::operator+=(const Matrix<T> &matrix) {
  this->add_(matrix);
  return *this;
}

template<typename T>
Matrix<T> &Matrix<T>::operator+=(const T &t) {
  this->add_(t);
  return *this;
}
}
