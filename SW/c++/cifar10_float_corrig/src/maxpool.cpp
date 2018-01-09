#include "../headers/main.hpp"
void maxpool(double input[MAX_IM],double output[MAX_IM],unsigned int inout_size[3],unsigned int stride, unsigned int size)
{
    unsigned int max_size[3]= {inout_size[0]/stride,inout_size[1]/stride,inout_size[2]};
    unsigned int m=0;
    for (unsigned int i = 0;i<MAX_IM;i++){output[i]=0;}
    for (unsigned int n = 0; n <inout_size[2];n++)
    {
        for (unsigned int i = 0; i <inout_size[0]-size;i+=stride)
        {
            for (unsigned int j = 0; j <inout_size[1]-size ;j+=stride)
            {
                unsigned int ii=i/(stride);
                unsigned int jj=j/(stride);
                m=output[indice(ii,jj,n,max_size)];
                for (unsigned int a = 0; a <size ;a++)
                {
                    for (unsigned int b = 0; b <size ;b++)
                    {
                        if(input[indice(i+a,j+b,n,inout_size)]>m ){output[indice(ii,jj,n,max_size)]=input[indice(i+a,j+b,n,inout_size)];}
                    }
                }
            }
        }
    }
    inout_size[0]=max_size[0];inout_size[1]=max_size[1];inout_size[2]=max_size[2];
}
