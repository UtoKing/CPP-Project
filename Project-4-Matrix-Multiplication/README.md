# REPORT on PROJECT 4: Improved Matrix Multiplication

Name: MIAO Fangran

Student ID: 11911819

GitHub: https://github.com/UtoKing/CPP-Project/tree/main/Project-4-Matrix-Multiplication

---

## PART 1: Analysis

矩阵乘法：![](http://latex.codecogs.com/svg.latex?C=AB).

1. 根据矩阵乘法的定义的 implementation: 使用 ![](http://latex.codecogs.com/svg.latex?c_{ij}={\textstyle\sum_{k=0}^{n}}a_{ik}b_{kj}) 完成三重 for 循环即可。

2. **改进版的矩阵乘法**：因为矩阵相乘时第二个矩阵是提取每一列出来，因此在内存中是不连续的，读取时会花费很多时间。
而将矩阵转置也同样会花费很多的时间。
因此我们可以改变 for 循环的顺序从而让程序访问内存时是连续的。
我们先提取 A 的第一行，让第一个元素乘以 B 矩阵的第一行，第二个元素乘以 B 矩阵的第二行，以此类推，第 n 个元素乘以 B 矩阵的第 n 行。
并把所有的这些相加得到 C 矩阵的第一行。
这样访问 A 和 B 的内存空间时都是连续的了。

3. **使用 SIMD**: 主要使用了 __m256 这个类型的数据存储向量，并在改进版的矩阵乘法上完成。

4. **使用 OpenMP**: 在使用了 SIMD 的代码上加上了 OpenMP 的指令。

5. **使用 OpenBLAS**: 通过安装 OpenBLAS 的库并调用得到矩阵。

## PART 2: Code

### 矩阵乘法

```c
matrix *matmul_plain(matrix *matrix_1, matrix *matrix_2) {
  if (matrix_1 == NULL) {
	fprintf(stderr, "File %s, Line %d, Function %s: First input is invalid.\n", __FILE__, __LINE__, __FUNCTION__);
  } else if (matrix_1->data == NULL) {
	fprintf(stderr, "File %s, Line %d, Function %s: First input has invalid data.\n", __FILE__, __LINE__, __FUNCTION__);
  }

  if (matrix_2 == NULL) {
	fprintf(stderr, "File %s, Line %d, Function %s: Second input is invalid.\n", __FILE__, __LINE__, __FUNCTION__);
  } else if (matrix_2->data == NULL) {
	fprintf(stderr,
			"File %s, Line %d, Function %s: Second input has invalid data.\n",
			__FILE__,
			__LINE__,
			__FUNCTION__);
  }

  if (matrix_1->column != matrix_2->row) {
	fprintf(stderr, "Failed to perform matrix multiplication.\n");
  }

  size_t row = matrix_1->row, column = matrix_2->column,
	  middle = matrix_1->column;

  float *pFloat = (float *)malloc(row * column * sizeof(float));
  if (pFloat == NULL) {
	fprintf(stderr, "Failed to allocate memory.\n");
  }

  for (int i = 0; i < row * column; ++i) {
	size_t n_row = i / column, n_column = i % column;
	float sum = 0;
	for (int j = 0; j < middle; ++j) {
	  sum += *(matrix_1->data + n_row * middle + j) *
		  *(matrix_2->data + n_column + j * column);
	}
	*pFloat = sum;
	pFloat++;
  }
  pFloat -= row * column;
  return createMatrix(pFloat, row, column);
}
```

### 改进版矩阵乘法
```c
matrix *matmul_improved(matrix *matrix_1, matrix *matrix_2) {
  if (matrix_1 == NULL) {
	fprintf(stderr, "File %s, Line %d, Function %s: First input is invalid.\n", __FILE__, __LINE__, __FUNCTION__);
  } else if (matrix_1->data == NULL) {
	fprintf(stderr, "File %s, Line %d, Function %s: First input has invalid data.\n", __FILE__, __LINE__, __FUNCTION__);
  }

  if (matrix_2 == NULL) {
	fprintf(stderr, "File %s, Line %d, Function %s: Second input is invalid.\n", __FILE__, __LINE__, __FUNCTION__);
  } else if (matrix_2->data == NULL) {
	fprintf(stderr,
			"File %s, Line %d, Function %s: Second input has invalid data.\n",
			__FILE__,
			__LINE__,
			__FUNCTION__);
  }

  if (matrix_1->column != matrix_2->row) {
	fprintf(stderr, "Failed to perform matrix multiplication.\n");
  }

  size_t row = matrix_1->row, column = matrix_2->column,
	  middle = matrix_1->column;

  float *pFloat = (float *)malloc(row * column * sizeof(float));
  if (pFloat == NULL) {
	fprintf(stderr, "Failed to allocate memory.\n");
  }

  for (int k = 0; k < middle; ++k) {
	for (int i = 0; i < row; ++i) {
	  float r = *(matrix_1->data + i * row + k);
	  for (int j = 0; j < column; ++j) {
		*(pFloat + i * row + j) += r * *(matrix_2->data + k * middle + j);
	  }
	}
  }
  return createMatrix(pFloat, row, column);
}
```

### SIMD 矩阵乘法
```c
matrix *matmul_simd(matrix *matrix_1, matrix *matrix_2) {
  if (matrix_1 == NULL) {
	fprintf(stderr, "File %s, Line %d, Function %s: First input is invalid.\n", __FILE__, __LINE__, __FUNCTION__);
  } else if (matrix_1->data == NULL) {
	fprintf(stderr, "File %s, Line %d, Function %s: First input has invalid data.\n", __FILE__, __LINE__, __FUNCTION__);
  }

  if (matrix_2 == NULL) {
	fprintf(stderr, "File %s, Line %d, Function %s: Second input is invalid.\n", __FILE__, __LINE__, __FUNCTION__);
  } else if (matrix_2->data == NULL) {
	fprintf(stderr,
			"File %s, Line %d, Function %s: Second input has invalid data.\n",
			__FILE__,
			__LINE__,
			__FUNCTION__);
  }

  if (matrix_1->column != matrix_2->row) {
	fprintf(stderr, "Failed to perform matrix multiplication.\n");
  }

  size_t row = matrix_1->row, column = matrix_2->column,
	  middle = matrix_1->column;

  float *pFloat = (float *)malloc(row * column * sizeof(float));
  if (pFloat == NULL) {
	fprintf(stderr, "Failed to allocate memory.\n");
  }

  __m256 row_data[column / 8];
  for (int i = 0; i < row; ++i) {
	for (int j = 0; j < column / 8; ++j) {
	  row_data[j] = _mm256_setzero_ps();
	}
	for (int j = 0; j < middle; ++j) {
	  __m256 r = _mm256_set1_ps(*(matrix_1->data + i * row + j));
	  for (int k = 0; k < column / 8; ++k) {
		__m256 temp = _mm256_loadu_ps(matrix_2->data + j * middle + k * 8);
		row_data[k] = _mm256_fmadd_ps(r, temp, row_data[k]);
	  }
	}
	for (int j = 0; j < column / 8; ++j) {
	  _mm256_storeu_ps(pFloat + i * row + j * 8, row_data[j]);
	}
  }
  return createMatrix(pFloat, row, column);
}
```

### OpenMP 矩阵乘法
```c
matrix *matmul_openmp(matrix *matrix_1, matrix *matrix_2) {
  if (matrix_1 == NULL) {
	fprintf(stderr, "File %s, Line %d, Function %s: First input is invalid.\n", __FILE__, __LINE__, __FUNCTION__);
  } else if (matrix_1->data == NULL) {
	fprintf(stderr, "File %s, Line %d, Function %s: First input has invalid data.\n", __FILE__, __LINE__, __FUNCTION__);
  }

  if (matrix_2 == NULL) {
	fprintf(stderr, "File %s, Line %d, Function %s: Second input is invalid.\n", __FILE__, __LINE__, __FUNCTION__);
  } else if (matrix_2->data == NULL) {
	fprintf(stderr,
			"File %s, Line %d, Function %s: Second input has invalid data.\n",
			__FILE__,
			__LINE__,
			__FUNCTION__);
  }

  if (matrix_1->column != matrix_2->row) {
	fprintf(stderr, "Failed to perform matrix multiplication.\n");
  }

  size_t row = matrix_1->row, column = matrix_2->column,
	  middle = matrix_1->column;

  float *pFloat = (float *)malloc(row * column * sizeof(float));
  if (pFloat == NULL) {
	fprintf(stderr, "Failed to allocate memory.\n");
  }

  __m256 row_data[column / 8];
  for (int i = 0; i < row; ++i) {
	for (int j = 0; j < column / 8; ++j) {
	  row_data[j] = _mm256_setzero_ps();
	}
#pragma omp parallel for
	for (int j = 0; j < middle; ++j) {
	  __m256 r = _mm256_set1_ps(*(matrix_1->data + i * row + j));
#pragma omp parallel for
	  for (int k = 0; k < column / 8; ++k) {
		__m256 temp = _mm256_loadu_ps(matrix_2->data + j * middle + k * 8);
		row_data[k] = _mm256_fmadd_ps(r, temp, row_data[k]);
	  }
	}
	for (int j = 0; j < column / 8; ++j) {
	  _mm256_storeu_ps(pFloat + i * row + j * 8, row_data[j]);
	}
  }
  return createMatrix(pFloat, row, column);
}
```

### OpenBLAS 矩阵乘法
```c
cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m1->row, m2->column,
              m1->column, 1.0, m1->data, m1->column, m2->data, m2->column, 0.0,
              m3->data, m3->column);
```

## PART 3: Verification

以下分别测试了 $16\times16,\ 128\times128,\ 1024\times1024,\ 8192\times8192$ 时的运行时间，16k 和 64k 因为太大，内存不够所以没有进行测试。

 ****         | $16\times16$ | $128\times128$ | $1024\times1024$ | $8192\times8192$ 
:------------:|:------------:|:--------------:|:----------------:|:----------------:
 **plain**    | 0.000196s |     0.092247s  |     14.803492s    |      \\          
 **improved** | 0.000155s    |   0.109603s    |   3.496663s     |  2997.796907s   
 **SIMD**     | 0.000049s    |    0.021087s   |   0.675707s     |  351.525582s    
 **OpenMP**   | 0.000051s    |   0.019728s    |   0.724746s     |  350.796248s     
 **OpenBLAS** |0.000231s    |    0.042744s    |  0.053698s      |  3.5934 s     


