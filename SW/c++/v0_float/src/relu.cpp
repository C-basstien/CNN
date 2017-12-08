#include "../headers/main.hpp"
void relu(double*** sig,unsigned int* sig_size)// transform all the negatives coefficient of the array into 0
{
    for (unsigned int i = 0; i <sig_size[0];i++)
    {
        for (unsigned int j = 0; j <sig_size[1] ;j++)
        {
            for (unsigned int k = 0; k <sig_size[2] ;k++)
            {
                    if(sig[i][j][k]<0){sig[i][j][k]=0;}
            }
        }
    }
}
