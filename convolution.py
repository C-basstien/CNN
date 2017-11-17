#Sw implementation of CNN
from PIL import Image
import numpy
#import matplotlib.pyplot as plt
#import matplotlib.image as mpimg

def convolve(im,ker):#fonction qui convolue 2 image ensemble
im_width, im_height = im.size 
ker_width, ker_height = ker.size 
#create vect
for c in range(3):
 for i in range(im_widt)
   for j in range(im_height)
       out(i,j,c)=out(i,j,c)+imge(im_widt+ker_widt-1-i,im_height+ker_height-1,c)*kern(i,j,c)
return out

#RGB=3
#image=numpy.zeros((x_len,y_len,RGB))
#img = mpimg.imread("image.jpg")
image = Image.open("image.jpg")
kernel = Image.open("kernel.jpg")
#width, height = image.size
#print()
#mpimg.
#imgplot = plt.imshow(img)
#plt.show()
#data = list(im.getdata())
