// Include necessary header files
#include "img.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a maximum character limit for reading lines from files
#define MAXCHAR 10000

// Function to convert CSV data to an array of Img pointers
Img** csv_to_imgs(char* file_string, int number_of_imgs) {
    FILE *fp;
    Img** imgs = malloc(number_of_imgs * sizeof(Img*));
    char row[MAXCHAR];
    fp = fopen(file_string, "r");

    // Read and ignore the header row
    fgets(row, MAXCHAR, fp);

    int i = 0;
    // Loop through the file until EOF or the desired number of images is reached
    while (feof(fp) != 1 && i < number_of_imgs) {
        // Allocate memory for a new Img instance
        imgs[i] = malloc(sizeof(Img));

        int j = 0;
        // Read the current row from the CSV file
        fgets(row, MAXCHAR, fp);
        char* token = strtok(row, ",");
        // Create a matrix for image data (assumed to be 28x28)
        imgs[i]->img_data = matrix_create(28, 28);
        while (token != NULL) {
            if (j == 0) {
                // Parse and store the label of the image
                imgs[i]->label = atoi(token);
            } else {
                // Parse and store pixel values while normalizing to the range [0, 1]
                imgs[i]->img_data->entries[(j-1) / 28][(j-1) % 28] = atoi(token) / 256.0;
            }
            // Move to the next token (pixel value)
            token = strtok(NULL, ",");
            j++;
        }
        i++;
    }
    // Close the file after reading
    fclose(fp);
    return imgs;
}

// Function to print an image's data and label
void img_print(Img* img) {
    matrix_print(img->img_data);
    printf("Img Label: %d\n", img->label);
}

// Function to free memory occupied by an Img instance
void img_free(Img* img) {
    matrix_free(img->img_data); // Free the image data matrix
    free(img); // Free the Img structure
    img = NULL; // Set the pointer to NULL to prevent further use
}

// Function to free memory occupied by an array of Img pointers
void imgs_free(Img** imgs, int n) {
    for (int i = 0; i < n; i++) {
        img_free(imgs[i]); // Free each Img instance in the array
    }
    free(imgs); // Free the array itself
    imgs = NULL; // Set the pointer to NULL to prevent further use
}
