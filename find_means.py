def count_mean(image):
    x_mean = 0
    this_sum = 0

    for i, vector in enumerate(image):
        for j, pixel in enumerate(vector):
            x_mean += j * pixel
            this_sum += pixel
    x_mean /= this_sum

    y_mean = 0
    for i, vector in enumerate(image):
        for j, pixel in enumerate(vector):
            y_mean += i * pixel
    y_mean /= this_sum

    return x_mean, y_mean
