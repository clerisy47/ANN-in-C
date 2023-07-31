#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

void SigmoidOfElements(float  *input_Array, int no_of_elements);
float SigmoidArray(float x);
void reluToEachElement(float* inputArray, int size);
float relu(float x);
void tanhyper(float *inputArray, int size);
void generateNumbers(float *array, int size);


int main() {
    srand(time(NULL)); // for generating random numbers , must be in main do not remove
    return 0;
}

// Passing Each element of array to sigmodArray Function.
void SigmoidOfElements(float  *input_Array, int no_of_elements) {
    for (int i = 0; i < no_of_elements; i++) {
        input_Array[i] = SigmoidArray(input_Array[i]);
    }
}

// Applying sigmoid function to each element of array
float SigmoidArray(float x) {
    return(1/(1+exp(-x))); 

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

//random function
void generateNumbers(float *array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = (float)rand() / RAND_MAX;
        printf("%f\t",array[i]);
    }
}