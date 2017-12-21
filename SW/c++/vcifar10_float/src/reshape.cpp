#include "../headers/main.hpp"

double * reshape(double *** M,unsigned int size[3])
{
    double* res= new double[sizes[0]*sizes[1]*sizes[2]]();

    for (unsigned int i = 0; i <sizes[0];i++)
    {
        for (unsigned int j = 0; j <sizes[1];j++)
        {
            for (unsigned int k = 0; k <sizes[2];k++)
            {
                res[i*sizes[1]+j*sizes[0]+k]=mat[i][j][k];
            }
        }
    }
	return res;

}
