#include "main.h"

int main() {
    float a[3][4] = {{1.f, 2, 3, 4},
                     {2,   3, 4, 5},
                     {3,   4, 5, 6}};
    matrix *m = createMatrix((float *) a, 3, 4);
    printMatrix(m);
    addScalar(m, 2);
    printMatrix(m);
    subtractScalar(m, 2);
    printMatrix(m);
    printf("%f,%f", max(m), min(m));
    return 0;
}
