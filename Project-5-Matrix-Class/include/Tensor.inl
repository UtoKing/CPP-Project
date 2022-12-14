//
// Created by UtoKing on 2022/12/13.
//

#include "Tensor.h"

namespace Mat {

template<typename T>
Tensor<T>::Tensor(size_t r, size_t col, size_t ch):channel(ch) {
  auto *temp = new Matrix<T>[ch];
  for (int i = 0; i < ch; ++i) {
	Matrix<T> matrix(r, col);
	*(temp + i) = matrix;
  }
  shared_ptr<Matrix<T>> t(temp);
  data = t;
}

template<typename T>
Tensor<T>::Tensor(size_t r, size_t col, size_t ch, T *p_t):channel(ch) {
  auto *temp = new Matrix<T>[ch];
  for (int i = 0; i < ch; ++i) {
	Matrix<T> matrix(r, col, p_t + i * r * col);
	*(temp + i) = matrix;
  }
  shared_ptr<Matrix<T>> t(temp);
  data = t;
}

template<typename T>
T Tensor<T>::getElement(size_t r, size_t col, size_t ch) {
  if (not data or data.get() == nullptr) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Null pointer."
		 << endl;
	return 0;
  }
  if (r >= this->getRow() or col >= this->getColumn() or ch >= channel) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Index out of range."
		 << endl;
	return 0;
  }

  return (data.get()+ch)->getElement(r, col);
}

template<typename T>
bool Tensor<T>::setElement(size_t r, size_t col, size_t ch, const T &t) {
  if (not data or data.get() == nullptr) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Null pointer."
		 << endl;
	return false;
  }
  if (r >= this->getRow() or col >= this->getColumn() or ch >= channel) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Index out of range."
		 << endl;
	return false;
  }

  (data.get() + ch)->setElement(r, col, t);
  return true;
}

template<typename T>
Tensor<T> Tensor<T>::transpose() const {
  auto row = this->getRow();
  auto column = this->getColumn();
  if (not data or data.get() == nullptr) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Invalid object."
		 << endl;
	return Tensor<T>();
  }

  auto *p_t = new T[row * column * channel];
  if (p_t== nullptr){
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Failed to allocate memory."
		 << endl;
	return Tensor<T>();
  }
  for (int k = 0; k < channel; ++k) {
	for (int i = 0; i < row; ++i) {
	  for (int j = 0; j < column; ++j) {
		*(p_t + k * row * column + j * row + i) = *((data.get() + k)->getData().get() + i * column + j);
	  }
	}
  }

  return Tensor<T>(row, column, channel, p_t);
}

template<typename U>
ostream &operator<<(ostream &os, const Tensor<U> &tensor) {
  os << "[";
  for (int i = 0; i < tensor.channel; ++i) {
	if (i != 0) os << " ";
	os << *(tensor.data.get() + i);
	if (i != tensor.channel - 1) os << "," << endl;
  }
  os << "]";
  return os;
}
} // Mat