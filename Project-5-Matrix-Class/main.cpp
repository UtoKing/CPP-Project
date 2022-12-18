#include "main.h"

using namespace std;
using namespace Mat;

int main() {
  auto *p_double = new double[24];
  for (int i = 0; i < 24; ++i) {
	*(p_double + i) = i;
  }
  Tensor<double> tensor(2, 3, 4, p_double);
  cout << "tensor=\n" << tensor << endl;
  cout << "tensor's shape: " << "channel: " << tensor.getChannel() << " row: " << tensor.getRow() << " Column: "
	   << tensor.getColumn() << endl;

  cout << "Copy constructor and assignment:" << endl;
  auto tensor2(tensor);
  auto tensor3 = tensor;
  cout << "tensor2[0]=\n" << tensor2[0] << endl;
  cout << "tensor3[1]=\n" << tensor3[1] << endl;

  cout << "Transpose" << endl;
  auto tensor4 = tensor.transpose();
  cout << tensor4 << endl;

  cout << "Addition" << endl;
  auto tensor5 = tensor + 1;
  cout << "tensor+1=\n" << tensor5 << endl;

  cout << "Multiplication" << endl;
  auto tensor6 = tensor * tensor.transpose();
  cout << "tensor * tensor's transpose=\n" << tensor6 << endl;

  cout << "Extract specific location's element:" << endl;
  cout << "tensor6[0][1][2]=" << tensor6[0][1][2] << endl;

  return 0;
}
