//
// Created by UtoKing on 2022/12/16.
//

#ifndef PROJECT_5_MATRIX_CLASS_INCLUDE_TENSOR_OPERATION_INL_
#define PROJECT_5_MATRIX_CLASS_INCLUDE_TENSOR_OPERATION_INL_

#include "Tensor.h"

using namespace std;

namespace Mat {
template<typename T>
Tensor<T> Tensor<T>::transpose() const {
  if (not data or data.get() == nullptr) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Invalid object."
		 << endl;
	return Tensor<T>();
  }

  auto *p_t = new T[row * column * channel];
  if (p_t == nullptr) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Failed to allocate memory."
		 << endl;
	return Tensor<T>();
  }

  for (int k = 0; k < channel; ++k) {
	Matrix<T> trans = getChannelMatrix(k).transpose();
	auto p = trans.getData().get();
	copy(p, p + row * column, p_t + k * row * column);
  }

  return Tensor<T>(channel, column, row, p_t);
}

template<typename T>
Matrix<T> Tensor<T>::getChannelMatrix(size_t ch) const {
  auto *t = new T[row * column];
  copy(data.get() + ch * row * column, data.get() + (ch + 1) * row * column, t);
  return Matrix<T>(row, column, t);
}

template<typename U>
ostream &operator<<(ostream &os, const Tensor<U> &tensor) {
  os << "[";
  for (int i = 0; i < tensor.channel; ++i) {
	if (i != 0) os << " ";
	os << tensor.getChannelMatrix(i);
	if (i != tensor.channel - 1) os << "," << endl;
  }
  os << "]";
  return os;
}

}

#endif //PROJECT_5_MATRIX_CLASS_INCLUDE_TENSOR_OPERATION_INL_
