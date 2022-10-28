//
// Created by UtoKing on 2022/10/19.
//

#ifndef PROJECT_2_MATRIX_OPERATION_MATRIXOPERATION_H
#define PROJECT_2_MATRIX_OPERATION_MATRIXOPERATION_H

#include "matrix.h"
#include "malloc.h"
#include "assert.h"
#include "string.h"

void printMatrix(matrix *m);

matrix *createMatrix(float *data, int row, int column);

void deleteMatrix(matrix *m);

matrix *copyMatrix(matrix *m);

matrix *addMatrix(matrix *matrix1, matrix *matrix2);

matrix *subtractMatrix(matrix *matrix1, matrix *matrix2);

void addScalar_(matrix *m, float scalar);

void subtractScalar_(matrix *m, float scalar);

void multiplyScalar_(matrix *m, float scalar);

matrix *addScalar(matrix *m, float scalar);

matrix *subtractScalar(matrix *m, float scalar);

matrix *multiplyScalar(matrix *m, float scalar);

float max(matrix *m);

float min(matrix *m);

matrix *multiplyMatrix(matrix *matrix1, matrix *matrix2);

#endif //PROJECT_2_MATRIX_OPERATION_MATRIXOPERATION_H


