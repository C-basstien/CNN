#include "../headers/main.hpp"

double * softmax(double* V,unsigned int size)
{
    double* res= new double[size]();/**output vector**/
    double norm=0;
    for(unsigned int i=0;i<size;i++)/**calcul exp of each element of the vector and the sum of all this exp elemnts**/
    {
        res[i]=exp(V[i]);
        norm=norm+res[i];
    }
    for(unsigned int i=0;i<size;i++)//division for each elements by the norm (which is the sum of all the exponentiate elements of the vector)
    {
        res[i]=res[i]/norm;
    }

    return res;
}

