//
// Created by UtoKing on 2022/12/10.
//

#include "Matrix.h"
#include <iostream>
#include <immintrin.h>

using namespace std;
namespace Mat {
//multiplication
template<>
Matrix<float> Matrix<float>::multiply(const Matrix<float> &matrix) const {
  if (not this->data) {
	cerr << "Error: Null pointer!" << endl;
  }
  if (not matrix.getData()) {
	cerr << "Error: Null pointer!" << endl;
  }

  if (this->column != matrix.getRow()) {
	cerr << "Error: Failed to perform matrix multiplication." << endl;
  }

  size_t r_row = this->row, r_column = matrix.getColumn(), middle = this->column;

  auto *p_float = new float[r_row * r_column]{};

  __m256 row_data[r_column / 8];
  for (int i = 0; i < r_row; ++i) {
	for (int j = 0; j < r_column / 8; ++j) {
	  row_data[j] = _mm256_setzero_ps();
	}
#pragma omp parallel for
	for (int j = 0; j < middle; ++j) {
	  __m256 r = _mm256_set1_ps(*(this->data.get() + i * r_row + j));
#pragma omp parallel for
	  for (int k = 0; k < r_column / 8; ++k) {
		__m256 temp = _mm256_loadu_ps(matrix.getData().get() + j * middle + k * 8);
		row_data[k] = _mm256_fmadd_ps(r, temp, row_data[k]);
	  }
	}
	for (int j = 0; j < r_column / 8; ++j) {
	  _mm256_storeu_ps(p_float + i * r_row + j * 8, row_data[j]);
	}
  }
  return Matrix<float>(r_row, r_column, p_float);
}

template<>
Matrix<double> Matrix<double>::multiply(const Matrix<double> &matrix) const {
  if (not this->data) {
	cerr << "Error: Null pointer!" << endl;
  }
  if (not matrix.getData()) {
	cerr << "Error: Null pointer!" << endl;
  }

  if (this->column != matrix.getRow()) {
	cerr << "Error: Failed to perform matrix multiplication." << endl;
  }

  size_t r_row = this->row, r_column = matrix.getColumn(), middle = this->column;

  auto *p_double = new double[r_row * r_column]{};

  __m256d row_data[r_column / 4];
  for (int i = 0; i < r_row; ++i) {
	for (int j = 0; j < r_column / 4; ++j) {
	  row_data[j] = _mm256_setzero_pd();
	}
#pragma omp parallel for
	for (int j = 0; j < middle; ++j) {
	  __m256d r = _mm256_set1_pd(*(this->data.get() + i * r_row + j));
#pragma omp parallel for
	  for (int k = 0; k < r_column / 4; ++k) {
		__m256d temp = _mm256_loadu_pd(matrix.getData().get() + j * middle + k * 4);
		row_data[k] = _mm256_fmadd_pd(r, temp, row_data[k]);
	  }
	}
	for (int j = 0; j < r_column / 4; ++j) {
	  _mm256_storeu_pd(p_double + i * r_row + j * 4, row_data[j]);
	}
  }
  return Matrix<double>(r_row, r_column, p_double);
}
}
