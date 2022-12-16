#include "main.h"

using namespace std;
using namespace Mat;

int main() {
  auto *p_double = new double[12];
  auto *p_double2 = new double[12];
  for (int i = 0; i < 12; ++i) {
	*(p_double + i) = i;
	*(p_double2 + i) = i;
  }
  Matrix<double> matrix1(2, 6, p_double);
  Tensor<double> tensor(3, 2, 2, p_double2);
  cout << matrix1 << endl;
  cout << tensor << endl;
  tensor = tensor * matrix1;
  cout << tensor << endl;

  return 0;
}
