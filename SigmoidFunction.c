#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

void SigmoidOfElements(float  *input_Array, int no_of_elements);
float SigmoidArray(float x);


int main() {
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