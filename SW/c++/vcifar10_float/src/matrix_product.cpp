#include "../headers/main.hpp"

double * matrix_product(double ** M, double* V,unsigned int* sizes)
{
    double* res= new double[sizes[0]]();
    for(unsigned int i=0;i<sizes[0];i++)
    {
        for(unsigned int j=0;j<sizes[1];j++)
        {
            res[i]=res[i]+M[i][j]*V[j];
        }
    }
    return res;
}
