from scipy import signal
from PIL import Image
import sys
sys.path.insert(0,'../') # to specify python code exist in another folder
import numpy as np
np.set_printoptions(threshold=np.inf) # to forced full print of numpy array
import adaptation_image as normal
import load_file as wload
import load_database as Db
import Vcifar10 as Vcifar10
import math

#def accuracy(imgClassPredicted,imgReadClass,missPredictionNum,totalImageRead):
 #   if imgClassPredicted != imgReadClass:
  #      missPredictionNum+=1

   # accuracy=(totalImageRead-missPredictionNum)/totalImageRead
    #return accuracy

#def accuracy(imgClassPredicted,imgReadClass,goodPredictionNum,totalImageRead):
 #   if imgClassPredicted == imgReadClass:
  #      goodPredictionNum+=1
   # 
    #accuracy=float((goodPredictionNum))/float(totalImageRead)*100.0
    #return accuracy,goodPredictionNum

def accuracy(imgClassPredicted,imgReadClass,goodPredictionNum,totalImageRead):
    if imgClassPredicted == imgReadClass:
        goodPredictionNum+=1
    
    accuracy=float((goodPredictionNum))/float(totalImageRead)*100.0
    return accuracy,goodPredictionNum
imgClassPredicted=0
imgReadClass=0
missPredictionNum=0
totalImgRead=0
totalImg=2
accuracyCalc=(0,0)
#kernel parameters
convLayer1_channelNum=64
convLayer2_channelNum=32
convLayer3_channelNum=20
kernelConvSize=5
kernelImageChannelConvLayer1=3
kernelImageChannelConvLayer2=64
kernelImageChannelConvLayer3=32

#pooling parameter
poolingHeight=3
poolingWidth=3
poolingStride=2
poolingType='max'
poolingMode='SAME'
poolingPos='false' #before RELU (true) or not

# Loading image database 
#db=cifarDb.readDatabase('data_batch_1.bin')

# Allocating bias matrix + kernel + fcLayer Matrix
biasConvLayer1=np.zeros((1,1,convLayer1_channelNum))
biasConvLayer2=np.zeros((1,1,convLayer2_channelNum))
biasConvLayer3=np.zeros((1,1,convLayer3_channelNum))

"""
kernelConvLayer1=np.zeros((kernelImageChannelConvLayer1,convLayer1_channelNum,
                           kernelConvSize,kernelConvSize))
kernelConvLayer2=np.zeros((kernelImageChannelConvLayer2,convLayer2_channelNum,
                           kernelConvSize,kernelConvSize))
kernelConvLayer3=np.zeros((kernelImageChannelConvLayer3,convLayer3_channelNum,
                           kernelConvSize,kernelConvSize))
"""

kernelConvLayer1=np.zeros((kernelConvSize,kernelConvSize,kernelImageChannelConvLayer1,convLayer1_channelNum))
kernelConvLayer2=np.zeros((kernelConvSize,kernelConvSize,kernelImageChannelConvLayer2,convLayer2_channelNum))
kernelConvLayer3=np.zeros((kernelConvSize,kernelConvSize,kernelImageChannelConvLayer3,convLayer3_channelNum))

biasFClayer=np.zeros((1,10))

fcVectorLayer=np.zeros((180,10))


# Loading weights

weightFilename='CNN_coeff_'+str(kernelConvSize)+'x'+str(kernelConvSize)+'_mod.txt'

wload.loadWeightFromFile(weightFilename,kernelConvLayer1,kernelConvLayer2,kernelConvLayer3,
                         biasConvLayer1,biasConvLayer2,biasConvLayer3,fcVectorLayer,biasFClayer)


db= Db.readDatabase('/home/le/Desktop/SysC/De_Algo_a_Arch/cifar/cifar-10-batches-py/data_batch_1') #change your path 

for num in range (0,totalImg):
    imgIn= Db.readImgFromDatabase(db,num)
    cnnInputLayerMatrix = imgIn[0]
    imgReadClass=imgIn[1]

   # print(cnnInputLayerMatrix)
    #cnnInputLayerMatrix1= Vcifar10.troncature(cnnInputLayerMatrix)
    #cnnInputLayerMatrix1= Vcifar10.normalization(cnnInputLayerMatrix1)
    cnnInputLayerMatrix1=normal.adapatation_imag(cnnInputLayerMatrix)	
    #print(cnnInputLayerMatrix1.max())
    #RELU1

  #  print(biasConvLayer1[0,0,:])
   # print(cnnInputLayerMatrix1)
   # print(cnnInputLayerMatrix.shape)
   # print(kernelConvLayer1.shape)
   # print( biasConvLayer1[0,0,:].shape)

    #print(cnnConv1LayerMatrix.shape)
    print(kernelConvLayer1.shape)
    print(biasConvLayer1.shape)
    
    cnnConv1LayerMatrix = Vcifar10.convolve(cnnInputLayerMatrix1, kernelConvLayer1, biasConvLayer1[0,0,:])
    cnnConv1LayerMatrix = Vcifar10.relu(cnnConv1LayerMatrix)
    print(cnnConv1LayerMatrix.shape)
    #Maxpool1
    cnnConv1LayerMatrix = Vcifar10.maxpool(cnnConv1LayerMatrix)

    print(cnnConv1LayerMatrix.shape)

    # Using kernelConvLayer2, biasConvLayer2
    #RELU2
    print("Layer 2")
    
   # print(kernelConvLayer2.shape)
   # print(biasConvLayer2[0, 0, :].shape)
    cnnConv2LayerMatrix = Vcifar10.convolve(cnnConv1LayerMatrix,  kernelConvLayer2, biasConvLayer2[0,0,:])
    cnnConv2LayerMatrix = Vcifar10.relu(cnnConv2LayerMatrix)
    #Maxpool2
    cnnConv2LayerMatrix = Vcifar10.maxpool(cnnConv2LayerMatrix)
    #print(cnnConv2LayerMatrix.shape)
    # Using kernelConvLayer3, biasConvLayer3
    #RELU3

    cnnConv3LayerMatrix = Vcifar10.convolve(cnnConv2LayerMatrix,  kernelConvLayer3, biasConvLayer3[0,0,:])
    cnnConv3LayerMatrix = Vcifar10.relu(cnnConv3LayerMatrix)
#Maxpool3
    cnnConv3LayerMatrix = Vcifar10.maxpool(cnnConv3LayerMatrix)
    #print(cnnConv3LayerMatrix.shape)
#Maxpool3
    cnnConv3LayerReshape = Vcifar10.reshape(cnnConv3LayerMatrix, 180)
    #print(cnnConv3LayerReshape.shape)
    #print(fcVectorLayer.shape)
    #print(fcVectorLayer)
    cnnFullyConnectedLayer = Vcifar10.matrix_multilpy( fcVectorLayer.transpose(),cnnConv3LayerReshape)
    #print(cnnFullyConnectedLayer.shape)
    outputVector = Vcifar10.softmax(cnnFullyConnectedLayer)
    totalImgRead+=1	
    print(outputVector)
    imgClassPredicted = outputVector.argmax()	
    #imgClassPredicted=cnnFullyConnectedLayer.argmax()
    print(imgReadClass)
    print(totalImgRead)
    print(imgClassPredicted)
    print(imgReadClass)
    print(missPredictionNum)
    accuracyCalc = accuracy(imgClassPredicted,imgReadClass,accuracyCalc[1],totalImgRead)
    print("--> accuracy = %f (prc)" %accuracyCalc[0])
    print('--> progression = %d/%d' %(totalImgRead,totalImg))
    #print('--> accuracy = %f',accuracy(imgClassPredicted,imgReadClass,missPredictionNum,totalImgRead))
    #print('--> progression = %d/%d',totalImgRead,totalImg)
    
    

    
