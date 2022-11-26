//
// Created by UtoKing on 2022/10/19.
//

//#include <avxintrin.h>
#include "matrixOperation.h"

#include <immintrin.h>

void printMatrix(matrix *m) {
  size_t row = m->row, column = m->column;
  float *pFloat = m->data;

  printf("Matrix: [\n");
  for (int i = 0; i < row * column; ++i) {
    printf("%f", *pFloat);
    pFloat++;
    if ((i + 1) % column == 0) {
      printf("\n");
    } else {
      printf(",");
    }
  }
  printf("]\n");
}

matrix *createMatrix(float *data, size_t row, size_t column) {
  matrix *m = NULL;

  if (data == NULL) {
    fprintf(stderr, "Input data is Invalid");
  }

  if (row == 0 || column == 0) {
    fprintf(stderr, "row or/and column is 0.\n");
    return NULL;
  }

  m = (matrix *)malloc(sizeof(matrix));

  if (m == NULL) {
    fprintf(stderr, "Failed to allocate memory.\n");
    return NULL;
  }
  m->row = row;
  m->column = column;
  m->data = (float *)malloc(sizeof(float) * row * column);

  if (m->data == NULL) {
    fprintf(stderr, "Failed to allocate memory.\n");
    free(m);
    return NULL;
  }

  float *pFloat = m->data;
  for (int i = 0; i < row * column; ++i) {
    *pFloat = *data;
    pFloat++;
    data++;
  }
  return m;
}

bool deleteMatrix(matrix *m) {
  if (m == NULL) return false;
  if (m->data) free(m->data);
  free(m);
  return true;
}

matrix *copyMatrix(matrix *m) {
  if (m == NULL) {
    fprintf(stderr, "File %s, Line %d, Function %s: Input is invalid.\n",
            __FILE__, __LINE__, __FUNCTION__);
  } else if (m->data == NULL) {
    fprintf(stderr, "File %s, Line %d, Function %s: Input has invalid data.\n",
            __FILE__, __LINE__, __FUNCTION__);
  }

  float *pFloat = (float *)malloc(m->row * m->column * sizeof(float));
  if (pFloat == NULL) {
    fprintf(stderr, "Failed to allocate memory.\n");
  }

  memcpy(pFloat, m->data, m->row * m->column * sizeof(float));
  matrix *copy = createMatrix(pFloat, m->row, m->column);
  return copy;
}

matrix *matmul_plain(matrix *matrix_1, matrix *matrix_2) {
  if (matrix_1 == NULL) {
    fprintf(stderr, "File %s, Line %d, Function %s: First input is invalid.\n",
            __FILE__, __LINE__, __FUNCTION__);
  } else if (matrix_1->data == NULL) {
    fprintf(stderr,
            "File %s, Line %d, Function %s: First input has invalid data.\n",
            __FILE__, __LINE__, __FUNCTION__);
  }

  if (matrix_2 == NULL) {
    fprintf(stderr, "File %s, Line %d, Function %s: Second input is invalid.\n",
            __FILE__, __LINE__, __FUNCTION__);
  } else if (matrix_2->data == NULL) {
    fprintf(stderr,
            "File %s, Line %d, Function %s: Second input has invalid data.\n",
            __FILE__, __LINE__, __FUNCTION__);
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

matrix *matmul_improved(matrix *matrix_1, matrix *matrix_2) {
  if (matrix_1 == NULL) {
    fprintf(stderr, "File %s, Line %d, Function %s: First input is invalid.\n",
            __FILE__, __LINE__, __FUNCTION__);
  } else if (matrix_1->data == NULL) {
    fprintf(stderr,
            "File %s, Line %d, Function %s: First input has invalid data.\n",
            __FILE__, __LINE__, __FUNCTION__);
  }

  if (matrix_2 == NULL) {
    fprintf(stderr, "File %s, Line %d, Function %s: Second input is invalid.\n",
            __FILE__, __LINE__, __FUNCTION__);
  } else if (matrix_2->data == NULL) {
    fprintf(stderr,
            "File %s, Line %d, Function %s: Second input has invalid data.\n",
            __FILE__, __LINE__, __FUNCTION__);
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

matrix *matmul_simd(matrix *matrix_1, matrix *matrix_2) {
  if (matrix_1 == NULL) {
    fprintf(stderr, "File %s, Line %d, Function %s: First input is invalid.\n",
            __FILE__, __LINE__, __FUNCTION__);
  } else if (matrix_1->data == NULL) {
    fprintf(stderr,
            "File %s, Line %d, Function %s: First input has invalid data.\n",
            __FILE__, __LINE__, __FUNCTION__);
  }

  if (matrix_2 == NULL) {
    fprintf(stderr, "File %s, Line %d, Function %s: Second input is invalid.\n",
            __FILE__, __LINE__, __FUNCTION__);
  } else if (matrix_2->data == NULL) {
    fprintf(stderr,
            "File %s, Line %d, Function %s: Second input has invalid data.\n",
            __FILE__, __LINE__, __FUNCTION__);
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

matrix *matmul_openmp(matrix *matrix_1, matrix *matrix_2) {
  if (matrix_1 == NULL) {
    fprintf(stderr, "File %s, Line %d, Function %s: First input is invalid.\n",
            __FILE__, __LINE__, __FUNCTION__);
  } else if (matrix_1->data == NULL) {
    fprintf(stderr,
            "File %s, Line %d, Function %s: First input has invalid data.\n",
            __FILE__, __LINE__, __FUNCTION__);
  }

  if (matrix_2 == NULL) {
    fprintf(stderr, "File %s, Line %d, Function %s: Second input is invalid.\n",
            __FILE__, __LINE__, __FUNCTION__);
  } else if (matrix_2->data == NULL) {
    fprintf(stderr,
            "File %s, Line %d, Function %s: Second input has invalid data.\n",
            __FILE__, __LINE__, __FUNCTION__);
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
