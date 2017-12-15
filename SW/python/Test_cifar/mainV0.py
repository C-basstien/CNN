#import library
from PIL import Image
import numpy as np
from scipy import signal


def convolve(im,ker):#function that convolve an image array and a kernel
    
    im_width, im_height, channel=im.shape#get the dimensions of the image, image have 3 dimensions
    ker_width, ker_height,channel, n_filtre=ker.shape#get the dimensions of the kernel, image have 4 dimensions
   
    #initialisation of the matrix
    out=np.zeros((im_width,im_height,n_filtre))
    buff=np.zeros((im_width+ker_width-1,im_height+ker_height-1,n_filtre))
    
    #filtering loop
    for filter_index in range(n_filtre):#number of filter
        for color_index in range(channel):#image channel number  
            for i in range(im_width+ker_width):#width of the convolved output
                for j in range(im_height+ker_height):#height of the convolved output    
                     for k in range(ker_width):#sweep the kernel in horizontal direction
                         for l in range(ker_height):#sweep the kernel in vertical direction
                             if( i-k <0 or i-k >=im_width or j-l<0 or j-l >= im_height ):#when a coefficient is outside the 
                                 0
                             else:
                                #convolution summation and product
                                 buff[i,j,filter_index]=buff[i,j,filter_index]+im[i-k,j-l,color_index]*ker[k,l,color_index,filter_index]
                              

    out=buff[0:im_width,0:im_height,0:filter_index+1]#store the revelant part of buff in the output
    return out
def convolve2(im,ker):#convolve an 3d array with a 4d kernel
    #get the dimensions of the image and kernel
    im_width, im_height, channel=im.shape
    ker_width, ker_height,channel, n_filtre=ker.shape
    #initialisation of the matrix
    out=np.zeros((im_width,im_height,n_filtre))
    buff=np.zeros((im_width+ker_width-1,im_height+ker_height-1,n_filtre))##create output vect
    for filter_index in range(n_filtre):#number of filter
        for color_index in range(channel):#number of channel in the array
           #convolution : summation and product
           buff[:,:,filter_index]=buff[:,:,filter_index] + signal.convolve2d(im[:,:,color_index], ker[:,:,color_index,filter_index])
    out=buff[0:im_width,0:im_height,0:filter_index+1]
    return out

def relu(vect):#function for 3d array that replace by 0 the negative values stored in the array
    n_x, n_y, n_channel=vect.shape#get the dimensions
    out=vect
    for i_x in range(n_x):
        for i_y in range(n_y):
            for i_channel in range(n_channel):
                if(vect[i_x,i_y,i_channel] < 0):
                    out[i_x,i_y,i_channel]=0
    return out
def maxpool(vect):#function that return a matrix of the local maximun of the input matrix
    n_x, n_y, n_channel = vect.shape#get the dimensions
    stride=4#size of the local analyse -> ouput matrix dimension will be n_x/4, n_y/4, n_channel
    buff=np.zeros((stride,stride))#initialisation
    out=np.zeros((n_x/stride,n_y/stride,n_channel))
    for i_channel in range(n_channel):
        for i_x in range(0,n_x,stride+1):
            for i_y in range(0,n_y,stride+1):
               buff[:,:]= vect[i_x:i_x+stride,i_y:i_y+stride,i_channel]#area of analyse selection
               out[i_x/stride,i_y/stride,i_channel]=buff.max()#maximun of the area 
    return out
def reshape2 (vect,n):#return a vector of size 1xn
    return np.reshape(vect,n)
    

def matrix_multilpy(Matrix,Vect): #matrix product principle
    m_col, m_line = Matrix.shape
    print(m_col,m_line)
    out=np.zeros((m_col))
    for i_col in range(m_col):
        print("Column:")
        print(i_col)
        for i_line in range(m_line):
            print("Line:")
            print(i_line)
            print(Vect[i_line])
            out[i_col]=out[i_col]+Matrix[i_col,i_line]*Vect[i_line]
    return out
def matrix_multilpy2(Matrix,Vect): #matrix product optimized
    return np.dot(Matrix,Vect)

def softmax(vect):
    return (np.exp(vect))/(np.sum(np.exp(vect)))
        
#RGB=3
#image=numpy.zeros((x_len,y_len,RGB))
#img = mpimg.imread("image.jpg")
image = Image.open("image 256 256.jpg")
im_arr = np.array(image)
#print(im_arr.shape)
#print(im_arr)
filtre_number=64
class_number=10
ker_arr = np.random.rand(3,3,3,filtre_number)#kernel de convolution mettre d'autre coeffs plus tard
#ker_arr = np.random.rand(3,3,3,64)#kernel de convolution mettre d'autre coeffs plus tard
matrix_classe=np.random.rand(class_number,16*16*filtre_number)/10000
ker_arr2 = np.random.rand(3,3,64,filtre_number)/10000
print(ker_arr.shape)
print(ker_arr)
res_conv=convolve(im_arr,ker_arr)
print(res_conv)
res_conv2=convolve2(im_arr,ker_arr)
print("compar")
print(res_conv2)
print(res_conv-res_conv2)
res_conv2=convolve2(im_arr,ker_arr)
relu_res=relu(res_conv2)
maxp_res=maxpool(relu_res)
res_conv22=convolve2(maxp_res,ker_arr2)
relu_res2=relu(res_conv22)
maxp_res2=maxpool(relu_res2)
reschape_res=reshape2(maxp_res2,16*16*filtre_number)
matrix_prod_res=matrix_multilpy2(matrix_classe,reschape_res)
softmax_res=softmax(matrix_prod_res)
print(softmax_res)
print(sum(softmax_res))#=~1


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
