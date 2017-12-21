#include "../headers/main.hpp"
double*** maxpool(double ***sig,unsigned int* sig_size,unsigned int stride, unsigned int size)
{
    unsigned int max_size[3]= {sig_size[0]/stride,sig_size[1]/stride,sig_size[2]};
    double *** max=alloc_matrix(max_size);
    cout << sig_size[0]<<sig_size[1] <<sig_size[2]<< endl;
    for (unsigned int n = 0; n <sig_size[2];n++)
    {
        for (unsigned int i = 0; i <sig_size[0]-size;i+=stride)
        {
            for (unsigned int j = 0; j <sig_size[1]-size ;j+=stride)
            {
                unsigned int ii=i/(stride);
                unsigned int jj=j/(stride);
                for (unsigned int a = 0; a <size ;a++)
                {
                    for (unsigned int b = 0; b <size ;b++)
                    {
                        if(sig[i+a][j+b][n]>max[ii][jj][n] ){max[ii][jj][n]=sig[i+a][j+b][n];}
                    }
                }


            }
        }
    }
    return max;
}
