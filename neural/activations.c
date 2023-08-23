// Include necessary header files
#include "activations.h"
#include <math.h>
#include "../matrix/ops.h"

// Sigmoid activation function
double sigmoid(double input) {
    return 1.0 / (1 + exp(-1 * input));
}

// Calculate the derivative of sigmoid activation
Matrix* sigmoidPrime(Matrix* m) {
    // Create a matrix of ones with the same dimensions as 'm'
    Matrix* ones = matrix_create(m->rows, m->cols);
    matrix_fill(ones, 1);

    // Calculate the element-wise difference between 'ones' and 'm'
    Matrix* subtracted = subtract(ones, m);

    // Calculate the element-wise product of 'm' and 'subtracted'
    Matrix* multiplied = multiply(m, subtracted);

    // Free intermediate matrices
    matrix_free(ones);
    matrix_free(subtracted);

    return multiplied;
}

// Softmax activation function
Matrix* softmax(Matrix* m) {
    double total = 0;

    // Calculate the sum of exponential values for normalization
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            total += exp(m->entries[i][j]);
        }
    }

    // Create a matrix for storing the softmax probabilities
    Matrix* mat = matrix_create(m->rows, m->cols);
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            // Calculate the softmax probability for each element
            mat->entries[i][j] = exp(m->entries[i][j]) / total;
        }
    }
    return mat;
}
