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
           buff[:,:,filter_index]=buff[:,:,filter_index] + signal.convolve2d(im[:,:,color_index], ker[:,:,color_index,filter_index])
            #temp=signal.convolve2d(im[:,:,color_index], ker[:,:,color_index,filter_index])
    out=buff[0:im_width,0:im_height,0:4]
    return out

def relu(vect):
    n_x, n_y, n_channel=vect.shape
    out=vect
    for i_x in range(n_x):
        for i_y in range(n_y):
            for i_channel in range(n_channel):
                if(vect[i_x,i_y,i_channel] < 0):
                    out[i_x,i_y,i_channel]=0
    return out
def maxpool(vect):
    n_x, n_y, n_channel = vect.shape
   # print(n_x)
    #print(n_y)
    stride=4
    buff=np.zeros((stride,stride))
    out=np.zeros((n_x/stride,n_y/stride,n_channel))
    for i_channel in range(n_channel):
        for i_x in range(0,n_x,stride+1):
            for i_y in range(0,n_y,stride+1):
               buff[:,:]= vect[i_x:i_x+stride,i_y:i_y+stride,i_channel]
              # print(buff)
               #print(buff.shape)
               out[i_x/stride,i_y/stride,i_channel]=buff.max()
               #out[i_x/stride,i_y/stride,i_channel]
               #np.amax(buff, axis=1)
    return out
def reshape1 (vect,n):
    return np.reshape(vect,n)
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
#print(ker_arr)
#res_conv=convolve(im_arr,ker_arr)
#print(res_conv)
res_conv2=convolve2(im_arr,ker_arr)
print("compar")
print(res_conv2)
#print(res_conv-res_conv2)
relu_res=relu(res_conv2)
maxp_res=maxpool(res_conv2)
print(maxp_res)
reshp_res=reshape1(maxp_res,64*64)

#print(res_conv2)
#width, height = image.size
#print()
#mpimg.
#imgplot = plt.imshow(img)
#plt.show()
#data = list(im.getdata())
