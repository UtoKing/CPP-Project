#include "main.h"

int main() {
    float a[3][4] = {{1,  2,  3,  4},
                     {2,  3,  4,  5},
                     {-3, -4, -5, -6}};
    matrix *m1 = createMatrix((float *) a, 3, 4);
    printf("matrix 1 = ");
    printMatrix(m1);

    float b[4][2] = {{1,  1},
                     {-1, -1},
                     {2,  3},
                     {5,  6}};
    matrix *m2 = createMatrix((float *) b, 4, 2);
    printf("matrix 2 = ");
    printMatrix(m2);

    matrix *m1_copy = copyMatrix(m1);
    printf("matrix 1 copy = ");
    printMatrix(m1_copy);

    printf("pointer of matrix 1: %p\n", m1);
    printf("pointer of matrix 2: %p\n\n", m1_copy);

    matrix *m_addition = addMatrix(m1, m1_copy);
    printf("matrix 1 + matrix 1 copy = ");
    printMatrix(m_addition);

    matrix *m_subtract = subtractMatrix(m1, m1_copy);
    printf("matrix 1 - matrix 1 copy = ");
    printMatrix(m_subtract);

    addScalar_(m1, 1.2f);
    printf("self-addition: matrix 1 + 1.2 = ");
    printMatrix(m1);

    matrix *m2_subtract = subtractScalar(m2, 0.5f);
    printf("matrix 2 - 0.5 = ");
    printMatrix(m2_subtract);

    matrix *m_multiply = multiplyMatrix(m1, m2);
    printf("matrix 1 * matrix 2 = ");
    printMatrix(m_multiply);

    printf("Max of matrix 1 is: %f\n", max(m1));
    printf("Min of matrix 2 is: %f\n", min(m2));

    deleteMatrix(m1);
    deleteMatrix(m2);
    deleteMatrix(m1_copy);
    deleteMatrix(m_addition);
    deleteMatrix(m_subtract);
    deleteMatrix(m2_subtract);
    deleteMatrix(m_multiply);

    return 0;
}
