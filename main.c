#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

void SigmoidOfElements(float  *input_Array, int no_of_elements);
float SigmoidArray(float x);
void reluToEachElement(float* inputArray, int size);
float relu(float x);


   


int main() {
     // Initialize testArray with some values
    float testArray[] = {32, -32, 21, -23, 21, 32, 23, 232, 1, 32.7};
    int size = sizeof(testArray) / sizeof(testArray[0]);


    // Apply ReLU to each element of the array
    reluToEachElement(testArray, size);

    // Initialize inputArray
    float input_Array[] = {0.1,0.65,1,0,-0.34,-0.02};
    int no_of_elements = sizeof(input_Array) / sizeof(input_Array[0]);

    printf("\nInputs for sigmoid function:\n");
    for (int i = 0; i < no_of_elements; i++) {
        printf("%f\n",input_Array[i]);
    }
    

    // call sigmoid function
    SigmoidOfElements(input_Array, no_of_elements);
    printf("\nOutputs after applying sigmoid:\n");
    for (int i = 0; i < no_of_elements; i++) {
        printf("%f\n",input_Array[i]);
    }
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