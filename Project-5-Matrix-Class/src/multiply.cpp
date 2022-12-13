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
Matrix<T> Matrix<T>::multiply(const Matrix<T> &matrix) {
  if (not this->getData()) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__
		 << ", first input is invalid."
		 << endl;
  }
  if (not matrix.getData()) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__
		 << ", second input is invalid."
		 << endl;
  }

  if (this->column != matrix.getRow()) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__
		 << ", first matrix's column doesn't match second's row."
		 << endl;
  }

  size_t r_row = this->row, r_column = matrix.getColumn(),
	  middle = this->column;

  auto *p_t = new T[r_row * r_column];
  if (p_t == nullptr) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__
		 << ", failed to allocate memory."
		 << endl;
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
}
