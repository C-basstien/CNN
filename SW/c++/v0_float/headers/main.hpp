


#ifndef MAIN_HPP
#define MAIN_HPP



#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <png.h>
#include <math.h>

using namespace std;

double*** alloc_matrix(unsigned int * dim_array);
void print_matrix(double*** mat,unsigned int * dim_array);
void print_ker(double**** ker,unsigned int * dim_array);
double*** convolve(char*** im, double**** ker,unsigned int* im_size, unsigned int* ker_size);
void relu(double*** sig,unsigned int* sig_size);
double*** maxpool(double ***sig,unsigned int* sig_size,unsigned int stride);
char*** read_png_file(char* file_name,unsigned int* output_im_size);
double**** gen_rand_ker(unsigned int* ker_size);
double * matrix_product(double ** M, double V,unsigned int* sizes);
double * softmax(double* V,unsigned int size);






#endif

