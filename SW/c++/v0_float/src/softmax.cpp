#include "../headers/main.hpp"

double * softmax(double* V,unsigned int size)
{
    double* res= new double[size]();
    double max=0;
    double norm=0;
    for(unsigned int i=0;i<size;i++)
    {
            if(max<V[i]){max=V[i];}
    }
    for(unsigned int i=0;i<size;i++)
    {
        res[i]=exp(V[i]);
        norm=norm+res[i];
    }
    for(unsigned int i=0;i<size;i++)
    {
        res[i]=res[i]/norm;
    }

    return res;
}

