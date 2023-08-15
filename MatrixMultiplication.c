
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>


float** Multiply_Matrices(float** Matrix1, int rows1, int cols1, float** Matrix2, int rows2, int cols2);
void free_memory(float** matrix, int rows);


int main(){
    return 0;
}

//Function to multiply the matrices
float** Multiply_Matrices(float** Matrix1, int rows1, int cols1, float** Matrix2, int rows2, int cols2){

    //allocating memory for result matrix
    float** resultMatrix = (float**) malloc(rows1*sizeof(float*));
    for (int i = 0; i < rows1; i++){
        resultMatrix[i]= (float*) malloc(cols2*sizeof(float));
    }

    //Multiplying the matrices
    for(int i = 0; i < rows1; i++){
        for(int j = 0; j < cols2; j++){
            resultMatrix[i][j]=0;
            for(int k = 0; k < cols1; k++){
                resultMatrix[i][j] =  resultMatrix[i][j] + (Matrix1[i][k]*Matrix2[k][j]);
            }
        }
    }
    return resultMatrix;
}
   

    // function for freeing the memory
    void free_memory(float** matrix, int rows){
        for(int i=0; i<rows; i++){
            free(matrix[i]);
    }
    free(matrix);
}