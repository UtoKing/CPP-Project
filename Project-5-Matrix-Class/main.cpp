#include <iostream>
#include "src/Matrix.cpp"

using namespace std;
using namespace Mat;

int main() {
  auto *p_double = new double[12];
  for (int i = 0; i < 12; ++i) {
	*(p_double + i) = i;
  }
  Matrix<double> matrix1(4, 3, p_double);
  Matrix<int> matrix2;
//  matrix2.getElement(0, 0);
  const Matrix<double> &matrix3(matrix1);
  Matrix<double> matrix4 = matrix1.add(matrix3);
  Matrix<double> matrix5 = matrix1 + matrix3;
  cout << matrix5 << endl;
  matrix5 = matrix5 + 1.0;
  cout << matrix5 << endl;

//  cout << matrix1 << endl;
//  cout << matrix1.getElement(2, 2) << endl;
//  matrix1.setElement(2, 2, 1000);
//  cout << matrix1 << endl;
//  Matrix<double> matrix2 = matrix1.add(matrix1);
//  cout << matrix1 << endl;
//  cout << matrix2 << endl;
//
//  matrix1.add_(matrix1);
//  cout << matrix1 << endl;
  return 0;
}
