from PIL import Image
import numpy as np
#import matplotlib.pyplot as plt
#import matplotlib.image as mpimg
from scipy import signal
def convolve(im,ker):#fonction qui convolue 2 le ker et l'image (matrice)
    im_width, im_height, RGB=im.shape
    #print(im.shape)
    ker_width, ker_height,RGB, n_filtre=ker.shape
    #print(ker.shape)
    out=np.zeros((im_width,im_height,n_filtre))
    buff=np.zeros((im_width+ker_width-1,im_height+ker_height-1,n_filtre))##create output vect
    for filter_index in range(n_filtre):
        for color_index in range(3):#RGB mapping  
            for i in range(im_width+ker_width):
                print(i)
                for j in range(im_height+ker_height):    
                    #convolution summation
                     for k in range(ker_width):
                         for l in range(ker_height):
                             if( i-k <0 or i-k >=im_width or j-l<0 or j-l >= im_height ):
                                 0
                             else:
                                 buff[i,j,filter_index]=buff[i,j,filter_index]+im[i-k,j-l,color_index]*ker[k,l,color_index,filter_index]
                              #                   if(i>ker_height )
 #                   else
    out=buff[0:im_width,0:im_height,0:4]
    return out
def convolve2(im,ker):
    im_width, im_height, RGB=im.shape
    #print(im.shape)
    ker_width, ker_height,RGB, n_filtre=ker.shape
    #print(ker.shape)
    out=np.zeros((im_width,im_height,n_filtre))
    buff=np.zeros((im_width+ker_width-1,im_height+ker_height-1,n_filtre))##create output vect
    for filter_index in range(n_filtre):
        for color_index in range(3):#RGB mapping 
            buff[:,:,n_filtre]=buff[:,:,n_filtre] + signal.convolve2d(im, ker)
    out=buff[0:im_width,0:im_height,0:4]
    return out


#RGB=3
#image=numpy.zeros((x_len,y_len,RGB))
#img = mpimg.imread("image.jpg")
image = Image.open("image 256 256.jpg")
im_arr = np.array(image)
print(im_arr.shape)
print(im_arr)
ker_arr = np.random.rand(3,3,3,1)#kernel de convolution mettre d'autre coeffs plus tard
#ker_arr = np.random.rand(3,3,3,64)#kernel de convolution mettre d'autre coeffs plus tard

print(ker_arr.shape)
print(ker_arr)
res_conv=convolve(im_arr,ker_arr)
#print(res_conv)
res_conv2=convolve(im_arr,ker_arr)
#print(res_conv2)
print(np.array_equal(res_conv,res_conv2))
#width, height = image.size
#print()
#mpimg.
#imgplot = plt.imshow(img)
#plt.show()
#data = list(im.getdata())
