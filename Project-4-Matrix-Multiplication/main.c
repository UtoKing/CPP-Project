#include "include/main.h"

int main() {
  size_t n = 4096;
  float *p1 = malloc(n * n * sizeof(float));
  for (int i = 0; i < n * n; ++i) {
	*(p1 + i) = (float)(rand() % 10);
  }
  float *p2 = malloc(n * n * sizeof(float));
  for (int i = 0; i < n * n; ++i) {
	*(p2 + i) = (float)(rand() % 10);
  }

  matrix *m1 = createMatrix(p1, n, n);
  matrix *m2 = createMatrix(p2, n, n);

  clock_t start, stop;
  matrix *m3;
  double duration;

//   start = clock();
//   m3 = matmul_plain(m1, m2);
//   stop = clock();
//   printf("First element: %f\n", *(m3->data));
//   duration = (double)(stop - start) / CLOCKS_PER_SEC;
//   printf("%f\n", duration);

//  start = clock();
//  m3 = matmul_improved(m1, m2);
//  stop = clock();
//  printf("First five element: %f, %f, %f, %f, %f,\n",
//		 *(m3->data),
//		 *(m3->data + 1),
//		 *(m3->data + 2),
//		 *(m3->data + 3),
//		 *(m3->data + 4));
//  duration = (double)(stop - start) / CLOCKS_PER_SEC;
//  printf("Improved Plain Time: %fs\n", duration);

  start = clock();
  m3 = matmul_simd(m1, m2);
  stop = clock();
  printf("First five element: %f, %f, %f, %f, %f,\n",
		 *(m3->data),
		 *(m3->data + 1),
		 *(m3->data + 2),
		 *(m3->data + 3),
		 *(m3->data + 4));
  duration = (double)(stop - start) / CLOCKS_PER_SEC;
  printf("SIMD Time: %fs\n", duration);

  start = clock();
  m3 = matmul_openmp(m1, m2);
  stop = clock();
  printf("First five element: %f, %f, %f, %f, %f,\n",
		 *(m3->data),
		 *(m3->data + 1),
		 *(m3->data + 2),
		 *(m3->data + 3),
		 *(m3->data + 4));
  duration = (double)(stop - start) / CLOCKS_PER_SEC;
  printf("OpenMP Time: %fs\n", duration);

  start = clock();
  cblas_sgemm(CblasRowMajor,
			  CblasNoTrans,
			  CblasNoTrans,
			  m1->row,
			  m2->column,
			  m1->column,
			  1.0,
			  m1->data,
			  m1->column,
			  m2->data,
			  m2->column,
			  0.0,
			  m3->data,
			  m3->column);
  stop = clock();
  printf("First five element: %f, %f, %f, %f, %f,\n",
		 *(m3->data),
		 *(m3->data + 1),
		 *(m3->data + 2),
		 *(m3->data + 3),
		 *(m3->data + 4));
  duration = (double)(stop - start) / CLOCKS_PER_SEC;
  printf("OpenBLAS Time: %fs\n", duration);

  deleteMatrix(m1);
  deleteMatrix(m2);
  deleteMatrix(m3);

  return 0;
}
