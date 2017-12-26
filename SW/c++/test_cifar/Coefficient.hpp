#ifndef COEFFICIENT_HPP
#define COEFFICIENT_HPP

#include <iostream>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <math.h>

using namespace std;



#define IN_C_1 3
#define KER_SIZE 3
#define NB_COL_LOC_RESHAPE 180
#define NB_BIAS_1 64
#define NB_BIAS_2 32
#define NB_BIAS_3 20
#define NB_BIAS_4 10

char* appendCharToCharArray(char* array, char a);
double read_float(std::string ligne,int* pos);

void read_coefficient(std::string file,double weigth1[IN_C_1][NB_BIAS_1][KER_SIZE][KER_SIZE], double weigth2[NB_BIAS_1][NB_BIAS_2][KER_SIZE][KER_SIZE], double weigth3[NB_BIAS_2][NB_BIAS_3][KER_SIZE][KER_SIZE], double biases1[NB_BIAS_1], double biases2[NB_BIAS_2],double biases3[NB_BIAS_3],double biases4[NB_BIAS_4], double reshape[NB_COL_LOC_RESHAPE][NB_BIAS_4]);

#endif 
