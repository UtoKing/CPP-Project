//
// Created by UtoKing on 2022/12/16.
//

#ifndef PROJECT_5_MATRIX_CLASS_INCLUDE_TENSOR_MULTIPLY_INL_
#define PROJECT_5_MATRIX_CLASS_INCLUDE_TENSOR_MULTIPLY_INL_

#include "Tensor.h"

namespace Mat {

template<typename T>
Tensor<T> Tensor<T>::operator*(const Tensor<T> &tensor) {
  if (not this->data) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Invalid object."
		 << endl;
	return Tensor < T > ();
  }
  if (not tensor.getData()) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Invalid input."
		 << endl;
	return Tensor < T > ();
  }
  if (this->channel != tensor.getChannel() or this->column != tensor.getRow()) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Shape mismatch."
		 << endl;
	return Tensor < T > ();
  }

  auto ptr = new T[channel * row * tensor.getColumn()];
  for (int i = 0; i < channel; ++i) {
	Matrix<T> mat1 = getChannelMatrix(i);
	Matrix<T> mat2 = tensor.getChannelMatrix(i);
	Matrix<T> mat_result = mat1 * mat2;
	auto p = mat_result.getData().get();
	copy(p, p + row * tensor.getColumn(), ptr + i * row * tensor.getColumn());
  }
  return Tensor < T > (channel, row, tensor.getColumn(), ptr);
}

template<typename T>
Tensor<T> Tensor<T>::operator*(const T &t) const {
  if (not this->data) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Invalid object."
		 << endl;
	return Tensor < T > ();
  }
  auto ptr = new T[channel * row * column];
  for (int i = 0; i < channel * row * column; ++i) {
	*(ptr + i) = *(data.get() + i) * t;
  }
  return Tensor < T > (channel, row, column, ptr);
}
template<typename T>
Tensor<T> &Tensor<T>::operator*=(const Tensor<T> &tensor) {
  if (not data) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Invalid object."
		 << endl;
	return Tensor < T > ();
  }
  if (not tensor.getData()) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Input is invalid."
		 << endl;
	return Tensor < T > ();
  }

  if (this->column != tensor.getRow() or this->channel != tensor.getChannel()) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: First matrix's column doesn't match second's row."
		 << endl;
	return Tensor < T > ();
  }

  *this = *this * tensor;
  return *this;
}

template<typename T>
Tensor<T> &Tensor<T>::operator*=(const T &t) {
  if (not data) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Invalid object."
		 << endl;
	return Tensor < T > ();
  }
  *this = *this * t;
  return *this;
}

template<typename U, typename V>
Tensor<U> operator*(const V &v, const Tensor<U> &tensor) {
  return tensor * U(v);
}

template<typename T>
Tensor<T> Tensor<T>::operator*(const Matrix<T> &matrix) {
  if (not this->data) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Invalid object."
		 << endl;
	return Tensor < T > ();
  } else if (not matrix.getData()) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Input is invalid."
		 << endl;
	return Tensor < T > ();
  }
  if (column != matrix.getRow()) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Matrix of different size."
		 << endl;
	return Tensor < T > ();
  }

  auto ptr = new T[channel * row * matrix.getColumn()];
  for (int i = 0; i < channel; ++i) {
	auto channel_matrix = getChannelMatrix(i);
	auto result = channel_matrix * matrix;
	auto p = result.getData().get();
	copy(p, p + row * matrix.getColumn(), ptr + i * row * matrix.getColumn());
  }
  return Tensor < T > (channel, row, matrix.getColumn(), ptr);
}

template<typename U>
Tensor<U> operator*(const Matrix<U> &matrix, const Tensor<U> &tensor) {
  return tensor * matrix;
}

}

#endif //PROJECT_5_MATRIX_CLASS_INCLUDE_TENSOR_MULTIPLY_INL_
