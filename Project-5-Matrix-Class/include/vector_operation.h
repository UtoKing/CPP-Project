//
// Created by UtoKing on 2022/12/16.
//

#ifndef PROJECT_5_MATRIX_CLASS_INCLUDE_VECTOR_OPERATION_H_
#define PROJECT_5_MATRIX_CLASS_INCLUDE_VECTOR_OPERATION_H_

#include <vector>
#include <iostream>
#include <iterator>

template<typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &v) {
  if (!v.empty()) {
	out << '[';
	std::copy(v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
	out << "\b\b]";
  }
  return out;
}

#endif //PROJECT_5_MATRIX_CLASS_INCLUDE_VECTOR_OPERATION_H_
