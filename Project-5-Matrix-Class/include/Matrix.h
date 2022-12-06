//
// Created by UtoKing on 2022/12/2.
//

#ifndef PROJECT_5_MATRIX_CLASS_INCLUDE_MATRIX_H_
#define PROJECT_5_MATRIX_CLASS_INCLUDE_MATRIX_H_

#include <memory>
#include <iostream>

using namespace std;

template<typename T>
class Matrix {
 private:
  shared_ptr<T> data;

 public:
  size_t row, column;
  Matrix() : row(0), column(0) {
	data(nullptr);
  }
  Matrix(size_t r, size_t c) : row(r), column(c) {
	data.get() = new T[r * c];
  }
  Matrix(size_t r, size_t c, T *p_t) : row(r), column(c) {
	shared_ptr<T> temp(p_t);
	data = temp;
  }
  Matrix(const Matrix &matrix) : row(matrix.row), column(matrix.column) {
	this->data(matrix.data);
  }

  shared_ptr<T> getData() const { return data; }

  T getElement(size_t r, size_t c);
  bool setElement(size_t r, size_t c, T t);

  friend ostream &operator<<(ostream &os, const Matrix<T> &matrix) {
	os << '[';
	shared_ptr<T> p_c = matrix.getData();
	for (size_t j = 0; j < matrix.row; ++j) {
	  if (j != 0) os << ' ';
	  os << '[';
	  for (size_t k = 0; k < matrix.column; ++k) {
		os << *(p_c.get() + j * (matrix.column) + k);
		if (k < matrix.column - 1) os << ", ";
	  }
	  os << ']';
	  if (j < matrix.row - 1) os << endl;
	}
	os << ']' << endl;
	return os;
  }
}; // Mat

#endif //PROJECT_5_MATRIX_CLASS_INCLUDE_MATRIX_H_
