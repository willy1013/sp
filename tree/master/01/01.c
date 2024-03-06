#include <stdio.h>
#include <stdlib.h>

// 使用Chatgpt

// 定義矩陣結構
typedef struct {
    int rows;
    int cols;
    double *data; // 使用單一指針來表示二維陣列
} Matrix;

// 函式原型
Matrix *create_matrix(int rows, int cols);
void free_matrix(Matrix *matrix);
void transpose(Matrix *input, Matrix *output);
void add(Matrix *matrix1, Matrix *matrix2, Matrix *result);
void multiply(Matrix *matrix1, Matrix *matrix2, Matrix *result);
void dump(Matrix *matrix);
void reshape(Matrix *input, Matrix *output, int new_rows, int new_cols);

int main() {
    // 創建矩陣
    int rows = 3;
    int cols = 3;
    Matrix *matrix1 = create_matrix(rows, cols);
    Matrix *matrix2 = create_matrix(rows, cols);
    Matrix *result = create_matrix(rows, cols);

    // 初始化矩陣數據
    for (int i = 0; i < rows * cols; i++) {
        matrix1->data[i] = i + 1;
        matrix2->data[i] = 9 - i;
    }

    // 轉置矩陣
    Matrix *transposed = create_matrix(cols, rows);
    transpose(matrix1, transposed);
    printf("Transposed matrix:\n");
    dump(transposed);

    // 矩陣相加
    add(matrix1, matrix2, result);
    printf("Sum of matrices:\n");
    dump(result);

    // 矩陣相乘
    multiply(matrix1, matrix2, result);
    printf("Product of matrices:\n");
    dump(result);

    // 改形狀
    int new_rows = 1;
    int new_cols = 9;
    Matrix *reshaped = create_matrix(new_rows, new_cols);
    reshape(matrix1, reshaped, new_rows, new_cols);
    printf("Reshaped matrix:\n");
    dump(reshaped);

    // 釋放矩陣
    free_matrix(matrix1);
    free_matrix(matrix2);
    free_matrix(result);
    free_matrix(transposed);
    free_matrix(reshaped);

    return 0;
}

// 創建矩陣並初始化
Matrix *create_matrix(int rows, int cols) {
    Matrix *matrix = (Matrix *)malloc(sizeof(Matrix));
    if (matrix == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->data = (double *)malloc(rows * cols * sizeof(double));
    if (matrix->data == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    return matrix;
}

// 釋放矩陣的內存
void free_matrix(Matrix *matrix) {
    free(matrix->data);
    free(matrix);
}

// 轉置矩陣
void transpose(Matrix *input, Matrix *output) {
    for (int i = 0; i < input->rows; i++) {
        for (int j = 0; j < input->cols; j++) {
            output->data[j * input->rows + i] = input->data[i * input->cols + j];
        }
    }
}

// 矩陣相加
void add(Matrix *matrix1, Matrix *matrix2, Matrix *result) {
    for (int i = 0; i < matrix1->rows * matrix1->cols; i++) {
        result->data[i] = matrix1->data[i] + matrix2->data[i];
    }
}

// 矩陣相乘
void multiply(Matrix *matrix1, Matrix *matrix2, Matrix *result) {
    for (int i = 0; i < matrix1->rows; i++) {
        for (int j = 0; j < matrix2->cols; j++) {
            result->data[i * matrix2->cols + j] = 0;
            for (int k = 0; k < matrix1->cols; k++) {
                result->data[i * matrix2->cols + j] += matrix1->data[i * matrix1->cols + k] * matrix2->data[k * matrix2->cols + j];
            }
        }
    }
}

// 印出矩陣
void dump(Matrix *matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            printf("%lf ", matrix->data[i * matrix->cols + j]);
        }
        printf("\n");
    }
}

// 改形狀
void reshape(Matrix *input, Matrix *output, int new_rows, int new_cols) {
    if (input->rows * input->cols != new_rows * new_cols) {
        printf("Cannot reshape matrix: incompatible dimensions\n");
        return;
    }
    for (int i = 0; i < new_rows; i++) {
        for (int j = 0; j < new_cols; j++) {
            output->data[i * new_cols + j] = input->data[i * new_cols + j];
        }
    }
}
