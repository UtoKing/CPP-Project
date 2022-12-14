//
// Created by UtoKing on 2022/12/13.
//

#include "Matrix.h"

namespace Mat {
template<typename T>
Matrix<T> Matrix<T>::transpose() const {
  auto *p_t = new T[row * column];
  if (not data) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Invalid object."
		 << endl;
	return Matrix<T>();
  }

  for (int i = 0; i < row; ++i) {
	for (int j = 0; j < column; ++j) {
	  *(p_t + j * row + i) = *(data.get() + i * column + j);
	}
  }
  return Matrix<T>(column, row, p_t);
}
}
