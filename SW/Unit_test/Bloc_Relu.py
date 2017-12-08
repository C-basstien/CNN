from PIL import Image
import numpy as np
from scipy import signal


# import matplotlib.pyplot as plt
# import matplotlib.image as mpimg
def convolve2D(im, ker):  # fonction qui convolue 2 le ker et l'image (matrice)
    im_width, im_height = im.shape
    ker_width, ker_height = ker.shape
    out = np.zeros((im_width, im_height))
    # print(im_width, im_height)
    # print(ker_width, ker_height)
    buff = np.zeros((im_width + ker_width - 1, im_height + ker_height - 1))  ##create output vect

    for i_w in range(im_width + ker_width):
        for j_h in range(im_height + ker_height):
            for k_w in range(ker_width):
                for l_h in range(ker_height):
                    if (i_w - k_w < 0 or i_w - k_w >= im_width or j_h - l_h < 0 or j_h - l_h >= im_height):
                        0
                    else:
                        buff[i_w, j_h] = buff[i_w, j_h] + im[i_w - k_w, j_h - l_h] * ker[k_w, l_h]
    out = buff[ker_width - 1:im_width, ker_height - 1:im_height]
    return out


im = np.matrix(   '0 1 1 1 0 0 0; 0 0 1 1 1 0 0; 0 0 0 1 1 1 0; 0 0 0 1 1 0 0; 0 0 1 1 0 0 0; 0 1 1 0 0 0 0; 1 1 0 0 0 0 0')
#im = np.matrix('5 4 5 4; 3 2 3 2; 5 4 5 4; 3 2 3 2')
ker = np.matrix('1 0 1; 0 1 0; 1 0 1')
#ker = np.matrix('0.707; 0.207')
print(im)
print(im.shape)
print ("\n")
print(ker)
convolution_result = convolve2D(im, ker)
print("convolution without lib")
print(convolution_result)
print(convolution_result.shape)
c = signal.convolve2d(im, ker, mode='valid')
print("convolution uses lib")
print(c)
print(c.shape)
