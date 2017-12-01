from PIL import Image
import numpy as np
from scipy import signal



#_________________________________
#Convolution methode 1
def convolve(im,ker):#fonction qui convolue 2 le ker et l'image (matrice)
    im_width, im_height, channel=im.shape
    #print(im.shape)
    ker_width, ker_height,channel, n_filtre=ker.shape
    #print(ker.shape)
    out=np.zeros((im_width,im_height,n_filtre))
    buff=np.zeros((im_width+ker_width-1,im_height+ker_height-1,n_filtre))##create output vect
    for filter_index in range(n_filtre):
        for color_index in range(channel):#RGB mapping  
            for i in range(im_width+ker_width):
                #print(i)
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
    out=buff[0:im_width,0:im_height,0:filter_index+1]
    return out


#_________________________________
#Convolution methode 2
def convolve2(im,ker):
    im_width, im_height, channel=im.shape
    #print(im.shape)
    ker_width, ker_height,channel, n_filtre=ker.shape
    #print(ker.shape)
    out=np.zeros((im_width,im_height,n_filtre))
    buff=np.zeros((im_width+ker_width-1,im_height+ker_height-1,n_filtre))##create output vect
    for filter_index in range(n_filtre):
        for color_index in range(channel):#RGB mapping 
            buff[:,:,filter_index]=buff[:,:,filter_index] + signal.convolve2d(im[:,:,color_index], ker[:,:,color_index,filter_index])
            #temp=signal.convolve2d(im[:,:,color_index], ker[:,:,color_index,filter_index])
    out=buff[0:im_width,0:im_height,0:filter_index+1]
    return out


#__________________________________
#RELU
def relu(vect):
    n_x, n_y, n_channel=vect.shape
    out=vect
    for i_x in range(n_x):
        for i_y in range(n_y):
            for i_channel in range(n_channel):
                if(vect[i_x,i_y,i_channel] < 0):
                    out[i_x,i_y,i_channel]=0
    return out


#__________________________________
#MAXPOOL

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
def reshape2 (vect,n):
    return np.reshape(vect,n)


#__________________________________
#main_
image = Image.open("image 256 256.jpg")
im_arr = np.array(image)# Tao ra mang 3x3
#print(im_arr)
#print(im_arr.shape) #Ket quat: (256, 256, 3)

#__________________________________
filtre_number=64
class_number=10
ker_arr = np.random.rand(3,3,3,filtre_number)#kernel de convolution mettre d'autre coeffs plus tard
#print("ker_arr")
#print(ker_arr)
#print("ker_arr.shape")
#print(ker_arr.shape) #Ket qua: (3, 3, 3, filtre_number)

#il ser a quoi?
matrix_classe=np.random.rand(class_number,16*16*filtre_number)/10000
#print(matrix_classe.shape) #Ket qua: (10, 256*64)

#pourquoi tu divise ker_arr2 par 1000?
ker_arr2 = np.random.rand(3,3,64,filtre_number)/10000
#print(ker_arr.shape)

#____________________________________
#CONVOLUTION
#Methode 1
res_conv=convolve(im_arr,ker_arr)

#Methode 2
res_conv2=convolve2(im_arr,ker_arr)

#Comparer entre les deux
#print(res_conv-res_conv2)

#Relu
relu_res=relu(res_conv2)
#print(res_conv2)

#Maxpool
maxp_res=maxpool(relu_res)

#Conolution, relu, maxp 2 (Methode 2) with ker_arr2
res_conv22=convolve2(maxp_res,ker_arr2)
relu_res2=relu(res_conv22)
maxp_res2=maxpool(relu_res2)

reschape_res=reshape2(maxp_res2,16*16*filtre_number)
