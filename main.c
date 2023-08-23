#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "img/img.h"
#include "neural/activations.h"
#include "neural/nn.h"
#include "matrix/matrix.h"
#include "matrix/ops.h"

int main() {
    srand(time(NULL));

    int choice, number_imgs, row;
    printf("Select an option:\n");
    printf("1. Train Model\n");
    printf("2. Test Model's Score\n");
    printf("3. Predict Data with Model\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            // Training
            number_imgs = 10000;
            Img** train_imgs = csv_to_imgs("./data/mnist_train.csv", number_imgs);
            NeuralNetwork* train_network = network_create(784, 300, 10, 0.1);
            network_train_batch_imgs(train_network, train_imgs, number_imgs);
            network_save(train_network, "saved_model");
            printf("Model trained and saved.\n");
            network_free(train_network);
            imgs_free(train_imgs, number_imgs);
            break;

        case 2:
            // Testing
            number_imgs = 3000;
            Img** test_imgs = csv_to_imgs("data/mnist_test.csv", number_imgs);
            NeuralNetwork* test_network = network_load("saved_model");
            double score = network_predict_imgs(test_network, test_imgs, number_imgs);
            printf("Score: %1.2f\n", score * 100);
            network_free(test_network);
            imgs_free(test_imgs, number_imgs);
            break;

        case 3:
            // Predicting
			printf("Select which row of the csv file do you want to predict?\n");
    		scanf("%d", &row);
            number_imgs = 3000;
            Matrix* output;
            Img** predict_imgs = csv_to_imgs("data/mnist_test.csv", number_imgs);
            NeuralNetwork* predict_network = network_load("saved_model");
            Img* predict_image = predict_imgs[row];
            img_print(predict_image);
            output = network_predict_img(predict_network, predict_image);
            int max_i = matrix_argmax(output);
            printf("The number is predicted to be %d.\n", max_i);
            network_free(predict_network);
            imgs_free(predict_imgs, number_imgs);
            break;

        default:
            printf("Invalid choice.\n");
            break;
    }

    return 0;
}
