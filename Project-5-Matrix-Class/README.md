# REPORT on Project 5 Matrix Class

Name: MIAO Fangran

Student ID: 11911819

## PART 1: Analysis

本次 project 需要我们生成的矩阵类包含三个维度：通道，行和列。
因为要应对不同的数据类型，所以使用了类模板。

首先我创建了一个常规的矩阵类，Matrix, 只包含行和列以及数据。
其中数据使用了 `shared_ptr` 进行存储，使得这些矩阵在拷贝时为软拷贝。
虽然这个矩阵类的目的是为了方便做矩阵运算，但还是添加了矩阵加法和减法等一系列的功能。
> 注：本次 project 并没有去实现矩阵的元素乘积。

常规矩阵类实现了这些运算符的重载：+, -, *, +=, -=, *=.
其中这些运算符不仅可以跟相同类型的矩阵类做运算，还可以和单独的一个元素进行运算。
例如 `A+1` 则为每个元素都加上 1.

同时实现的还有下标运算符 `[]`, 该操作符会提取某一行的数据存于一个 vector 中。
因此你也可以 `A[0][1]` 来提取第 0 行，第 1 列的数据。

此外，矩阵类还实现了转置操作，此操作会实现一个新的矩阵。

这个矩阵类并没有实现求行列式，求逆等操作，因为这些操作需要相应的算法，并且时间复杂度也很高，所以现阶段难以实现。

---
在实现了常规的矩阵类之后我们就可以实现带通道的矩阵类，将这一矩阵类命名为 Tensor.
Tensor 的加减操作还是由本身的 data 自己加减实现。
而乘法操作就可以借助创建的 Matrix 类实现。
Tensor 的相乘要求两个 Tensor 的通道数相等，且每个通道的矩阵可以相乘。
单个通道就退化回了 Matrix 类，因此可以调用 Matrix 的乘法方法。

之后还是和之前一样实现了下标运算符，通过 `[]` 来提取某一个通道的数据。
同样可以通过 `A[0][1][2]` 来提取第 0 通道，第 1 行，第 2 列的数据。

此外通过重载 `<<` 实现了对 Matrix 以及 Tensor 的输出。

---
矩阵的加速实现按照了上一次的 Project，但是也有其局限性。
因为要求矩阵必须为 8 的倍数。
因此如果在类型为 float 且 第二个矩阵的列数为 8 的倍数时，生成了一个特例化的模板函数，来实现矩阵的加速。

## PART 2: Code
因本次的代码量较大，只会放一部分代码进行展示，其他可以在 `include` 文件夹中查看。
每个文件的命名都是相应的 Matrix 或 Tensor 的操作。

**Tensor 的构造函数**

```c++
template<typename T>
Tensor<T>::Tensor(size_t ch, size_t r, size_t col): channel(ch), row(r), column(col) {
  shared_ptr<T> temp(new T[r * col * ch]);
  data = temp;
}

template<typename T>
Tensor<T>::Tensor(size_t ch, size_t r, size_t col, T *p_t): channel(ch), row(r), column(col) {
  shared_ptr<T> temp(p_t);
  data = temp;
}

template<typename T>
Tensor<T>::Tensor(const Tensor<T> &tensor):row(tensor.row), column(tensor.column), channel(tensor.channel) {
  data = tensor.data;
}
```

**Tensor 的提取通道及重载 `[]`**

```c++
template<typename T>
Matrix<T> Tensor<T>::getChannelMatrix(size_t ch) const {
  auto *t = new T[row * column];
  copy(data.get() + ch * row * column, data.get() + (ch + 1) * row * column, t);
  return Matrix<T>(row, column, t);
}

template<typename T>
Matrix<T> Tensor<T>::operator[](size_t ch) {
  return getChannelMatrix(ch);
}

template<typename T>
const Matrix<T> &Tensor<T>::operator[](size_t ch) const {
  return getChannelMatrix(ch);
}
```

**Matrix 的 `<<` 的重载和 Tensor 的 `<<` 的重载**

```c++
template<typename T>
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

template<typename U>
ostream &operator<<(ostream &os, const Tensor<U> &tensor) {
  os << "[";
  for (int i = 0; i < tensor.channel; ++i) {
	if (i != 0) os << " ";
	os << tensor.getChannelMatrix(i);
	if (i != tensor.channel - 1) os << "," << endl;
  }
  os << "]";
  return os;
}
```

## PART 3: Verification

以下为运行 `main.cpp` 的输出。

```text
tensor=
[[[0, 1, 2, 3]
 [4, 5, 6, 7]
 [8, 9, 10, 11]],
 [[12, 13, 14, 15]
 [16, 17, 18, 19]
 [20, 21, 22, 23]]]
tensor's shape: channel: 2 row: 3 Column: 4
Copy constructor and assignment:
tensor2[0]=
[[0, 1, 2, 3]
 [4, 5, 6, 7]
 [8, 9, 10, 11]]
tensor3[1]=
[[12, 13, 14, 15]
 [16, 17, 18, 19]
 [20, 21, 22, 23]]
Transpose
[[[0, 4, 8]
 [1, 5, 9]
 [2, 6, 10]
 [3, 7, 11]],
 [[12, 16, 20]
 [13, 17, 21]
 [14, 18, 22]
 [15, 19, 23]]]
Addition
tensor+1=
[[[1, 2, 3, 4]
 [5, 6, 7, 8]
 [9, 10, 11, 12]],
 [[13, 14, 15, 16]
 [17, 18, 19, 20]
 [21, 22, 23, 24]]]
Multiplication
tensor * tensor's transpose=
[[[14, 38, 62]
 [38, 126, 214]
 [62, 214, 366]],
 [[734, 950, 1228]
 [988, 1356, 1724]
 [1228, 1724, 2220]]]
Extract specific location's element:
tensor6[0][1][2]=214
```
