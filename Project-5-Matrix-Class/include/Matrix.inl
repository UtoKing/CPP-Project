//
// Created by UtoKing on 2022/12/5.
//

#include <iostream>

#include "Matrix.h"

using namespace std;
namespace Mat {

template <typename T>
T Matrix<T>::getElement(size_t r, size_t c) {
  if (not data) {
    cerr << "File: " << __FILE__ << ", Line: " << __LINE__
         << ", Function: " << __FUNCTION__ << endl
         << "Error: Null pointer." << endl;
    return 0;
  }
  if (r >= this->row or c >= this->column) {
    cerr << "File: " << __FILE__ << ", Line: " << __LINE__
         << ", Function: " << __FUNCTION__ << endl
         << "Error: Index out of range." << endl;
    return 0;
  }

  return *(this->data.get() + r * column + c);
}

template <typename T>
bool Matrix<T>::setElement(size_t r, size_t c, const T &t) {
  if (not this->data) {
    cerr << "File: " << __FILE__ << ", Line: " << __LINE__
         << ", Function: " << __FUNCTION__ << endl
         << "Error: Null pointer." << endl;
    return false;
  }
  if (r >= this->row or c >= this->column) {
    cerr << "File: " << __FILE__ << ", Line: " << __LINE__
         << ", Function: " << __FUNCTION__ << endl
         << "Error: Index out of range." << endl;
    return false;
  }

  *(this->data.get() + r * this->column + c) = t;
  return true;
}

template <typename T>
vector<T> Matrix<T>::operator[](size_t r) {
  vector<T> v(column);
  for (int i = 0; i < column; ++i) {
    v[i] = *(data.get() + r * column + i);
  }
  return v;
}

template <typename T>
const vector<T> &Matrix<T>::operator[](size_t r) const {
  vector<T> v(column);
  for (int i = 0; i < column; ++i) {
    v[i] = *(data.get() + r * column + i);
  }
  return v;
}

template <typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &matrix) {
  this->row = matrix.row;
  this->column = matrix.column;
  this->data = matrix.getData();
  return *this;
}

template <typename T>
bool Matrix<T>::operator==(const Matrix<T> &matrix) {
  if (not data) {
    cerr << "File: " << __FILE__ << ", Line: " << __LINE__
         << ", Function: " << __FUNCTION__ << endl
         << "Error: invalid object." << endl;
    return false;
  }
  if (not matrix.getData()) {
    cerr << "File: " << __FILE__ << ", Line: " << __LINE__
         << ", Function: " << __FUNCTION__ << endl
         << "Error: invalid input." << endl;
    return false;
  }

  if (row != matrix.getRow() or column != matrix.getColumn()) return false;
  if (data.get() == matrix.getData().get()) return true;
  bool b = true;
  for (int i = 0; i < row * column; ++i) {
    if (*(data.get() + i) != *(matrix.getData().get() + i)) b = false;
  }
  return b;
}

template <typename T>
ostream &operator<<(ostream &os, const Matrix<T> &matrix) {
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
  os << ']';
  return os;
}

}  // namespace Mat
