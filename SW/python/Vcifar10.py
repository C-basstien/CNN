from PIL import Image
import numpy as np
#import matplotlib.pyplot as plt
#import matplotlib.image as mpimg
from scipy import signal

def read_cifar10(filename_queue):
  """Reads and parses examples from CIFAR10 data files.
  Recommendation: if you want N-way read parallelism, call this function
  N times.  This will give you N independent Readers reading different
  files & positions within those files, which will give better mixing of
  examples.
  Args:
    filename_queue: A queue of strings with the filenames to read from.
  Returns:
    An object representing a single example, with the following fields:
      height: number of rows in the result (32)
      width: number of columns in the result (32)
      depth: number of color channels in the result (3)
      key: a scalar string Tensor describing the filename & record number
        for this example.
      label: an int32 Tensor with the label in the range 0..9.
      uint8image: a [height, width, depth] uint8 Tensor with the image data
  """

  class CIFAR10Record(object):
    pass
  result = CIFAR10Record()

  # Dimensions of the images in the CIFAR-10 dataset.
  # See http://www.cs.toronto.edu/~kriz/cifar.html for a description of the
  # input format.
  label_bytes = 1  # 2 for CIFAR-100
  result.height = 32
  result.width = 32
  result.depth = 3
  image_bytes = result.height * result.width * result.depth
  # Every record consists of a label followed by the image, with a
  # fixed number of bytes for each.
  record_bytes = label_bytes + image_bytes

  # Read a record, getting filenames from the filename_queue.  No
  # header or footer in the CIFAR-10 format, so we leave header_bytes
  # and footer_bytes at their default of 0.
  reader = tf.FixedLengthRecordReader(record_bytes=record_bytes)
  result.key, value = reader.read(filename_queue)

  # Convert from a string to a vector of uint8 that is record_bytes long.
  record_bytes = tf.decode_raw(value, tf.uint8)

  # The first bytes represent the label, which we convert from uint8->int32.
  result.label = tf.cast(
      tf.strided_slice(record_bytes, [0], [label_bytes]), tf.int32)

  # The remaining bytes after the label represent the image, which we reshape
  # from [depth * height * width] to [depth, height, width].
  depth_major = tf.reshape(
      tf.strided_slice(record_bytes, [label_bytes],
                       [label_bytes + image_bytes]),
      [result.depth, result.height, result.width])
  # Convert from [depth, height, width] to [height, width, depth].
  result.uint8image = tf.transpose(depth_major, [1, 2, 0])

  return result
def troncature(im):#this function withdraw the border of an image to obtain a 24x24image 
    im_width, im_height, channel=im.shape
    if (im_width < 24 or im_height < 24):
        print("Error, uncorrect image size")
        return
    else:
        im_tronc=np.zeros((24,24,channel))
        im_tronc[:,:,:]=im[(im_width/2)-1-12:(im_width/2)-1+12,(im_height/2)-1-12:(im_height/2)-1+12,:]
    return im_tronc
def normalization(im):
    im_width, im_height, channel=im.shape
    mean=np.zeros(channel)
    delta=np.zeros(channel)
    im_norm=im
    mean=np.mean(im[:,:,:])
    delta= sqrt(np.mean((im[:,:,:]-mean)**2))
    im_norm[:,:,:]=(im[:,:,:]-mean)/max(delta,1/sqrt(im_width*im_height*channel))
    return im_norm
    
def convolve(im,ker,biases):
    im_width, im_height, channel=im.shape
    #print(im.shape)
    ker_width, ker_height,channel, n_filtre=ker.shape
    #print(ker.shape)
    out=np.zeros((im_width,im_height,n_filtre))
    ##buff=np.zeros((im_width+ker_width-1,im_height+ker_height-1,n_filtre))##create output vect
    for filter_index in range(n_filtre):
        for color_index in range(channel):#RGB mapping 
           out[:,:,filter_index]=out[:,:,filter_index] + signal.convolve2d(im[:,:,color_index], ker[:,:,color_index,filter_index],mode='same')
            #temp=signal.convolve2d(im[:,:,color_index], ker[:,:,color_index,filter_index])
    out=buff[:,:,0:filter_index+1]+biases[0:filter_index+1]
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
    stride=2
    size=3
    buff=np.zeros((stride,stride))
    out=np.zeros((n_x/stride,n_y/stride,n_channel))
    for i_channel in range(n_channel):
        for i_x in range(0,n_x,stride):
            for i_y in range(0,n_y,stride):
               buff[:,:]= vect[i_x:i_x+size,i_y:i_y+size,i_channel]
              # print(buff)
               #print(buff.shape)
               out[i_x/stride,i_y/stride,i_channel]=buff.max()
               #out[i_x/stride,i_y/stride,i_channel]
               #np.amax(buff, axis=1)
    return out
def reshape (vect,n):
    return np.reshape(vect,n)
def matrix_multilpy(Matrix,Vect):
    return np.dot(Matrix,Vect)
def softmax(vect):
    return (np.exp(vect))/(np.sum(np.exp(vect)))
        
#RGB=3
#image=numpy.zeros((x_len,y_len,RGB))
#img = mpimg.imread("image.jpg")
image = Image.open("image 256 256.jpg")
im_arr = np.array(image)#creer un tableau h * l * 3
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
