from PIL import Image
import numpy as np
#import matplotlib.pyplot as plt
#import matplotlib.image as mpimg
from scipy import signal
def troncature(im):#return a 24*24*3 image taken from the center part of the image
    im_width, im_height, channel=im.shape#get the dimensions
    if (im_width < 24 or im_height < 24):
        print("Error, uncorrect image size")
        return
    else:
        im_tronc=np.zeros((24,24,channel))
        im_tronc[:,:,:]=im[(im_width/2)-1-12:(im_width/2)-1+12,(im_height/2)-1-12:(im_height/2)-1+12,:]#take the image center
    return im_tronc
def normalization(im):#normalization function to modify according to tensorflow cifar 10 tutorial
    im_width, im_height, channel=im.shape
    mean=np.zeros(channel)
    delta=np.zeros(channel)
    im_norm=im
    for i in range(channel):#wrong the mean and variations calculation is done on all the image
        mean[i]=np.mean(im[:,:,i])
    for i in range(channel):
       delta[i]= sqrt(np.sum((im[:,:,i]-mean[i])*(im[:,:,i]-mean[i]))/(im_width*im_height))
       im_norm[:,:,i]=(im[:,:,i]-mean[1])/max(delta[i],1/sqrt(im_width*im_height))
    return im_norm
    
def convolve(im,ker,biases):#convolution function including biases
    im_width, im_height, channel=im.shape#get the dimensions of the input matrix
    ker_width, ker_height,channel, n_filtre=ker.shape #get the dimensions of the input kernel
    out=np.zeros((im_width,im_height,n_filtre))#initialization of output
    buff=np.zeros((im_width+ker_width-1,im_height+ker_height-1,n_filtre))##create output vect
    for filter_index in range(n_filtre):#number of the filter 
        for color_index in range(channel):#number of channel of the input matrix
           buff[:,:,filter_index]=buff[:,:,filter_index] + signal.convolve2d(im[:,:,color_index], ker[:,:,color_index,filter_index])
    out=buff[0:im_width,0:im_height,0:filter_index+1]+biases[0:filter_index+1]#take the revelant part of the signal
    return out

def relu(vect):#return a matrix with positive coefficient
    n_x, n_y, n_channel=vect.shape#get the dimensions
    out=vect
    for i_x in range(n_x):
        for i_y in range(n_y):
            for i_channel in range(n_channel):
                if(vect[i_x,i_y,i_channel] < 0):
                    out[i_x,i_y,i_channel]=0#if a a coefficent is negative then it's replace by 0
    return out
def maxpool(vect):
    n_x, n_y, n_channel = vect.shape#get the dimensions of the matrix
    stride=2#step between zones of analyse
    size=3#area of analyse 3*3blocs
    buff=np.zeros((stride,stride))#initialization
    out=np.zeros((n_x/stride,n_y/stride,n_channel))
    for i_channel in range(n_channel):#number of channel in the matrix
        for i_x in range(0,n_x,stride):#boucle of 
            for i_y in range(0,n_y,stride):
               buff[:,:]= vect[i_x:i_x+size,i_y:i_y+size,i_channel]#get the local area of analisis
               out[i_x/stride,i_y/stride,i_channel]=buff.max()#ge
    return out
def reshape (vect,n):
    return np.reshape(vect,n)
def matrix_multilpy(Matrix,Vect):
    return np.dot(Matrix,Vect)
def softmax(vect):
    return (np.exp(vect))/(np.sum(np.exp(vect)))
        
    
#BENCH PARTS HERE
#USE THE DIFFERENT FUNCTION TO TEST THE CIFAR10 LAYER
#RGB=3
#image=numpy.zeros((x_len,y_len,RGB))
#img = mpimg.imread("image.jpg")
image = Image.open("image 256 256.jpg")
im_arr = np.array(image)
Zim_norm=normalization(troncature(im_arr))
#print(im_arr.shape)
#print(im_norm)
#filtre_number=64
#class_number=10
#ker_arr = np.random.rand(3,3,3,filtre_number)#kernel de convolution mettre d'autre coeffs plus tard
#ker_arr = np.random.rand(3,3,3,64)#kernel de convolution mettre d'autre coeffs plus tard
#matrix_classe=np.random.rand(class_number,16*16*filtre_number)/10000
#ker_arr2 = np.random.rand(3,3,64,filtre_number)/10000
#print(ker_arr.shape)
#print(ker_arr)
#res_conv=convolve(im_arr,ker_arr)
#print(res_conv)
#res_conv2=convolve2(im_arr,ker_arr)
#print("compar")
#print(res_conv2)
#print(res_conv-res_conv2)
#res_conv2=convolve2(im_arr,ker_arr)
#relu_res=relu(res_conv2)
#maxp_res=maxpool(relu_res)
#res_conv22=convolve2(maxp_res,ker_arr2)
#relu_res2=relu(res_conv22)
#maxp_res2=maxpool(relu_res2)
#reschape_res=reshape2(maxp_res2,16*16*filtre_number)
#matrix_prod_res=matrix_multilpy2(matrix_classe,reschape_res)
#softmax_res=softmax(matrix_prod_res)
#print(softmax_res)
#print(sum(softmax_res))#=~1


#m=np.random.rand(2,3)
#print(m)
#v=np.random.rand(3,1)
#print(v)
#print(matrix_multilpy(m,v))
#print(matrix_multilpy2(m,v))


#print(maxp_res)
#reshp_res=reshape1(maxp_res,64*64*64)

#print(res_conv2)
#width, height = image.size
#print()
#mpimg.
#imgplot = plt.imshow(img)
#plt.show()
#data = list(im.getdata())
