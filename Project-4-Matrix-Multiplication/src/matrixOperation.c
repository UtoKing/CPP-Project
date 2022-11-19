//
// Created by UtoKing on 2022/10/19.
//

#include "matrixOperation.h"

void printMatrix(matrix *m) {
    int row = m->row, column = m->column;
    float *pDouble = m->data;

    printf("Matrix: [\n");
    for (int i = 0; i < row * column; ++i) {
        printf("%f", *pDouble);
        pDouble++;
        if ((i + 1) % column == 0) { printf("\n"); }
        else { printf(","); }
    }
    printf("]\n");
}

matrix *createMatrix(float *data, int row, int column) {
    matrix *m = (matrix *) malloc(sizeof(matrix));
    m->row = row;
    m->column = column;
    m->data = (float *) malloc(sizeof(float) * row * column);

    float *pDouble = m->data;
    for (int i = 0; i < row * column; ++i) {
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
    float *pDouble3 = (float *) malloc(m->row * m->column * sizeof(float));
    memcpy(pDouble3, m->data, m->row * m->column * sizeof(float));
    matrix *copy = createMatrix(pDouble3, m->row, m->column);
    return copy;
}


matrix *multiplyMatrix(matrix *matrix1, matrix *matrix2) {
    assert(matrix1->column == matrix2->row);
    int row = matrix1->row, column = matrix2->column, middle = matrix1->column;
    float *pDouble = (float *) malloc(row * column * sizeof(float));
    for (int i = 0; i < row * column; ++i) {
        int n_row = i / column, n_column = i % column;
        float sum = 0;
        for (int j = 0; j < middle; ++j) {
            sum += *(matrix1->data + n_row * middle + j) * *(matrix2->data + n_column + j * column);
        }
        *pDouble = sum;
        pDouble++;
    }
    pDouble -= row * column;
    return createMatrix(pDouble, row, column);
}
