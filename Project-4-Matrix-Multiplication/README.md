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
   这一步分成了每个操作各写了两个方法, 分别为每个矩阵的自身的增/减/乘或返回个新矩阵.
   例如 `addScalar_(matrix *m, float scalar)` 方法则会在传入的矩阵指针 `m` 上进行加法操作, 返回值为 `void`.
   而 `addScalar(matrix *m, float scalar)` 则会返回一个全新的矩阵, 而原矩阵不会做任何的改变.

7. **矩阵相乘**
   矩阵相乘也是需要一个判断, 即需要判断矩阵 1 的列等于矩阵 2 的行.
   之后按照矩阵相乘的公式进行计算即可.

8. **最大最小值**
   遍历数组, 获取最大最小值即可.
   但需要注意初始化时需要将初始值设为数组的第一元素, 不能设为 0 这种数.

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

这里仅展示 `addScalar_` 和 `addScalar` 方法, 减法和乘法的实现类似.

```c
void addScalar_(matrix *m, float scalar) {
    int row = m->row, column = m->column;
    float *pDouble = m->data;
    for (int i = 0; i < row * column; ++i) {
        *pDouble += scalar;
        pDouble++;
    }
}

matrix *addScalar(matrix *m, float scalar) {
    int row = m->row, column = m->column;
    float *pDouble1 = m->data;
    float *pDouble2 = (float *) malloc(row * column * sizeof(float));
    for (int i = 0; i < row * column; ++i) {
        *pDouble2 = *pDouble1 + scalar;
        pDouble1++;
        pDouble2++;
    }
    pDouble2 -= row * column;
    return createMatrix(pDouble2, row, column);
}
```

### 矩阵相乘

```c
matrix *matmul_plain(matrix *matrix1, matrix *matrix2) {
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
    float max = *(m->data);
    int row = m->row, column = m->column;
    float *pDouble = m->data;
    for (int i = 0; i < row * column; ++i) {
        if (*pDouble > max) max = *pDouble;
        pDouble++;
    }
    return max;
}

float min(matrix *m) {
    float min = *(m->data);
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

    printf("Matrix: [\n");
    for (int i = 0; i < row * column; ++i) {
        printf("%f", *pDouble);
        pDouble++;
        if ((i + 1) % column == 0) { printf("\n"); }
        else { printf(","); }
    }
    printf("]\n");
}
```

## PART 3: Verification

Verification 的相关代码放在了 `main.c` 中.
下面仅展示运行结果. (因输出结果有点长, 就没有截图, 但把运行结果粘贴在了下方)

```txt
matrix 1 = Matrix: [
1.000000,2.000000,3.000000,4.000000
2.000000,3.000000,4.000000,5.000000
-3.000000,-4.000000,-5.000000,-6.000000
]
matrix 2 = Matrix: [
1.000000,1.000000
-1.000000,-1.000000
2.000000,3.000000
5.000000,6.000000
]
matrix 1 copy = Matrix: [
1.000000,2.000000,3.000000,4.000000
2.000000,3.000000,4.000000,5.000000
-3.000000,-4.000000,-5.000000,-6.000000
]
pointer of matrix 1: 0x5563bbfa82a0
pointer of matrix 2: 0x5563bbfa87a0

matrix 1 + matrix 1 copy = Matrix: [
2.000000,4.000000,6.000000,8.000000
4.000000,6.000000,8.000000,10.000000
-6.000000,-8.000000,-10.000000,-12.000000
]
matrix 1 - matrix 1 copy = Matrix: [
0.000000,0.000000,0.000000,0.000000
0.000000,0.000000,0.000000,0.000000
0.000000,0.000000,0.000000,0.000000
]
self-addition: matrix 1 + 1.2 = Matrix: [
2.200000,3.200000,4.200000,5.200000
3.200000,4.200000,5.200000,6.200000
-1.800000,-2.800000,-3.800000,-4.800000
]
matrix 2 - 0.5 = Matrix: [
0.500000,0.500000
-1.500000,-1.500000
1.500000,2.500000
4.500000,5.500000
]
matrix 1 * matrix 2 = Matrix: [
33.400002,42.799999
40.400002,51.799995
-30.600000,-39.200001
]
Max of matrix 1 is: 6.200000
Min of matrix 2 is: -1.000000
```

## PART 4: Difficulties and Solutions

因为问题和解决办法在第一部分做了比较详细的阐述, 故在这里总结一下.

- 创建矩阵时用 `struct` 来实现的, 该结构体内包括行和列以及一个 `float` 的指针指向矩阵数据的开头, 在我们创建矩阵时都会返回一个结构体指针.
- 删除矩阵需要从最内部开始删除, 即先删除里面的 `float` 指针, 之后再删除结构体指针本身. 最后让指针指向 `NULL`.
- 拷贝矩阵会有新的指针产生, 且里面的数据是完全一样的 (除了指针本身的地址不一样).
- 矩阵加减会返回一个新的矩阵指针.
- 矩阵加减乘一个数分别实现了两个方法, 一个是自身的加/减/乘, 另外的一个会返回一个新的矩阵指针.
- 矩阵相乘按照计算矩阵乘法的运算法则即可.
- `min` `max` 遍历整个数组即可.
- 额外实现了一个打印数组的方法, 方便检查代码以及运算是否正确.
