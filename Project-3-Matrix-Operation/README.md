# REPORT on PROJECT 3: Matrix Operation

Name: MIAO Fangran

Student ID: 11911819

## PART 1: Analysis

在这个 Project 中需要我们定义矩阵并实现矩阵的大部分运算操作.

1. **定义矩阵**.
   我们用一个 `struct` 来实现矩阵的定义, 并用 `typedef` 方便以后书写代码.
   在这个结构体中我们首先需要定义行和列, 即 `row` 和 `column`.
   其次我们需要定义矩阵的数据.
   因为在结构体中定义数组的话必须要提前规定好大小, 而每个矩阵都有不同的大小, 所以不能够直接在里面提前定义.
   因此采用定义指针的方式, 而指针指向的数组的大小就是 `row * column`.

2. **如何定义矩阵**.
   在定义矩阵的函数中, 我们会先声明一个矩阵指针, 然后再初始化里面的数组指针.
   这两步的初始化都使用了 `malloc` 函数.
   最后我们会返回一个矩阵指针变量.

3. **删除矩阵**.
   在删除的操作中, 首先需要释放结构体内部的数组指针, 之后再释放该结构体指针本身.
   为保证安全性, 使结构体释放完成后让其指向了 `NULL`.

4. **拷贝矩阵**
   在拷贝矩阵的过程中, 需要分别生成新的数组指针和矩阵指针.
   然后采用 1 中的方法定义矩阵.

5. **矩阵加减**
   首先创建二维数组, 然后使矩阵中对应元素相加减即可.
   最后再用 1 的方法新建个矩阵指针并返回这个指针.
   但值得注意的是需要先判断两个矩阵的行和列是否相等.
   这里用到了 `assert` 来进行判断.

6. **矩阵的数乘, 数加, 数减**
   与矩阵的加减稍微不同的一点是矩阵加减会返回一个新的矩阵指针, 而数乘会在原来的矩阵指针上做修改.
   因此这些方法返回类型都是 `void`.
   实现方法也是每个元素加/减/乘一个数即可.

7. **矩阵相乘**
   矩阵相乘也是需要一个判断, 即需要判断矩阵 1 的列等于矩阵 2 的行.
   之后按照矩阵相乘的公式进行计算即可.

8. **最大最小值**
   遍历数组, 获取最大最小值即可.

9. **额外的函数**
   为方便查看矩阵, 因此特地写了打印矩阵的函数, 可以方便的打印 m 行 n 列的矩阵.

## PART 2: Code

### 定义矩阵

```c
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
```

### 删除矩阵

```c
void deleteMatrix(matrix *m) {
    if (m == NULL) return;
    free(m->data);
    free(m);
    m = NULL;
}
```

### 复制矩阵

```c
matrix *copyMatrix(matrix *m) {
    float *pDouble3 = (float *) malloc(m->row * m->column * sizeof(float));
    memcpy(pDouble3, m->data, m->row * m->column * sizeof(float));
    matrix *copy = createMatrix(pDouble3, m->row, m->column);
    return copy;
}
```

### 矩阵加减

```c
matrix *addMatrix(matrix *matrix1, matrix *matrix2) {
    int row = matrix1->row, column = matrix1->column;
    assert(row == matrix2->row);
    assert(column == matrix2->column);

    float *pDouble1 = matrix1->data;
    float *pDouble2 = matrix2->data;
    float *pDouble3 = (float *) malloc(row * column * sizeof(float));
    for (int i = 0; i < row * column; ++i) {
        *pDouble3 = *pDouble1 + *pDouble2;
        pDouble1++;
        pDouble2++;
        pDouble3++;
    }
    pDouble3 -= row * column;
    matrix *result = createMatrix(pDouble3, row, column);
    return result;
}

matrix *subtractMatrix(matrix *matrix1, matrix *matrix2) {
    int row = matrix1->row, column = matrix1->column;
    assert(row == matrix2->row);
    assert(column == matrix2->column);

    float *pDouble1 = matrix1->data;
    float *pDouble2 = matrix2->data;
    float *pDouble3 = (float *) malloc(row * column * sizeof(float));
    for (int i = 0; i < row * column; ++i) {
        *pDouble3 = *pDouble1 - *pDouble2;
        pDouble1++;
        pDouble2++;
        pDouble3++;
    }
    pDouble3 -= row * column;
    matrix *result = createMatrix(pDouble3, row, column);
    return result;
}
```

### 矩阵数乘/加/减

```c
void addScalar(matrix *m, float scalar) {
    int row = m->row, column = m->column;
    float *pDouble = m->data;
    for (int i = 0; i < row * column; ++i) {
        *pDouble += scalar;
        pDouble++;
    }
}

void subtractScalar(matrix *m, float scalar) {
    addScalar(m, -scalar);
}

void multiplyScalar(matrix *m, float scalar) {
    int row = m->row, column = m->column;
    float *pDouble = m->data;
    for (int i = 0; i < row * column; ++i) {
        *pDouble *= scalar;
        pDouble++;
    }
}
```

### 矩阵相乘

```c
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
```

### 最大最小值

```c
float max(matrix *m) {
    float max = 0;
    int row = m->row, column = m->column;
    float *pDouble = m->data;
    for (int i = 0; i < row * column; ++i) {
        if (*pDouble > max) max = *pDouble;
        pDouble++;
    }
    return max;
}

float min(matrix *m) {
    float min = 0;
    int row = m->row, column = m->column;
    float *pDouble = m->data;
    for (int i = 0; i < row * column; ++i) {
        if (*pDouble < min) min = *pDouble;
        pDouble++;
    }
    return min;
}
```

### 打印矩阵

```c
void printMatrix(matrix *m) {
    int row = m->row, column = m->column;
    float *pDouble = m->data;

    printf("Matrix: \n");
    for (int i = 0; i < row * column; ++i) {
        printf("%f", *pDouble);
        pDouble++;
        if ((i + 1) % column == 0) { printf("\n"); }
        else { printf(","); }
    }
    printf("\n");
}
```

## PART 3: Verification
