// Include necessary header files
#include "ops.h"
#include <stdlib.h>
#include <stdio.h>

// Function to check if the dimensions of two matrices are compatible for operations
int check_dimensions(Matrix *m1, Matrix *m2) {
    if (m1->rows == m2->rows && m1->cols == m2->cols) return 1;
    return 0;
}

// Function to perform element-wise matrix multiplication
Matrix* multiply(Matrix *m1, Matrix *m2) {
    if (check_dimensions(m1, m2)) {
        Matrix *m = matrix_create(m1->rows, m1->cols);
        for (int i = 0; i < m1->rows; i++) {
            for (int j = 0; j < m2->cols; j++) {
                m->entries[i][j] = m1->entries[i][j] * m2->entries[i][j];
            }
        }
        return m;
    } else {
        printf("Dimension mismatch multiply: %dx%d %dx%d\n", m1->rows, m1->cols, m2->rows, m2->cols);
        exit(1);
    }
}

// Function to perform element-wise matrix addition
Matrix* add(Matrix *m1, Matrix *m2) {
    if (check_dimensions(m1, m2)) {
        Matrix *m = matrix_create(m1->rows, m1->cols);
        for (int i = 0; i < m1->rows; i++) {
            for (int j = 0; j < m2->cols; j++) {
                m->entries[i][j] = m1->entries[i][j] + m2->entries[i][j];
            }
        }
        return m;
    } else {
        printf("Dimension mismatch add: %dx%d %dx%d\n", m1->rows, m1->cols, m2->rows, m2->cols);
        exit(1);
    }
}

// Function to perform element-wise matrix subtraction
Matrix* subtract(Matrix *m1, Matrix *m2) {
    if (check_dimensions(m1, m2)) {
        Matrix *m = matrix_create(m1->rows, m1->cols);
        for (int i = 0; i < m1->rows; i++) {
            for (int j = 0; j < m2->cols; j++) {
                m->entries[i][j] = m1->entries[i][j] - m2->entries[i][j];
            }
        }
        return m;
    } else {
        printf("Dimension mismatch subtract: %dx%d %dx%d\n", m1->rows, m1->cols, m2->rows, m2->cols);
        exit(1);
    }
}

// Function to apply a given function element-wise to a matrix
Matrix* apply(double (*func)(double), Matrix* m) {
    Matrix *mat = matrix_copy(m);
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            mat->entries[i][j] = (*func)(m->entries[i][j]);
        }
    }
    return mat;
}

// Function to perform matrix multiplication (dot product)
Matrix* dot(Matrix *m1, Matrix *m2) {
    if (m1->cols == m2->rows) {
        Matrix *m = matrix_create(m1->rows, m2->cols);
        for (int i = 0; i < m1->rows; i++) {
            for (int j = 0; j < m2->cols; j++) {
                double sum = 0;
                for (int k = 0; k < m2->rows; k++) {
                    sum += m1->entries[i][k] * m2->entries[k][j];
                }
                m->entries[i][j] = sum;
            }
        }
        return m;
    } else {
        printf("Dimension mismatch dot: %dx%d %dx%d\n", m1->rows, m1->cols, m2->rows, m2->cols);
        exit(1);
    }
}

// Function to scale a matrix by a scalar value
Matrix* scale(double n, Matrix* m) {
    Matrix* mat = matrix_copy(m);
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            mat->entries[i][j] *= n;
        }
    }
    return mat;
}

// Function to add a scalar value to each element of a matrix
Matrix* addScalar(double n, Matrix* m) {
    Matrix* mat = matrix_copy(m);
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            mat->entries[i][j] += n;
        }
    }
    return mat;
}

// Function to transpose a matrix
Matrix* transpose(Matrix* m) {
    Matrix* mat = matrix_create(m->cols, m->rows);
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            mat->entries[j][i] = m->entries[i][j];
        }
    }
    return mat;
}
