#include <iostream>
#include <stdio.h>
#include <math.h>

#include "Coefficient.hpp"
#include "Normalize.hpp"
#include "Write_file.hpp"


using namespace std;


#define NB_LIGNE_PLUS 32
#define NB_COLONNE_PLUS 32
#define NB_LIGNE 24
#define NB_COLONNE 24


int main()
{


  double img_red[NB_LIGNE][NB_COLONNE];
  double img_green[NB_LIGNE][NB_COLONNE];
  double img_blue[NB_LIGNE][NB_COLONNE];
  double coeff_weight1[3][64][3][3];
  double coeff_weight2[64][32][3][3];
  double coeff_weight3[32][20][3][3];
  double coeff_biases1[64];
  double coeff_biases2[32];
  double coeff_biases3[20];
  double coeff_biases4[10];
  double coeff_reshape[180][10];

  cout<<"Read and normalize image"<<endl;
  normalize_image("data_batch_1.bin",img_red,img_green,img_blue);

  //Regroup image
  double matrix_in[3][24][24];
  for(int L=0;L<24;L++)
    {
      for(int C=0;C<24;C++)
        {
	  matrix_in[1][L][C]=img_red[L][C];
	  matrix_in[2][L][C]=img_green[L][C];
	  matrix_in[3][L][C]=img_blue[L][C];
        }
    }

  

  cout<<"Read coefficients"<<endl;
  read_coefficient("CNN_coeff_3x3.txt", coeff_weight1, coeff_weight2, coeff_weight3, coeff_biases1, coeff_biases2, coeff_biases3, coeff_biases4, coeff_reshape);

  /*Parameters:

  matrix_in[3][24][24]	  

  coeff_weight1[3][64][3][3];
  coeff_weight2[64][32][3][3];
  coeff_weight3[32][20][3][3];
  coeff_biases1[64];
  coeff_biases2[32];
  coeff_biases3[20];
  coeff_biases4[10];
  coeff_reshape[180][10];
  */
  
  //Convolution1
  // Relu1
  // Maxpool1
  
  double matrix_out[64][24][24];
  for(int i=0;i<64;i++)
    {
      for(int j=0;j<24;j++)
        {
	  for(int k=0;k<24;k++)
            {
	      matrix_out[i][j][k]=0;
            }
        }
    }

  return 0;
}
