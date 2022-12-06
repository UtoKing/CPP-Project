//
// Created by UtoKing on 2022/12/5.
//

#include "Matrix.h"
#include <iostream>
//#include <string>

using namespace std;


template<typename T>
T Matrix<T>::getElement(size_t r, size_t c) {
  if (r >= this->row or c >= this->column) {
	cerr << "Error: Indices out of range!" << endl;
	return 0;
  }
  return *(this->data.get() + r * this->column + c);
}

template<typename T>
bool Matrix<T>::setElement(size_t r, size_t c, T t) {
  if (r >= this->row or c >= this->column) {
	cerr << "Error: Indices out of range!" << endl;
	return false;
  }
  *(this->data.get() + r * this->column + c) = t;
  return true;
}

