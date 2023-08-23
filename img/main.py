import numpy as np
import matplotlib.pyplot as plt

print("Enter the 28x28 matrix (each row on a new line, values separated by spaces):")
matrix_string = ""
for _ in range(28):
    line = input()
    matrix_string += line + "\n"

rows = matrix_string.strip().split('\n')
image_matrix = np.array([list(map(float, row.split())) for row in rows])

plt.imshow(image_matrix, cmap='gray')
plt.axis('off') 
plt.title("Image Display")
plt.show()

