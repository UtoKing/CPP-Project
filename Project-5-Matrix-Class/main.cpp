#include <iostream>
#include "src/Matrix.cpp"

using namespace std;
using namespace Mat;

int main() {
  auto *p_double = new double[12];
  auto *p_int = new int[12];
  for (int i = 0; i < 12; ++i) {
	*(p_double + i) = i;
	*(p_int + i) = i;
  }
  Matrix<double> matrix1(4, 3, p_double);
  Matrix<double> matrix2(3, 4, p_double);
  Matrix<double> matrix3 = matrix1.multiply(matrix2);
  cout << matrix3 << endl;

  cout << matrix1 << endl;
//  Matrix<double> matrix3 = matrix1 + matrix2;

  return 0;
}
