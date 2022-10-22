//
// Created by UtoKing on 2022/10/19.
//

#include "matrixOperation.h"

void printMatrix(matrix *m) {
    int rows = m->rows, columns = m->columns;
    float *pDouble = m->data;

    printf("Matrix: \n");
    for (int i = 0; i < rows * columns; ++i) {
        printf("%f", *pDouble);
        pDouble++;
        if ((i + 1) % columns == 0) { printf("\n"); }
        else { printf(","); }
    }
    printf("\n");
}

matrix *createMatrix(float *data, int rows, int columns) {
    matrix *m = (matrix *) malloc(sizeof(matrix));
    m->rows = rows;
    m->columns = columns;
    m->data = (float *) malloc(sizeof(float) * rows * columns);

    float *pDouble = m->data;
    for (int i = 0; i < rows * columns; ++i) {
        *pDouble = *data;
        pDouble++;
        data++;
    }
    return m;
}

void deleteMatrix(matrix *m) {
    if (m == NULL) return;
    free(m->data);
    free(m);
    m = NULL;
}

matrix *copyMatrix(matrix *m) {
    float *pDouble3 = (float *) malloc(m->rows * m->columns * sizeof(float));
    memcpy(pDouble3, m->data, m->rows * m->columns * sizeof(float));
    matrix *copy = createMatrix(pDouble3, m->rows, m->columns);
    return copy;
}

matrix *addMatrix(matrix *matrix1, matrix *matrix2) {
    int rows = matrix1->rows, columns = matrix1->columns;
    assert(rows == matrix2->rows);
    assert(columns == matrix2->columns);

    float *pDouble1 = matrix1->data;
    float *pDouble2 = matrix2->data;
    float *pDouble3 = (float *) malloc(rows * columns * sizeof(float));
    for (int i = 0; i < rows * columns; ++i) {
        *pDouble3 = *pDouble1 + *pDouble2;
        pDouble1++;
        pDouble2++;
        pDouble3++;
    }
    pDouble3 -= rows * columns;
    matrix *result = createMatrix(pDouble3, rows, columns);
    return result;
}

matrix *subtractMatrix(matrix *matrix1, matrix *matrix2) {
    int rows = matrix1->rows, columns = matrix1->columns;
    assert(rows == matrix2->rows);
    assert(columns == matrix2->columns);

    float *pDouble1 = matrix1->data;
    float *pDouble2 = matrix2->data;
    float *pDouble3 = (float *) malloc(rows * columns * sizeof(float));
    for (int i = 0; i < rows * columns; ++i) {
        *pDouble3 = *pDouble1 - *pDouble2;
        pDouble1++;
        pDouble2++;
        pDouble3++;
    }
    pDouble3 -= rows * columns;
    matrix *result = createMatrix(pDouble3, rows, columns);
    return result;
}

void addScalar(matrix *m, float scalar) {
    int rows = m->rows, columns = m->columns;
    float *pDouble = m->data;
    for (int i = 0; i < rows * columns; ++i) {
        *pDouble += scalar;
        pDouble++;
    }
}

void subtractScalar(matrix *m, float scalar) {
    addScalar(m, -scalar);
}

void multiplyScalar(matrix *m, float scalar) {
    int rows = m->rows, columns = m->columns;
    float *pDouble = m->data;
    for (int i = 0; i < rows * columns; ++i) {
        *pDouble *= scalar;
        pDouble++;
    }
}

float max(matrix *m) {
    float max = 0;
    int rows = m->rows, columns = m->columns;
    float *pDouble = m->data;
    for (int i = 0; i < rows * columns; ++i) {
        if (*pDouble > max) max = *pDouble;
        pDouble++;
    }
    return max;
}

float min(matrix *m) {
    float min = 0;
    int rows = m->rows, columns = m->columns;
    float *pDouble = m->data;
    for (int i = 0; i < rows * columns; ++i) {
        if (*pDouble < min) min = *pDouble;
        pDouble++;
    }
    return min;
}
