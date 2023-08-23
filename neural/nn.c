// Include necessary header files
#include "nn.h"
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../matrix/ops.h"
#include "../neural/activations.h"

// Define a maximum character limit for reading lines from files
#define MAXCHAR 1000

// Function to create a new NeuralNetwork instance
NeuralNetwork* network_create(int input, int hidden, int output, double lr) {
    NeuralNetwork* net = malloc(sizeof(NeuralNetwork));
    net->input = input;
    net->hidden = hidden;
    net->output = output;
    net->learning_rate = lr;
    Matrix* hidden_layer = matrix_create(hidden, input);
    Matrix* output_layer = matrix_create(output, hidden);
    matrix_randomize(hidden_layer, hidden);
    matrix_randomize(output_layer, output);
    net->hidden_weights = hidden_layer;
    net->output_weights = output_layer;
    return net;
}

// Function to train the neural network using backpropagation
void network_train(NeuralNetwork* net, Matrix* input, Matrix* output) {
    // Calculate forward pass through the network
    Matrix* hidden_inputs = dot(net->hidden_weights, input);
    Matrix* hidden_outputs = apply(sigmoid, hidden_inputs);
    Matrix* final_inputs = dot(net->output_weights, hidden_outputs);
    Matrix* final_outputs = apply(sigmoid, final_inputs);

    // Calculate output errors and backpropagate
    Matrix* output_errors = subtract(output, final_outputs);
    Matrix* transposed_mat = transpose(net->output_weights);
    Matrix* hidden_errors = dot(transposed_mat, output_errors);
    matrix_free(transposed_mat);

    // Calculate updates for output weights
    Matrix* sigmoid_primed_mat = sigmoidPrime(final_outputs);
    Matrix* multiplied_mat = multiply(output_errors, sigmoid_primed_mat);
    transposed_mat = transpose(hidden_outputs);
    Matrix* dot_mat = dot(multiplied_mat, transposed_mat);
    Matrix* scaled_mat = scale(net->learning_rate, dot_mat);
    Matrix* added_mat = add(net->output_weights, scaled_mat);

    matrix_free(net->output_weights);
    net->output_weights = added_mat;

    // Free intermediate matrices
    matrix_free(sigmoid_primed_mat);
    matrix_free(multiplied_mat);
    matrix_free(transposed_mat);
    matrix_free(dot_mat);
    matrix_free(scaled_mat);

    // Calculate updates for hidden weights
    sigmoid_primed_mat = sigmoidPrime(hidden_outputs);
    multiplied_mat = multiply(hidden_errors, sigmoid_primed_mat);
    transposed_mat = transpose(input);
    dot_mat = dot(multiplied_mat, transposed_mat);
    scaled_mat = scale(net->learning_rate, dot_mat);
    added_mat = add(net->hidden_weights, scaled_mat);

    matrix_free(net->hidden_weights);
    net->hidden_weights = added_mat;

    // Free intermediate matrices
    matrix_free(sigmoid_primed_mat);
    matrix_free(multiplied_mat);
    matrix_free(transposed_mat);
    matrix_free(dot_mat);
    matrix_free(scaled_mat);

    // Free matrices used in the forward pass
    matrix_free(hidden_inputs);
    matrix_free(hidden_outputs);
    matrix_free(final_inputs);
    matrix_free(final_outputs);
    matrix_free(output_errors);
    matrix_free(hidden_errors);
}

// Function to train the neural network using batch of images
void network_train_batch_imgs(NeuralNetwork* net, Img** imgs, int batch_size) {
    for (int i = 0; i < batch_size; i++) {
        if (i % 100 == 0) printf("Img No. %d\n", i);
        Img* cur_img = imgs[i];
        Matrix* img_data = matrix_flatten(cur_img->img_data, 0);
        Matrix* output = matrix_create(10, 1);
        output->entries[cur_img->label][0] = 1;
        network_train(net, img_data, output);
        matrix_free(output);
        matrix_free(img_data);
    }
}

// Function to predict output for a single image
Matrix* network_predict_img(NeuralNetwork* net, Img* img) {
    Matrix* img_data = matrix_flatten(img->img_data, 0);
    Matrix* res = network_predict(net, img_data);
    matrix_free(img_data);
    return res;
}

// Function to predict output for a batch of images and calculate accuracy
double network_predict_imgs(NeuralNetwork* net, Img** imgs, int n) {
    int n_correct = 0;
    for (int i = 0; i < n; i++) {
        Matrix* prediction = network_predict_img(net, imgs[i]);
        if (matrix_argmax(prediction) == imgs[i]->label) {
            n_correct++;
        }
        matrix_free(prediction);
    }
    return 1.0 * n_correct / n;
}

// Function to predict output for a given input data
Matrix* network_predict(NeuralNetwork* net, Matrix* input_data) {
    // Calculate forward pass through the network
    Matrix* hidden_inputs = dot(net->hidden_weights, input_data);
    Matrix* hidden_outputs = apply(sigmoid, hidden_inputs);
    Matrix* final_inputs = dot(net->output_weights, hidden_outputs);
    Matrix* final_outputs = apply(sigmoid, final_inputs);
    Matrix* result = softmax(final_outputs);

    // Free matrices used in the forward pass
    matrix_free(hidden_inputs);
    matrix_free(hidden_outputs);
    matrix_free(final_inputs);
    matrix_free(final_outputs);

    return result;
}

// Function to save the neural network's weights and structure to files
void network_save(NeuralNetwork* net, char* file_string) {
    mkdir(file_string, 0777);
    chdir(file_string);

    // Save network structure to "descriptor" file
    FILE* descriptor = fopen("descriptor", "w");
    fprintf(descriptor, "%d\n", net->input);
    fprintf(descriptor, "%d\n", net->hidden);
    fprintf(descriptor, "%d\n", net->output);
    fclose(descriptor);

    // Save hidden and output weights
    matrix_save(net->hidden_weights, "hidden");
    matrix_save(net->output_weights, "output");

    printf("Successfully written to '%s'\n", file_string);
    chdir("-");
}

// Function to load a previously saved neural network from files
NeuralNetwork* network_load(char* file_string) {
    NeuralNetwork* net = malloc(sizeof(NeuralNetwork));
    char entry[MAXCHAR];
    chdir(file_string);

    // Load network structure from "descriptor" file
    FILE* descriptor = fopen("descriptor", "r");
    fgets(entry, MAXCHAR, descriptor);
    net->input = atoi(entry);
    fgets(entry, MAXCHAR, descriptor);
    net->hidden = atoi(entry);
    fgets(entry, MAXCHAR, descriptor);
    net->output = atoi(entry);
    fclose(descriptor);

    // Load hidden and output weights
    net->hidden_weights = matrix_load("hidden");
    net->output_weights = matrix_load("output");

    printf("Successfully loaded network from '%s'\n", file_string);
    chdir("-");
    return net;
}

// Function to print the structure and weights of the neural network
void network_print(NeuralNetwork* net) {
    printf("# of Inputs: %d\n", net->input);
    printf("# of Hidden: %d\n", net->hidden);
    printf("# of Output: %d\n", net->output);
    printf("Hidden Weights: \n");
    matrix_print(net->hidden_weights);
    printf("Output Weights: \n");
    matrix_print(net->output_weights);
}

// Function to free memory occupied by a NeuralNetwork instance
void network_free(NeuralNetwork *net) {
    matrix_free(net->hidden_weights);
    matrix_free(net->output_weights);
    free(net);
    net = NULL;
}
