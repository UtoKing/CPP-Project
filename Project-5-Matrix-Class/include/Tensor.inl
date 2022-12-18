//
// Created by UtoKing on 2022/12/13.
//

#include "Tensor.h"
#include <vector>

namespace Mat {

template<typename T>
Tensor<T>::Tensor(size_t ch, size_t r, size_t col): channel(ch), row(r), column(col) {
  shared_ptr<T> temp(new T[r * col * ch]);
  data = temp;
}

template<typename T>
Tensor<T>::Tensor(size_t ch, size_t r, size_t col, T *p_t): channel(ch), row(r), column(col) {
  shared_ptr<T> temp(p_t);
  data = temp;
}

template<typename T>
Tensor<T>::Tensor(const Tensor<T> &tensor):row(tensor.row), column(tensor.column), channel(tensor.channel) {
  data = tensor.data;
}

template<typename T>
T Tensor<T>::getElement(size_t r, size_t col, size_t ch) {
  if (not data or data.get() == nullptr) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Null pointer."
		 << endl;
	return 0;
  }
  if (r >= row or col >= column or ch >= channel) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Index out of range."
		 << endl;
	return 0;
  }

  return *(data.get() + ch * row * column + r * column + col);
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

  *(data.get() + ch * row * column + r * column + col) = t;
  return true;
}

template<typename T>
Tensor<T> &Tensor<T>::operator=(const Tensor<T> &tensor) {
  this->row = tensor.row;
  this->column = tensor.column;
  this->channel = tensor.channel;
  this->data = tensor.getData();
  return *this;
}

template<typename T>
bool Tensor<T>::operator==(const Tensor<T> &tensor) {
  if (not data) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__
		 << ", Function: " << __FUNCTION__ << endl
		 << "Error: invalid object." << endl;
	return false;
  }
  if (not tensor.getData()) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__
		 << ", Function: " << __FUNCTION__ << endl
		 << "Error: invalid input." << endl;
	return false;
  }

  if (row != tensor.getRow() or column != tensor.getColumn() or channel != tensor.getChannel()) return false;
  if (data.get() == tensor.getData().get()) return true;
  for (int i = 0; i < row * column * channel; ++i) {
	if (*(data.get() + i) != *(tensor.getData().get() + i)) return false;
  }
  return true;
}

template<typename T>
Matrix<T> Tensor<T>::operator[](size_t ch) {
  return getChannelMatrix(ch);
}

template<typename T>
const Matrix<T> &Tensor<T>::operator[](size_t ch) const {
  return getChannelMatrix(ch);
}

} // Mat