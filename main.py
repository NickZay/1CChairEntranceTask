import cv2 as cv
import numpy as np

image_path = "C:\\Users\\zaits\\Desktop\\Python\\circle.png"  # input()
print(image_path)

image__ = cv.imread(image_path)
image_ = np.sum(image__, axis=2)
image = np.vectorize(lambda x: 765 - x)(image_)

from find_means import count_mean
image_mean_x, image_mean_y = count_mean(image)

points = list()
visited = np.zeros(image.shape, dtype=int)

more_than = lambda x: x > 380

for i, j in visited.shape:
    if more_than(image[i][j]) and not visited[i][j]:
        #dfs()
        pass