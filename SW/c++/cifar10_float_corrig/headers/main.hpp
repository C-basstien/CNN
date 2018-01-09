


#ifndef MAIN_HPP
#define MAIN_HPP



#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <png.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <math.h>
#include <string>
#include <string.h>

using namespace std;

#define MAX_IM 36864
#define MAX_KER 18432
#define MAX_BIAS 64

#define NB_LIGNE_PLUS 32
#define NB_COLONNE_PLUS 32
#define NB_LIGNE 24
#define NB_COLONNE 24
#define IN_C_1 3
#define KER_SIZE 3
#define NB_COL_LOC_RESHAPE 180
#define NB_BIAS_1 64
#define NB_BIAS_2 32
#define NB_BIAS_3 20
#define NB_BIAS_4 10

#define LIGNE_OUT 24
#define COLONNE_OUT 24

void write_img(double img_out[LIGNE_OUT][COLONNE_OUT]);

char* appendCharToCharArray(char* array, char a);
double read_float(std::string ligne,int* pos);

void read_coefficient(
                    std::string file,
                    double weigth1[MAX_KER],unsigned int weigth1_size[4],
                    double weigth2[MAX_KER],unsigned int weigth2_size[4],
                    double weigth3[MAX_KER],unsigned int weigth3_size[4],
                    double biases1[MAX_BIAS],
                    double biases2[MAX_BIAS],
                    double biases3[MAX_BIAS],
                    double biases4[NB_BIAS_4],
                    double reshape[NB_BIAS_4][NB_COL_LOC_RESHAPE]
                    );

double max_func(double a,double b);
void normalize_image(std::string image, double img_out_red[NB_LIGNE][NB_COLONNE], double img_out_green[NB_LIGNE][NB_COLONNE], double img_out_blue[NB_LIGNE][NB_COLONNE]);

unsigned int indice(unsigned int i,unsigned int j, unsigned int k, unsigned int size [3]);
unsigned int indice(unsigned int i,unsigned int j, unsigned int k,unsigned int l,unsigned int size [4]);

void convolve(double input[MAX_IM],double output[MAX_IM],double ker[MAX_KER],double bias[MAX_BIAS],unsigned int inout_size[3], unsigned int ker_size[4],unsigned int bias_size);
void relu(double inout[MAX_IM]);
void maxpool(double input[MAX_IM],double output[MAX_IM],unsigned int inout_size[3],unsigned int stride, unsigned int size);
void reshape(double input[MAX_IM],double output[180]);
void matrix_product(double input[180],double output[10],double M[10][180],double biases[10]);
void softmax(double in[10],double out[10]);

void print_signal(double signal[MAX_IM],unsigned int sig_size[3]);
void print_ker(double ker[MAX_IM],unsigned int sig_ker[4]);
void print_vector(double* vect, unsigned int size);




#endif

