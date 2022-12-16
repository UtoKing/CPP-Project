//
// Created by UtoKing on 2022/12/16.
//

#ifndef PROJECT_5_MATRIX_CLASS_INCLUDE_TENSOR_SUBTRACT_INL_
#define PROJECT_5_MATRIX_CLASS_INCLUDE_TENSOR_SUBTRACT_INL_

#include "Tensor.h"

namespace Mat {

template<typename T>
Tensor<T> Tensor<T>::operator-(const Tensor<T> &tensor) {
  if (not this->data) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Invalid object."
		 << endl;
	return Tensor<T>();
  }
  if (not tensor.getData()) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Invalid input."
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
	return Tensor<T>();
  }
  for (int i = 0; i < channel * row * column; ++i) {
	*(p_t + i) = *(this->data.get() + i) - *(tensor.getData().get() + i);
  }
  return Tensor<T>(channel, row, column, p_t);
}

template<typename T>
Tensor<T> Tensor<T>::operator-(const Matrix<T> &matrix) {
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
	auto this_matrix = getChannelMatrix(i);
	auto result = this_matrix - matrix;
	auto p = result.getData().get();
	copy(p, p + row * column, ptr + i * row * column);
  }
  return Tensor<T>(channel, row, column, ptr);
}

template<typename T>
Tensor<T> Tensor<T>::operator-(const T &t) {
  if (not this->data) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Invalid object."
		 << endl;
	return Tensor<T>();
  }

  T *p_t = new T[channel * row * column];
  if (p_t == nullptr) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Failed to allocate memory."
		 << endl;
	return Tensor<T>();
  }
  for (int i = 0; i < channel * row * column; ++i) {
	*(p_t + i) = *(this->data.get() + i) - t;
  }
  return Tensor<T>(this->row, this->column, p_t);
}

template<typename T>
Tensor<T> &Tensor<T>::operator-=(const Tensor<T> &tensor) {
  *this = *this - tensor;
  return *this;
}

template<typename T>
Tensor<T> &Tensor<T>::operator-=(const Matrix<T> &matrix) {
  *this = *this - matrix;
  return *this;
}

template<typename T>
Tensor<T> &Tensor<T>::operator-=(const T &t) {
  *this = *this - t;
  return *this;
}

template<typename U, typename V>
Tensor<U> operator-(const V &v, const Tensor<U> &tensor) {
  if (not tensor.data) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Invalid object."
		 << endl;
	return Tensor<U>();
  }

  auto *p_t = new U[tensor.getChannel() * tensor.getRow() * tensor.getColumn()];
  if (p_t == nullptr) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Failed to allocate memory."
		 << endl;
  }
  for (int i = 0; i < tensor.getRow() * tensor.getColumn() * tensor.getChannel(); ++i) {
	*(p_t + i) = v - *(tensor.data.get() + i);
  }
  return Matrix<U>(tensor.getChannel(), tensor.getRow(), tensor.getColumn(), p_t);
}

template<typename U>
Tensor<U> operator-(const Matrix<U> &matrix, const Tensor<U> &tensor) {
  if (not tensor.data) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Invalid object."
		 << endl;
	return Tensor<U>();
  } else if (not matrix.getData()) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Input is invalid."
		 << endl;
	return Tensor<U>();
  }
  if (tensor.getRow() != matrix.row or tensor.getColumn() != matrix.column) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Matrix of different size."
		 << endl;
	return Tensor<U>();
  }

  size_t channel = tensor.getChannel();
  size_t row = tensor.getRow();
  size_t column = tensor.getColumn();

  auto ptr = new U[channel * row * column];
  for (int i = 0; i < channel; ++i) {
	auto this_matrix = tensor[i];
	auto result = matrix - this_matrix;
	auto p = result.getData().get();
	copy(p, p + row * column, ptr + i * row * column);
  }
  return Tensor<U>(channel, row, column, ptr);
}

}

#endif //PROJECT_5_MATRIX_CLASS_INCLUDE_TENSOR_SUBTRACT_INL_
