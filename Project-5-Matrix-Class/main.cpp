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
  Matrix<double> matrix1(4, 3, p_double);
  Matrix<double> matrix2 = matrix1.transpose();
  Tensor<double> tensor(2, 2, 3, p_double2);
  cout << tensor << endl;
  Tensor<double> tensor_1 = tensor.transpose();
  cout << tensor_1 << endl;

  return 0;
}
