# -*- coding: utf-8 -*-
"""
Created on Mon Dec  4 20:35:18 2017

@author: gaell
"""
#from convolution.py import *
import numpy as np
from numpy import *

#Ouverture du fichier
def read_file():
    f = open('CNN_coeff_3x3.txt', 'r')
    #print(f)
    #print(type(f))
    contenu = f.read()
    #print(contenu)
    #mon_fichier = open("fichier_coeff.txt", "w") 
    objet = contenu.split("tensor_name:")
    obj_ret = []
    data_ret = []
    #print(objet)
    for i in range (2): #len(objet)-1):
        print("objet[",i+1,"] =")
        #print(objet[i+1])
        data = objet[i+1].split()
        #print(len(data))
        for j in range (len(data)):
            #print(data[j].strip('['))
            data[j] = data[j].strip('[')
            data[j] = data[j].strip(']')
            str_search = "e-"
            str_search2 = "e+"
            if ((data[j].find(str_search)!= -1 or data[j].find(str_search2) != -1) and data[j] != "conv1/biases" and data[j] != "conv1/weights" and data[j] != "conv2/biases" and data[j] != "conv2/weights" and data[j] != "conv3/biases" and data[j] != "conv3/weights" and data[j] != "local3/biases" and data[j] != "local3/biases"):
                #print("dans le if avec data[",j,"]=",data[j])
                data[j]=float(data[j])
            if (data[j] != ""):
                data_ret.append(data[j])
        print("objet_data_ret[",i+1,"] =")
        #print(data_ret)
        #obj_ret.append(data_ret)
    #print(obj_ret)
    return obj_ret

def convert_list_to_array(list):
    array_ret= np.array([],array)
    
    return array_ret

def matrix(x, y):
    M = numpy.ones((x,y))
    return M

def biais(matrix, m_biases, canal): #OK
    matrix_out = matrix + float(m_biases[canal])
    #print(float(m_biases[canal]))
    return matrix_out
    

valeur = read_file()
matrix = matrix(3,3)
matrix_out= biais(matrix, valeur[0] , 3)
print (matrix_out)
out = convert_list_to_array(valeur)
print(out)





    #mon_fichier.close
    #f.closed

#separation tous les tensor name
#for objet in contenu.split("tensor_name:"):
    #print(objet)
    #objet.strip()
    #print(objet)
    #objet.split('[')
    
    #pour chaque lot de données on les met dans une variable correspondante
    #if objet[0]=="conv1/biases":
       # print("conv1 biases")
       # conv1_biases = []
       # data = objet[1].split()
       # print(data)
        #on met les données dans une liste
       # for i in range (len(data)-2):
       #     conv1_biases.append(data[i])
        #On enleve le ] de fin de matrice
      #  conv1_biases[len(data)-1]= conv1_biases[len(data)-1].replace(']','')
        #affichage
      #  print(conv1_biases)
       # mon_fichier_r.write("conv1_biases = ")
       # mon_fichier_r.write(conv1_biases)

   # elsif (objet[0]=="conv1/weights")
   # elsif (objet[0]=="conv2/biases")
   # elsif (objet[0]=="conv2/weights")
   # elsif (objet[0]=="conv3/biases")
   # elsif (objet[0]=="conv3/weights")

