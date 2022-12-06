#include <iostream>
#include "src/Matrix.cpp"

using namespace std;

int main() {
  auto *p_double = new double[12];
  for (int i = 0; i < 12; ++i) {
	*(p_double + i) = i;
  }
  Matrix<double> matrix1(4, 3, p_double);
  cout << matrix1 << endl;
  cout << matrix1.getElement(2, 2) << endl;
  matrix1.setElement(2,2,1000);
  cout << matrix1 << endl;
  return 0;
}
