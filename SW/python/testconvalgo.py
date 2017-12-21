# -*- coding: utf-8 -*-
"""
Created on Wed Dec 20 19:43:13 2017

@author: Sébastien
"""

from PIL import Image
import numpy as np
from scipy import signal

#in this file we test the different algorithm for convolution function to understand well the way to compute them in C
def convolve(im,ker):#function that convolve an image array and a kernel
#the idea algorithm of the function can be directly translated in C

    im_width, im_height=im.shape#get the dimensions of the image, image have 3 dimensions
    ker_width, ker_height=ker.shape#get the dimensions of the kernel, image have 4 dimensions

    #initialisation of the matrix
    #out=np.zeros((im_width,im_height,n_filtre))
    buff=np.zeros((im_width+ker_width-1,im_height+ker_height-1))
    for i in range(im_width+ker_width-1):#width of the convolved output
        for j in range(im_height+ker_height-1):#height of the convolved output
            for k in range(ker_width):#sweep the kernel in horizontal direction
                for l in range(ker_height):#sweep the kernel in vertical direction
                    if( i-k <0 or i-k >=im_width or j-l<0 or j-l >= im_height ):#when a coefficient is outside the
                        0
                    else:
                    #convolution summation and product
                        buff[i,j]=buff[i,j]+im[i-k,j-l,]*ker[k,l]
    return buff

#ker and im definition to compare manually the result of the C algorithm and python

tab1=np.array([[10, 3, 12, 2] ,[1, 6, 1, 2], [9, 6, 7, 12], [13, 6, 5, 2]])#image 4x4
tab2=np.array([[1, 4, 3], [2, 6, 8], [20, 5, 6]])#kernel 3x3
imsize=4
kersize=3

###uncoment this part to test with others values the result##
#imsize=4#change this value to test with others sizes
#kersize=3#change this value to test with others sizes
#tab1 = np.random.rand(imsize,imsize)#image 4x4
#tab2 = np.random.rand(kersize,kersize)#kernel 3x3
print(tab1)
print(tab2)
#Python lib function convolution function test with different mode
conv_full1=signal.convolve2d(tab1,tab2,mode='full')
conv_same1=signal.convolve2d(tab1,tab2,mode='same')
conv_valid1=signal.convolve2d(tab1,tab2,mode='valid')
print("conv_full1=\n",conv_full1)
print("conv_same1=\n",conv_same1)
print("conv_valid1=\n",conv_valid1)

conv_full2=convolve(tab1,tab2)
conv_same2=conv_full2[kersize//2:imsize+kersize//2,kersize//2:imsize+kersize//2]#indeed, same and valid modes just select a sub matrix among the full conv result
conv_valid2=conv_full2[(kersize//2)+1:imsize-(kersize//2)+1,(kersize//2)+1:imsize-(kersize//2)+1]
print("conv_full2=\n",conv_full1)
print("conv_same2=\n",conv_same1)
print("conv_valid2=\n",conv_valid1)

#check differences between python lib and our function, should be 0!
#print(conv_full1-conv_full2)
#print(conv_same1-conv_same2)
#print(conv_valid1-conv_valid2)

print("image dim: ",tab1.shape)
print("ker dim: ",tab2.shape)
#print("conv_full1 dim: ",conv_full1.shape)
print("conv_same1 dim: ",conv_same1.shape)
#print("conv_valid1 dim: ",conv_valid1.shape)
