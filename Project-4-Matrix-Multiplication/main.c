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
    return 0;
}
