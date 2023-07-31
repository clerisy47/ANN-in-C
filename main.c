#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

void SigmoidOfElements(float  *input_Array, int no_of_elements);
float SigmoidArray(float x);


int main() {
    // Initialize inputArray
    float input_Array[] = {0.1,0.65,1,0,-0.34,-0.02};
    int no_of_elements = sizeof(input_Array) / sizeof(input_Array[0]);

    // call sigmoid function
    SigmoidOfElements(input_Array, no_of_elements);

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

