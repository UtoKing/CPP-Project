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
  cout << matrix1 << endl;
  Matrix<double> matrix2 = 1 - matrix1;
  cout << matrix2 << endl;

  return 0;
}
