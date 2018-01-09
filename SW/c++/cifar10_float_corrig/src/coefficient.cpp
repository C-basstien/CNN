
#include "../headers/main.hpp"



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
void init_weigth(double weigth[MAX_KER])
{
    for(unsigned int i=0;i<MAX_KER;i++ )
    {
        weigth[i]=0;
    }
}
void init_bias(double biases[MAX_BIAS])
{
    for(unsigned int i=0;i<MAX_BIAS;i++ )
    {
        biases[i]=0;
    }
}

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
                    )
{
  init_weigth(weigth1);
  init_weigth(weigth2);
  init_weigth(weigth3);
  init_bias(biases1);
  init_bias(biases2);
  init_bias(biases3);
  std::ifstream inFlux("./cifardata/CNN_coeff_3x3.txt");
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
	      weigth1[indice(var_ker_c,var_ker_l,var_out_c,var_in_c,weigth1_size)]=value;
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
	      weigth2[indice(var_ker_c,var_ker_l,var_out_c,var_in_c,weigth2_size)]=value;
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
	      weigth3[indice(var_ker_c,var_ker_l,var_out_c,var_in_c,weigth3_size)]=value;
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
	      reshape[var_colonne][var_ligne]=value;
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


