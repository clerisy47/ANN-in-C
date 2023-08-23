// Include necessary header files
#include "matrix.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Define a maximum character limit for reading lines from files
#define MAXCHAR 100

// Function to create a new Matrix instance with given dimensions
Matrix* matrix_create(int row, int col) {
    Matrix *matrix = malloc(sizeof(Matrix));
    matrix->rows = row;
    matrix->cols = col;
    matrix->entries = malloc(row * sizeof(double*));
    for (int i = 0; i < row; i++) {
        matrix->entries[i] = malloc(col * sizeof(double));
    }
    return matrix;
}

// Function to fill a Matrix with a given value 'n'
void matrix_fill(Matrix *m, int n) {
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            m->entries[i][j] = n;
        }
    }
}

// Function to free memory occupied by a Matrix instance
void matrix_free(Matrix *m) {
    for (int i = 0; i < m->rows; i++) {
        free(m->entries[i]);
    }
    free(m->entries);
    free(m);
    m = NULL;
}

// Function to print the dimensions and entries of a Matrix
void matrix_print(Matrix* m) {
    printf("Rows: %d Columns: %d\n", m->rows, m->cols);
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            printf("%1.3f ", m->entries[i][j]);
        }
        printf("\n");
    }
}

// Function to create a deep copy of a Matrix instance
Matrix* matrix_copy(Matrix* m) {
    Matrix* mat = matrix_create(m->rows, m->cols);
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            mat->entries[i][j] = m->entries[i][j];
        }
    }
    return mat;
}

// Function to save a Matrix's data to a file
void matrix_save(Matrix* m, char* file_string) {
    FILE* file = fopen(file_string, "w");
    fprintf(file, "%d\n", m->rows);
    fprintf(file, "%d\n", m->cols);
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            fprintf(file, "%.6f\n", m->entries[i][j]);
        }
    }
    printf("Successfully saved matrix to %s\n", file_string);
    fclose(file);
}

// Function to load a Matrix's data from a file
Matrix* matrix_load(char* file_string) {
    FILE* file = fopen(file_string, "r");
    char entry[MAXCHAR];
    fgets(entry, MAXCHAR, file);
    int rows = atoi(entry);
    fgets(entry, MAXCHAR, file);
    int cols = atoi(entry);
    Matrix* m = matrix_create(rows, cols);
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            fgets(entry, MAXCHAR, file);
            m->entries[i][j] = strtod(entry, NULL);
        }
    }
    printf("Successfully loaded matrix from %s\n", file_string);
    fclose(file);
    return m;
}

// Function to generate a uniform random number within a given range
double uniform_distribution(double low, double high) {
    double difference = high - low;
    int scale = 10000;
    int scaled_difference = (int)(difference * scale);
    return low + (1.0 * (rand() % scaled_difference) / scale);
}

// Function to fill a Matrix with random values within a specific range
void matrix_randomize(Matrix* m, int n) {
    double min = -1.0 / sqrt(n);
    double max = 1.0 / sqrt(n);
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            m->entries[i][j] = uniform_distribution(min, max);
        }
    }
}

// Function to find the index of the maximum value in a Matrix
int matrix_argmax(Matrix* m) {
    double max_score = 0;
    int max_idx = 0;
    for (int i = 0; i < m->rows; i++) {
        if (m->entries[i][0] > max_score) {
            max_score = m->entries[i][0];
            max_idx = i;
        }
    }
    return max_idx;
}

// Function to flatten a Matrix along a specified axis (0 or 1)
Matrix* matrix_flatten(Matrix* m, int axis) {
    Matrix* mat;
    if (axis == 0) {
        mat = matrix_create(m->rows * m->cols, 1);
    } else if (axis == 1) {
        mat = matrix_create(1, m->rows * m->cols);
    } else {
        printf("Argument to matrix_flatten must be 0 or 1");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            if (axis == 0) mat->entries[i * m->cols + j][0] = m->entries[i][j];
            else if (axis == 1) mat->entries[0][i * m->cols + j] = m->entries[i][j];
        }
    }
    return mat;
}
