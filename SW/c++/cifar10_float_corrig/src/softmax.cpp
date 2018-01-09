#include "../headers/main.hpp"

void softmax(double in[10],double out[10])
{
    double max=0;
    double norm=0;
    for(unsigned int i=0;i<10;i++)
    {
            if(max<in[i]){max=in[i];}
    }
    for(unsigned int i=0;i<10;i++)
    {
        out[i]=exp(in[i]/max);
        norm=norm+out[i];
    }
    for(unsigned int i=0;i<10;i++)
    {
        out[i]=out[i]/norm;
    }
}

