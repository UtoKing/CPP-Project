//
// Created by UtoKing on 2022/12/10.
//

#include <iostream>
#include <immintrin.h>

using namespace std;
namespace Mat {
//multiplication

Matrix<float> matmul_openmp(const Matrix<float> &matrix_1, const Matrix<float> &matrix_2) {
  size_t row = matrix_1.getRow(), column = matrix_2.getColumn(),
	  middle = matrix_1.getColumn();

  auto pFloat = new float[row * column];

  __m256 row_data[column / 8];
  for (int i = 0; i < row; ++i) {
	for (int j = 0; j < column / 8; ++j) {
	  row_data[j] = _mm256_setzero_ps();
	}
#pragma omp parallel for
	for (int j = 0; j < middle; ++j) {
	  __m256 r = _mm256_set1_ps(*(matrix_1.getData().get() + i * row + j));
#pragma omp parallel for
	  for (int k = 0; k < column / 8; ++k) {
		__m256 temp = _mm256_loadu_ps(matrix_2.getData().get() + j * middle + k * 8);
		row_data[k] = _mm256_fmadd_ps(r, temp, row_data[k]);
	  }
	}
	for (int j = 0; j < column / 8; ++j) {
	  _mm256_storeu_ps(pFloat + i * row + j * 8, row_data[j]);
	}
  }
  return {row, column, pFloat};
}

template<>
Matrix<float> Matrix<float>::multiply(const Matrix<float> &matrix) const {
  if (not this->getData()) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Invalid object."
		 << endl;
	return Matrix<float>();
  }
  if (not matrix.getData()) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Input is invalid."
		 << endl;
	return Matrix<float>();
  }

  if (this->column != matrix.getRow()) {
	cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __FUNCTION__ << endl
		 << "Error: Shape mismatch."
		 << endl;
	return Matrix<float>();
  }

  size_t r_row = this->row, r_column = matrix.getColumn(),
	  middle = this->column;

  if (column % 8 == 0)
	return matmul_openmp(*this, matrix);

  auto *p_t = new float[r_row * r_column];

  for (int i = 0; i < r_row; ++i) {
	for (int j = 0; j < middle; ++j) {
	  auto r = *(this->data.get() + i * middle + j);
	  for (int k = 0; k < r_column; ++k) {
		*(p_t + i * r_column + k) += r * *(matrix.getData().get() + j * r_column + k);
	  }
	}
  }
  return {r_row, r_column, p_t};
}

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
		 << "Error: Shape mismatch."
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
  *this = this->multiply(matrix);
  return *this;
}

template<typename T>
Matrix<T> &Matrix<T>::operator*=(const T &t) {
  *this = this->multiply(t);
  return *this;
}

}
