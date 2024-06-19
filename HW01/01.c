#include <stdio.h>
#include <stdlib.h>

// Function prototypes
double* createMatrix(int rows, int cols);
void transpose(double* matrix, int rows, int cols, double* result);
void add(double* matrix1, double* matrix2, int rows, int cols, double* result);
void multiply(double* matrix1, int rows1, int cols1, double* matrix2, int rows2, int cols2, double* result);
void dump(double* matrix, int rows, int cols);

int main() {
    // Example usage of the library functions
    int rows = 2, cols = 3;
    double* matrix1 = createMatrix(rows, cols);
    double* matrix2 = createMatrix(rows, cols);
    double* result = createMatrix(rows, cols);

    // Initializing example matrices
    for (int i = 0; i < rows * cols; i++) {
        matrix1[i] = i + 1;
        matrix2[i] = (i + 1) * 2;
    }

    printf("Matrix 1:\n");
    dump(matrix1, rows, cols);

    printf("Matrix 2:\n");
    dump(matrix2, rows, cols);

    add(matrix1, matrix2, rows, cols, result);
    printf("Addition Result:\n");
    dump(result, rows, cols);

    int rowsB = 3, colsB = 2;
    double* matrixB = createMatrix(rowsB, colsB);
    for (int i = 0; i < rowsB * colsB; i++) {
        matrixB[i] = i + 1;
    }

    double* resultMul = createMatrix(rows, colsB);
    multiply(matrix1, rows, cols, matrixB, rowsB, colsB, resultMul);
    printf("Multiplication Result:\n");
    dump(resultMul, rows, colsB);

    double* resultTrans = createMatrix(cols, rows);
    transpose(matrix1, rows, cols, resultTrans);
    printf("Transpose Result:\n");
    dump(resultTrans, cols, rows);

    // Free allocated memory
    free(matrix1);
    free(matrix2);
    free(matrixB);
    free(result);
    free(resultMul);
    free(resultTrans);

    return 0;
}

double* createMatrix(int rows, int cols) {
    return (double*)malloc(rows * cols * sizeof(double));
}

void transpose(double* matrix, int rows, int cols, double* result) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[j * rows + i] = matrix[i * cols + j];
        }
    }
}

void add(double* matrix1, double* matrix2, int rows, int cols, double* result) {
    for (int i = 0; i < rows * cols; i++) {
        result[i] = matrix1[i] + matrix2[i];
    }
}

void multiply(double* matrix1, int rows1, int cols1, double* matrix2, int rows2, int cols2, double* result) {
    if (cols1 != rows2) {
        printf("Matrix multiplication is not possible.\n");
        return;
    }

    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            result[i * cols2 + j] = 0;
            for (int k = 0; k < cols1; k++) {
                result[i * cols2 + j] += matrix1[i * cols1 + k] * matrix2[k * cols2 + j];
            }
        }
    }
}

void dump(double* matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%lf ", matrix[i * cols + j]);
        }
        printf("\n");
    }
}
