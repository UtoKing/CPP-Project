#include "include/main.h"

int timeuse;
struct timeval start, end;
char name;

#define TIME_START gettimeofday(&start, NULL);
#define TIME_END(name)                                                     \
  gettimeofday(&end, NULL);                                                \
  timeuse =                                                                \
      1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec; \
  printf("%s: %.4f s\n", name, ((float)timeuse / 1000000.0f));

int main() {
  size_t n = 8192;
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
  matrix *m3 = createMatrix(p1, n, n);

  TIME_START
  m3 = matmul_plain(m1, m2);
  TIME_END("Plain")
  printf("First five element: %f, %f, %f, %f, %f,\n", *(m3->data),
         *(m3->data + 1), *(m3->data + 2), *(m3->data + 3), *(m3->data + 4));

  TIME_START
  m3 = matmul_improved(m1, m2);
  TIME_END("Improved")
  printf("First five element: %f, %f, %f, %f, %f,\n", *(m3->data),
         *(m3->data + 1), *(m3->data + 2), *(m3->data + 3), *(m3->data + 4));

  TIME_START
  m3 = matmul_simd(m1, m2);
  TIME_END("SIMD")
  printf("First five element: %f, %f, %f, %f, %f,\n", *(m3->data),
         *(m3->data + 1), *(m3->data + 2), *(m3->data + 3), *(m3->data + 4));

  TIME_START
  m3 = matmul_openmp(m1, m2);
  TIME_END("OpenMP")
  printf("First five element: %f, %f, %f, %f, %f,\n", *(m3->data),
         *(m3->data + 1), *(m3->data + 2), *(m3->data + 3), *(m3->data + 4));

  TIME_START
  cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m1->row, m2->column,
              m1->column, 1.0, m1->data, m1->column, m2->data, m2->column, 0.0,
              m3->data, m3->column);
  TIME_END("OpenBLAS")
  printf("First five element: %f, %f, %f, %f, %f,\n", *(m3->data),
         *(m3->data + 1), *(m3->data + 2), *(m3->data + 3), *(m3->data + 4));

  deleteMatrix(m1);
  deleteMatrix(m2);
  deleteMatrix(m3);

  return 0;
}
