
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <math.h>
#include <string>
#include <string.h>
#include "Coefficient.hpp"

using namespace std;



char* appendCharToCharArray(char* array, char a)
{
  size_t len = strlen(array);

  char* ret = new char[len+2];

  strcpy(ret, array);
  ret[len] = a;
  ret[len+1] = '\0';

  return ret;
}

double read_float(std::string ligne,int* pos)
{
  string value;
  double result;

  while(ligne[*pos]!=' ' && ligne[*pos]!=']' && *pos<ligne.size())
    {
      value+=ligne[*pos];
      *pos=*pos+1;;
    }
  result = atof(value.c_str());
  return result;
}


void read_coefficient(std::string file,double weigth1[IN_C_1][NB_BIAS_1][KER_SIZE][KER_SIZE], double weigth2[NB_BIAS_1][NB_BIAS_2][KER_SIZE][KER_SIZE], double weigth3[NB_BIAS_2][NB_BIAS_3][KER_SIZE][KER_SIZE], double biases1[NB_BIAS_1], double biases2[NB_BIAS_2],double biases3[NB_BIAS_3],double biases4[NB_BIAS_4], double reshape[NB_COL_LOC_RESHAPE][NB_BIAS_4])
{
  std::ifstream inFlux("CNN_coeff_3x3.txt");
  double value=0;
  int i=1;
  int* pos=&i;

  int posBias=0;

  *pos=1;
  if(inFlux)
    {
      std::string ligne;
      //bias1
      std::getline(inFlux,ligne);
      getline(inFlux,ligne);
      while(ligne.compare("tensor_name:  conv1/weights")!=0)
        {
	  i=1;
          while(ligne[i]!=']' && i<ligne.size())
            {
	      if(ligne[i]==' ')
                {
		  i++;
                }
	      value=read_float(ligne,pos);
	      biases1[posBias]=value;
	      i++;
	      posBias++;
            }
	  getline(inFlux,ligne);
        }
      cout<<"bias tab"<<endl;
      
      //remplissage weigth 1
      int var_in_c=0;
      int var_out_c=0;
      int var_ker_l=0;
      int var_ker_c=0;

      getline(inFlux,ligne);
      while(ligne.compare("tensor_name:  conv2/biases")!=0)
        {
	  i=4;
	  while(ligne[i]!=']' && i<ligne.size())
            {
	      while(ligne[i]==' ' || ligne[i]=='[')
                {
		  i++;
                }
	      value=read_float(ligne,&i);
	      weigth1[var_in_c][var_out_c][var_ker_l][var_ker_c]=value;
	      var_out_c++;
	      i++;
            }
	  if(var_out_c==NB_BIAS_1 && var_in_c!=IN_C_1-1)
            {
	      var_in_c++;
	      var_out_c=0;
            }
	  if(var_out_c==NB_BIAS_1 && var_in_c==IN_C_1-1)
            {
	      var_in_c=0;
	      var_out_c=0;

	      var_ker_c++;

	      if(var_ker_c==KER_SIZE && var_ker_l!=KER_SIZE-1)
                {
		  var_ker_c=0;
		  var_ker_l++;
                }
	      if(var_ker_c==KER_SIZE && var_ker_l==KER_SIZE-1)
                {
		  var_ker_l=0;
		  var_ker_c=0;
                }
            }
	  getline(inFlux,ligne);
        }

      cout<<"Done weigth"<<endl;

      //biases 2
      cout<<"biases2"<<endl;
      getline(inFlux,ligne);
      posBias=0;
      while(ligne.compare("tensor_name:  conv2/weights")!=0)
        {
	  i=1;
	  while(ligne[i]!=']' && i<ligne.size())
            {
	      if(ligne[i]==' ')
                {
		  i++;
                }
	      value=read_float(ligne,&i);
	      biases2[posBias]=value;

	      i++;
	      posBias++;
            }
	  getline(inFlux,ligne);
        }
      cout<<"bias tab"<<endl;
      cout<<"conv2/weigths"<<endl;
      var_in_c=0;
      var_out_c=0;
      var_ker_l=0;
      var_ker_c=0;

      getline(inFlux,ligne);
      while(ligne.compare("tensor_name:  conv3/biases")!=0)
        {
	  i=0;
	  while(ligne[i]!=']' && i<ligne.size())
            {
	      while(ligne[i]==' ' || ligne[i]=='[')
                {
		  i++;
                }
	      value=read_float(ligne,&i);
	      weigth2[var_in_c][var_out_c][var_ker_l][var_ker_c]=value;
	      var_out_c++;
	      i++;
            }
	  if(var_out_c==NB_BIAS_2 && var_in_c!=NB_BIAS_1-1)
            {
	      var_in_c++;
	      var_out_c=0;
            }
	  if(var_out_c==NB_BIAS_2 && var_in_c==NB_BIAS_1-1)
            {
	      var_in_c=0;
	      var_out_c=0;

	      var_ker_c++;

	      if(var_ker_c==KER_SIZE && var_ker_l!=KER_SIZE-1)
                {
		  var_ker_c=0;
		  var_ker_l++;
                }
	      if(var_ker_c==KER_SIZE && var_ker_l==KER_SIZE-1)
                {
		  var_ker_l=0;
		  var_ker_c=0;
                }
            }
	  getline(inFlux,ligne);
        }

      cout<<"Done weigth"<<endl;

      //conv3/bias
      cout<<"biases3"<<endl;
      getline(inFlux,ligne);
      posBias=0;
      while(ligne.compare("tensor_name:  conv3/weights")!=0)
        {
	  i=1;

	  while(ligne[i]!=']' && i<ligne.size())
            {
	      if(ligne[i]==' ')
                {
		  i++;
                }
	      value=read_float(ligne,&i);
	      biases3[posBias]=value;

	      i++;
	      posBias++;
            }
	  getline(inFlux,ligne);
        }
      cout<<"bias tab"<<endl;
      //conv3/weigths
      cout<<"conv3/weigths"<<endl;
      var_in_c=0;
      var_out_c=0;
      var_ker_l=0;
      var_ker_c=0;

      getline(inFlux,ligne);
      while(ligne.compare("tensor_name:  local3/biases")!=0)
        {
	  i=0;
	  while(ligne[i]!=']' && i<ligne.size())
            {
	      while(ligne[i]==' ' || ligne[i]=='[')
                {
		  i++;
                }
	      value=read_float(ligne,&i);
	      weigth3[var_in_c][var_out_c][var_ker_l][var_ker_c]=value;
	      var_out_c++;
	      i++;
            }
	  if(var_out_c==NB_BIAS_3 && var_in_c!=NB_BIAS_2-1)
            {
	      var_in_c++;
	      var_out_c=0;
            }
	  if(var_out_c==NB_BIAS_3 && var_in_c==NB_BIAS_2-1)
            {
	      var_in_c=0;
	      var_out_c=0;

	      var_ker_c++;

	      if(var_ker_c==KER_SIZE && var_ker_l!=KER_SIZE-1)
                {
		  var_ker_c=0;
		  var_ker_l++;
                }
	      if(var_ker_c==KER_SIZE && var_ker_l==KER_SIZE-1)
                {
		  var_ker_l=0;
		  var_ker_c=0;
                }
            }
	  getline(inFlux,ligne);
        }

      cout<<"Done weigth"<<endl;

      //local3/biases
      cout<<"local3/biases"<<endl;
      getline(inFlux,ligne);
      posBias=0;
      while(ligne.compare("tensor_name:  local3/weights")!=0)
        {
	  i=1;

	  while(ligne[i]!=']' && i<ligne.size())
            {
	      if(ligne[i]==' ')
                {
		  i++;
                }
	      value=read_float(ligne,&i);
	      biases4[posBias]=value;

	      i++;
	      posBias++;
            }
	  getline(inFlux,ligne);
        }
      cout<<"bias tab"<<endl;
 
      //local3/weigths
      cout<<"conv4/weigths"<<endl;
      int var_ligne=0;
      int var_colonne=0;

      while(getline(inFlux,ligne))
        {
	  i=0;
	  while(ligne[i]!=']' && i<ligne.size())
            {
	      while(ligne[i]==' ' || ligne[i]=='[')
                {
		  i++;
                }
	      value=read_float(ligne,&i);
	      reshape[var_ligne][var_colonne]=value;
	      var_ligne++;
	      i++;
            }
	  if(var_ligne==NB_COL_LOC_RESHAPE && var_colonne!=NB_BIAS_4-1)
            {
	      var_colonne++;
	      var_ligne=0;
            }
	  if(var_ligne==NB_COL_LOC_RESHAPE && var_colonne==NB_BIAS_4-1)
            {
	      var_ligne=0;
	      var_colonne=0;
            }
        }

      cout<<"Done weigth"<<endl;


      inFlux.close();
    }
  else{
    std::cout<<"Error flux input"<<std::endl;
    inFlux.close();

  }
}


