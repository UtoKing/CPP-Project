#include "include/main.h"

int main() {
  size_t n = 1024;
  printf(".");
  float p1[n];
  for (int i = 0; i < n * n; ++i) {
    *(p1 + i) = (float)(rand() % 10);
  }
  float p2[n];
  for (int i = 0; i < n * n; ++i) {
    *(p2 + i) = (float)(rand() % 10);
  }

  matrix *m1 = createMatrix(p1, n, n);
  matrix *m2 = createMatrix(p2, n, n);

  clock_t start, stop;
  matrix *m3;
  double duration;

  // start = clock();
  // m3 = matmul_plain(m1, m2);
  // stop = clock();
  // printf("First element: %f\n", *(m3->data));
  // duration = (double)(stop - start) / CLOCKS_PER_SEC;
  // printf("%f\n", duration);

  // start = clock();
  // m3 = matmul_improved(m1, m2);
  // stop = clock();
  // printf("First element: %f\n", *(m3->data));
  // duration = (double)(stop - start) / CLOCKS_PER_SEC;
  // printf("%f\n", duration);

  start = clock();
  m3 = matmul_simd(m1, m2);
  stop = clock();
  printf("First element: %f\n", *(m3->data));
  duration = (double)(stop - start) / CLOCKS_PER_SEC;
  printf("%f\n", duration);

  return 0;
}
