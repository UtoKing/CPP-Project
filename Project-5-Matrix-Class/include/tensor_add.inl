//
// Created by UtoKing on 2022/12/16.
//

#ifndef PROJECT_5_MATRIX_CLASS_INCLUDE_TENSOR_ADD_INL_
#define PROJECT_5_MATRIX_CLASS_INCLUDE_TENSOR_ADD_INL_

#include "Tensor.h"

namespace Mat {

template<typename T>
Tensor<T> Tensor<T>::operator+(const T &t) {
  if (not this->data) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Invalid object."
		 << endl;
	return Matrix<T>();
  }

  T *p_t = new T[row * column * channel];
  if (p_t == nullptr) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Failed to allocate memory."
		 << endl;
	return Matrix<T>();
  }
  for (int i = 0; i < row * column * channel; ++i) {
	*(p_t + i) = t + *(this->data.get() + i);
  }
  return Matrix<T>(channel, row, column, p_t);
}

template<typename T>
Tensor<T> Tensor<T>::operator+(const Tensor<T> &tensor) {
  if (not this->data) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Invalid object."
		 << endl;
	return Tensor<T>();
  } else if (not tensor.getData()) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Input is invalid."
		 << endl;
	return Tensor<T>();
  }
  if (this->row != tensor.getRow() or this->column != tensor.getColumn() or this->channel != tensor.getChannel()) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Matrix of different size."
		 << endl;
	return Tensor<T>();
  }

  T *p_t = new T[channel * row * column];
  if (p_t == nullptr) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Failed to allocate memory."
		 << endl;
	return Matrix<T>();
  }
  for (int i = 0; i < channel * row * column; ++i) {
	*(p_t + i) = *(this->data.get() + i) + *(tensor.getData().get() + i);
  }
  return Matrix<T>(channel, row, column, p_t);
}

template<typename T>
Tensor<T> Tensor<T>::operator+(const Matrix<T> &matrix) {
  if (not this->data) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Invalid object."
		 << endl;
	return Tensor<T>();
  } else if (not matrix.getData()) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Input is invalid."
		 << endl;
	return Tensor<T>();
  }
  if (this->row != matrix.row or this->column != matrix.column) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Matrix of different size."
		 << endl;
	return Tensor<T>();
  }

  auto ptr = new T[channel * row * column];
  for (int i = 0; i < channel; ++i) {
	auto channel_matrix = getChannelMatrix(i);
	auto result = channel_matrix + matrix;
	auto p = result.getData().get();
	copy(p, p + row * column, ptr + i * row * column);
  }
  return Tensor<T>(channel, row, column, ptr);
}

template<typename T>
Tensor<T> &Tensor<T>::operator+=(const T &t) {
  *this = *this + t;
  return *this;
}

template<typename T>
Tensor<T> &Tensor<T>::operator+=(const Tensor<T> &tensor) {
  *this = *this + tensor;
  return *this;
}

template<typename T>
Tensor<T> &Tensor<T>::operator+=(const Matrix<T> &matrix) {
  *this = *this + matrix;
  return *this;
}

template<typename U, typename V>
Tensor<U> operator+(const V &v, const Tensor<U> &tensor) {
  return tensor + U(v);
}

template<typename U>
Tensor<U> operator+(const Matrix<U> &matrix, const Tensor<U> &tensor) {
  return tensor + matrix;
}

}

#endif //PROJECT_5_MATRIX_CLASS_INCLUDE_TENSOR_ADD_INL_
