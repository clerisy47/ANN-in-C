# C-Project

## Neural Network Handwritten Digit Recognizer
This repository contains code for a simple neural network implemented in C for recognizing handwritten digits from the MNIST dataset. The neural network uses a feedforward architecture with customizable layer sizes and activation functions. The code includes functionality for training, testing, and predicting with the trained model.

# Dependencies
Make sure you have the following libraries installed before running the code:

math.h
time.h
stdio.h
stdlib.h
Additionally, this code relies on custom header files provided in the repository:

img/img.h: Header for handling image data.
neural/activations.h: Header for defining activation functions for neural network layers.
neural/nn.h: Header for creating and manipulating the neural network.
matrix/matrix.h: Header for matrix operations.
matrix/ops.h: Header for matrix operations.

# Usage
The provided code has three main sections: training, testing, and predicting. By commenting/uncommenting the relevant sections, you can execute different tasks using the neural network.

Training
To train the neural network, follow these steps:

Uncomment the training section by removing the comment markers //.
Adjust the number_imgs variable to specify the number of images to use for training.
Ensure you have the MNIST dataset in CSV format (e.g., "data/mnist_test.csv").
Create the neural network using the network_create function with the desired layer sizes and learning rate.
Train the network using network_train_batch_imgs with the loaded images.
Save the trained network using network_save.
Run the code and the network will be trained on the specified images.

# Testing
To test the trained neural network, follow these steps:

Uncomment the testing section by removing the comment markers //.
Adjust the number_imgs variable to specify the number of images to use for testing.
Load the previously saved network using network_load.
Test the network's accuracy using network_predict_imgs.
Print the test accuracy.
Run the code to evaluate the network's performance on the test images.
# Predicting
To use the trained network for making predictions, follow these steps:

Uncomment the predicting section by removing the comment markers //.
Adjust the number_imgs variable to specify the number of images to use for prediction.
Load the previously saved network using network_load.
Load an image you want to predict.
Print the image using img_print.
Use the trained network to predict the digit in the image using network_predict_img.
Print the predicted digit.
Run the code to predict the digit in the specified image.
# Note
This code is a simplified example and may require additional optimizations and error handling for production use. Additionally, make sure to have the MNIST dataset or a compatible dataset available in the specified paths for training, testing, and predicting.

Feel free to modify and expand upon this code to create more complex neural networks or integrate it into larger projects.
