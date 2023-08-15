#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

void reluToEachElement(float* inputArray, int size);
float relu(float x);
void tanhyper(float *inputArray, int size);
float** Multiply_Matrices(float** Matrix1, int rows1, int cols1, float** Matrix2, int rows2, int cols2);
void free_memory(float** matrix, int rows);


int main() {
    return 0;
}
 
// Applying relu function to each element of array
void reluToEachElement(float* inputArray, int size) {
    for (int i = 0; i < size; i++) {
        inputArray[i] = relu(inputArray[i]);
    }
}

// relu function
float relu(float x) {
    return (x > 0) ? x : 0;
}


//tan hyperbolic function
void tanhyper(float *inputArray, int size)
{
    for (int i = 0; i < size; i++)
    {
        inputArray[i] = tanh(inputArray[i]);
    }
}

