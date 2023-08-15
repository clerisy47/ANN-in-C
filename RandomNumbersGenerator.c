#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>


// Function to generate random numbers between 0 and 1
void generateNumbers(float *array, int size);

int main() {
    srand(time(NULL)); // for generating random numbers , must be in main do not remove
    return 0;
}

//generating random numbers between 0 and 1
void generateNumbers(float *array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = (float)rand() / RAND_MAX;
    }
}
