#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

void reluToEachElement(float* inputArray, int size);
float relu(float x);

int main() {
    // Initialize testArray with some values
    float testArray[] = {32, -32, 21, -23, 21, 32, 23, 232, 1, 32.7};
    int size = sizeof(testArray) / sizeof(testArray[0]);


    // Apply ReLU to each element of the array
    reluToEachElement(testArray, size);



    return 0;
}

// relu function to take each element of an array and apply ReLU
void reluToEachElement(float* inputArray, int size) {
    for (int i = 0; i < size; i++) {
        inputArray[i] = relu(inputArray[i]);
    }
}

// relu function
float relu(float x) {
    return (x > 0) ? x : 0;
}